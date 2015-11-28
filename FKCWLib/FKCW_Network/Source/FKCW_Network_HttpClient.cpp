//--------------------------------------------------------------------
#include "../Include/FKCW_Network_HttpClient.h"
#include <queue>
#include <errno.h>
#include "curl/curl.h"
#include <pthread.h>
#include "../../FKCW_Base/Include/FKCW_Base_Data.h"
//--------------------------------------------------------------------
struct SHttpContext
{
	FKCW_Network_HttpClient*		client;
	FKCW_Network_HttpRequest*		request;
	FKCW_Network_HttpResponse*		response;
	float							connectTimeout;
	float							readTimeout;
};
//--------------------------------------------------------------------
// ʵ��ִ��һ��Http����
class FKCW_Network_UrlHandler : public CCObject
{
public:
	CURL*			m_pCurl;							// CURLʵ��
	curl_slist*		m_pHeaders;							// ������Զ��� ͷ����
	char			m_szErrorBuffer[CURL_ERROR_SIZE];	// ������Ϣ����
	SHttpContext*	m_pCtx;								// Http����������
	int32_t			m_nResponseCode;					// Ӧ����
	pthread_mutex_t m_pMutex;							// ������
	bool			m_bIsDone;							// �Ƿ���ɵı�־
	FKCW_Base_Data* m_pData;							// δ�ͷ�����
	bool			m_bIsHttpDidReceiveResponseDelivered;	// NotificationHttpDidReceiveResponse �Ƿ����
	bool			m_bIsHeaderAllReceived;				// �Ƿ�ȫ��ͷ�������
public:
	FKCW_Network_UrlHandler()
		: m_pCtx( NULL )
		, m_pCurl( NULL )
		, m_bIsDone( false )
		, m_nResponseCode( 500 )
		, m_bIsHttpDidReceiveResponseDelivered( false )
		, m_bIsHeaderAllReceived( false )
		, m_pHeaders( NULL )
	{
		m_pData = new FKCW_Base_Data();
		CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(FKCW_Network_UrlHandler::DispatchNotification), this, 0, kCCRepeatForever, 0, false);
	}

	virtual ~FKCW_Network_UrlHandler()
	{
		if(m_pCurl)
			curl_easy_cleanup(m_pCurl);
		if(m_pHeaders)
			curl_slist_free_all(m_pHeaders);
		if(m_pCtx->client) {
			m_pCtx->client->RemoveContext(m_pCtx);
		}
		CC_SAFE_RELEASE(m_pCtx->request);
		CC_SAFE_RELEASE(m_pCtx->response);
		CC_SAFE_FREE(m_pCtx);
		CC_SAFE_RELEASE(m_pData);
		pthread_mutex_destroy(&m_pMutex);
	}

	// libcul�յ���Ӧ���ݵĻص�����
	static size_t WriteData(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		FKCW_Network_UrlHandler* handler = (FKCW_Network_UrlHandler*)userdata;
		size_t sizes = size * nmemb;

		// �ڽ��ջ���������һ������
		pthread_mutex_lock(&handler->m_pMutex);
		handler->m_pData->AppendBytes((uint8_t*)ptr, sizes);
		handler->m_bIsHeaderAllReceived = true;
		pthread_mutex_unlock(&handler->m_pMutex);

		// ����һ��ֵ�������ֵ����մ�С��ͬ������ֹ
		if(handler->m_pCtx->request->isCancel())
			return sizes + 1;
		else
			return sizes;
	}

	// libcul�յ�ͷ���ݵĻص�����
	static size_t WriteHeaderData(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		FKCW_Network_UrlHandler* handler = (FKCW_Network_UrlHandler*)userdata;
		size_t sizes = size * nmemb;

		// ��
		pthread_mutex_lock(&handler->m_pMutex);

		// ��ʼ����
		string header((const char*)ptr, sizes);
		CCArray* pair = new CCArray();
		if(!header.empty()) 
		{
			// �Ƴ�ͷ��β���ո��Լ�����
			size_t start = 0;
			size_t end = header.length() - 1;
			char c = header[start];
			while(c == '{' || c == '[' || c == '(') 
			{
				start++;
				c = header[start];
			}
			c = header[end];
			while(c == '}' || c == ']' || c == ')') 
			{
				end--;
				c = header[end];
			}

			// ���������ַ���
			size_t compStart = start;
			for(size_t i = start; i <= end; i++) 
			{
				c = header[i];
				if(c == ':') 
				{
					CCString* s = new CCString(header.substr(compStart, i - compStart));
					pair->addObject(s);
					s->release();
					compStart = i + 1;
				} 
				else if(c == ' ' || c == '\t' || c == '\r' || c == '\n') 
				{
					if(compStart == i) 
					{
						compStart++;
					}
				}
			}

			// ������һ���ַ��Ƿָ�����������ַ�������
			if(compStart <= end)
			{
				CCString* s = new CCString(header.substr(compStart, end - compStart + 1));
				pair->addObject(s);
				s->release();
			} 
			else if(header[end] == ':') 
			{
				CCString* s = new CCString("");
				pair->addObject(s);
				s->release();
			}
		}

		// �������Ϊ2��������
		if(pair->count() == 2) 
		{
			handler->m_pCtx->response->AddHeader(((CCString*)pair->objectAtIndex(0))->getCString(),
				((CCString*)pair->objectAtIndex(1))->getCString());
		}

		pair->release();

		// ����
		pthread_mutex_unlock(&handler->m_pMutex);

		// ����һ��ֵ������ֵ����մ�С��ͬ������ֹ
		if(handler->m_pCtx->request->isCancel())
			return sizes + 1;
		else
			return sizes;
	}

	bool InitWithContext(SHttpContext* ctx) 
	{
		// ����������
		m_pCtx = ctx;

		// ���
		m_pCurl = curl_easy_init();
		if (!m_pCurl)
			return false;
		if (!ConfigureCURL())
			return false;

		// ����������
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&m_pMutex, &attr);
		pthread_mutexattr_destroy(&attr);

		// ��ȡ�Զ���ͷ����
		const vector<string>& headers = ctx->request->getHeaders();
		if(!headers.empty()) 
		{
			// �������Զ���ͷ
			for (vector<string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
				m_pHeaders = curl_slist_append(m_pHeaders, it->c_str());

			// Ϊcurl�����Զ���ͷ
			if (curl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, m_pHeaders) != CURLE_OK)
				return false;
		}

		return curl_easy_setopt(m_pCurl, CURLOPT_URL, ctx->request->getUrl().c_str()) == CURLE_OK &&
			curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, WriteData) == CURLE_OK &&
			curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, this) == CURLE_OK &&
			curl_easy_setopt(m_pCurl, CURLOPT_HEADERFUNCTION, WriteHeaderData) == CURLE_OK &&
			curl_easy_setopt(m_pCurl, CURLOPT_HEADERDATA, this) == CURLE_OK;
	}

	bool ConfigureCURL()
	{
		if(curl_easy_setopt(m_pCurl, CURLOPT_ERRORBUFFER, m_szErrorBuffer) != CURLE_OK) 
		{
			return false;
		}
		if(curl_easy_setopt(m_pCurl, CURLOPT_TIMEOUT, m_pCtx->readTimeout) != CURLE_OK) 
		{
			return false;
		}
		if(curl_easy_setopt(m_pCurl, CURLOPT_CONNECTTIMEOUT, m_pCtx->connectTimeout) != CURLE_OK) 
		{
			return false;
		}
		curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
		// �����ʱ�������߳̽��ж����߳�
		curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL, 1L);

		return true;
	}

	bool ProcessGetTask() 
	{
		curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, true);
		return Perform();
	}

	bool ProcessPostTask() 
	{
		curl_easy_setopt(m_pCurl, CURLOPT_POST, 1);
		FKCW_Base_Data* data = m_pCtx->request->getRequestData();
		if(data) 
		{
			curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, data->getBytes());
			curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, data->getSize());
		}
		return Perform();
	}

	bool ProcessPutTask() 
	{
		curl_easy_setopt(m_pCurl, CURLOPT_CUSTOMREQUEST, "PUT");
		FKCW_Base_Data* data = m_pCtx->request->getRequestData();
		if(data) {
			curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDS, data->getBytes());
			curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, data->getSize());
		}

		return Perform();
	}

	bool ProcessDeleteTask() 
	{
		curl_easy_setopt(m_pCurl, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_easy_setopt(m_pCurl, CURLOPT_FOLLOWLOCATION, true);
		return Perform();
	}

	bool Perform() 
	{
		CURLcode code = curl_easy_perform(m_pCurl);
		if (code != CURLE_OK)
		{
			CCLOG("curl_easy_perform error: %d, request: %s", code, m_pCtx->request->getUrl().c_str());
			return false;
		}

		// ��ȡ������
		code = curl_easy_getinfo(m_pCurl, CURLINFO_RESPONSE_CODE, &m_nResponseCode);
		if (code != CURLE_OK || m_nResponseCode != 200)
			return false;

		return true;
	}
	
	// �������ʱ����
	void OnRequestDone() 
	{
		pthread_mutex_lock(&m_pMutex);
		m_bIsDone = true;
		pthread_mutex_unlock(&m_pMutex);
	}

	// ��Ϣ�ַ�
	void DispatchNotification(float delta) 
	{
		// ��Ϣ����
		CCNotificationCenter* nc = CCNotificationCenter::sharedNotificationCenter();
		pthread_mutex_lock(&m_pMutex);

		// ͷ��Ϣ֪ͨ
		if(!m_bIsHttpDidReceiveResponseDelivered && m_bIsHeaderAllReceived)
		{
			m_bIsHttpDidReceiveResponseDelivered = true;
			nc->postNotification( NotificationHttpDidReceiveResponse, m_pCtx->response);
		}

		// ֪ͨ
		if(m_pData->getSize() > 0) 
		{
			m_pCtx->response->setData(m_pData);
			nc->postNotification( NotificationHttpDataReceived, m_pCtx->response);

			// �ؽ�һ�������ݶ���
			CC_SAFE_RELEASE(m_pData);
			m_pData = new FKCW_Base_Data();
		}

		// �Ƿ����
		if(m_bIsDone) 
		{
			// ֪ͨ
			nc->postNotification( NotificationHttpRequestCompleted, m_pCtx->response);
			// ��HttpThreadEntry����retain,��������Ҫrelease();
			autorelease();
			// ����ж��
			CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(FKCW_Network_UrlHandler::DispatchNotification), this);
		}

		pthread_mutex_unlock(&m_pMutex);
	}
};
//--------------------------------------------------------------------
// FKCW_Network_HttpClient
//--------------------------------------------------------------------
// �߳����
void* FKCW_Network_HttpClient::__HttpThreadEntry( void* p_pArg )
{
	// url������������ʼ��ʧ�ܻ���������� DispatchNotification() �����б��ͷţ��벻Ҫ�ֶ��ͷ�
	SHttpContext* ctx = (SHttpContext*)p_pArg;
	FKCW_Network_UrlHandler* curl = new FKCW_Network_UrlHandler();
	if(!curl->InitWithContext(ctx)) 
	{
		CC_SAFE_RELEASE_NULL(curl);
	}

	if(curl) 
	{
		// ����һ��Ӧ��
		FKCW_Network_HttpResponse* response = new FKCW_Network_HttpResponse(ctx->request);
		ctx->response = response;

		// ��������
		bool retValue = false;
		switch (ctx->request->getMethod()) {
		case FKCW_Network_HttpRequest::eHttpMethod_Get:
			retValue = curl->ProcessGetTask();
			break;
		case FKCW_Network_HttpRequest::eHttpMethod_Post:
			retValue = curl->ProcessPostTask();
			break;
		case FKCW_Network_HttpRequest::eHttpMethod_Put:
			retValue = curl->ProcessPutTask();
			break;
		case FKCW_Network_HttpRequest::eHttpMethod_Delete:
			retValue = curl->ProcessDeleteTask();
			break;
		default:
			CCAssert(true, "CBHttpClient: unkown request type, only GET and POST are supported");
			break;
		}

		// ����Ӧ��
		response->setResponseCode(curl->m_nResponseCode);
		if (retValue) 
		{
			response->setSuccess(true);
		} else 
		{
			response->setSuccess(false);
			response->SetErrorData(curl->m_szErrorBuffer);
		}

		// ���
		curl->OnRequestDone();
	}

	// �˳�
	pthread_exit(NULL);

	return NULL;
}
//--------------------------------------------------------------------
FKCW_Network_HttpClient::FKCW_Network_HttpClient()
	: m_fConnectTimeout( 30.0f )
	, m_fReadTimeout( 60.0f )
{
	// ����������
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_Mutex, &attr);
	pthread_mutexattr_destroy(&attr);
}
//--------------------------------------------------------------------
FKCW_Network_HttpClient::~FKCW_Network_HttpClient()
{
	pthread_mutex_lock(&m_Mutex);
	for(vector<void*>::iterator iter = m_vecActiveContexts.begin(); iter != m_vecActiveContexts.end(); iter++)
	{
		SHttpContext* ctx = (SHttpContext*)*iter;
		ctx->client = NULL;
	}
	pthread_mutex_unlock(&m_Mutex);
	pthread_mutex_destroy(&m_Mutex);
}
//--------------------------------------------------------------------
FKCW_Network_HttpClient* FKCW_Network_HttpClient::Create()
{
	FKCW_Network_HttpClient* c = new FKCW_Network_HttpClient();
	if(c->Init()) 
	{
		return (FKCW_Network_HttpClient*)c->autorelease();
	}
	CC_SAFE_RELEASE(c);
	return NULL;
}
//--------------------------------------------------------------------
// ��ʼ��
bool FKCW_Network_HttpClient::Init()
{
	return true;
}
//--------------------------------------------------------------------
// ִ��һ��Http���󣬸�������һ���������߳���ִ��
// ������p_pRequest Http������󡣰�������url����Ӧ�ص��ȶ�������
// ע���뱣֤��ִ�б�����֮ǰ�������е� p_pRequest->m_pRequestData �ѱ����
void FKCW_Network_HttpClient::AsyncExecute( FKCW_Network_HttpRequest* p_pRequest )
{
	if (!p_pRequest)
	{
		return;
	}

	// ����������
	SHttpContext* ctx = (SHttpContext*)calloc(1, sizeof(SHttpContext));
	ctx->request = p_pRequest;
	ctx->connectTimeout = m_fConnectTimeout;
	ctx->readTimeout = m_fReadTimeout;
	ctx->client = this;
	CC_SAFE_RETAIN(p_pRequest);

	// ��ӵ�cache
	pthread_mutex_lock(&m_Mutex);
	m_vecActiveContexts.push_back(ctx);
	pthread_mutex_unlock(&m_Mutex);

	// ���������߳�
	pthread_t thread;
	pthread_create(&thread, NULL, __HttpThreadEntry, ctx);
	pthread_detach(thread);
}
//--------------------------------------------------------------------
// ȡ��һ������
void FKCW_Network_HttpClient::Cancel( int p_nTag )
{
	pthread_mutex_lock(&m_Mutex);
	for(vector<void*>::iterator iter = m_vecActiveContexts.begin(); iter != m_vecActiveContexts.end(); iter++)
	{
		SHttpContext* ctx = (SHttpContext*)*iter;
		if(ctx->request->getTag() == p_nTag) 
		{
			ctx->request->setCancel(true);
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// ȡ��ȫ��http����
void FKCW_Network_HttpClient::CancelAll()
{
	pthread_mutex_lock(&m_Mutex);
	for(vector<void*>::iterator iter = m_vecActiveContexts.begin(); iter != m_vecActiveContexts.end(); iter++) 
	{
		SHttpContext* ctx = (SHttpContext*)*iter;
		ctx->request->setCancel(true);
	}
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �Ƴ��߳�������
void FKCW_Network_HttpClient::RemoveContext( void* p_pContext )
{
	pthread_mutex_lock(&m_Mutex);
	for(vector<void*>::iterator iter = m_vecActiveContexts.begin(); iter != m_vecActiveContexts.end(); iter++) 
	{
		if(p_pContext == *iter)
		{
			m_vecActiveContexts.erase(iter);
			break;
		}
	}
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------