//--------------------------------------------------------------------
#include "../Include/FKCW_Network_FileDownLoader.h"
#include "../../FKCW_Base/Include/FKCW_Base_Utils.h"
//--------------------------------------------------------------------
// FKCW_Network_DownloadEntry
//--------------------------------------------------------------------
FKCW_Network_DownloadEntry::FKCW_Network_DownloadEntry()
	: m_unSize( 0 )
	, m_bAppend( false )
{

}
//--------------------------------------------------------------------
FKCW_Network_DownloadEntry::~FKCW_Network_DownloadEntry()
{

}
//--------------------------------------------------------------------
FKCW_Network_DownloadEntry*	FKCW_Network_DownloadEntry::Create()
{
	FKCW_Network_DownloadEntry* p = new FKCW_Network_DownloadEntry();
	return ( FKCW_Network_DownloadEntry* )p->autorelease();
}
//--------------------------------------------------------------------
// FKCW_Network_FileDownLoader
//--------------------------------------------------------------------
static FKCW_Network_FileDownLoader* s_Instance = NULL;
//--------------------------------------------------------------------
FKCW_Network_FileDownLoader::FKCW_Network_FileDownLoader()
	: m_bIsDownloading( false )
	, m_nTotalSize( 0 )
	, m_nTotalDownloadedSize( 0 )
	, m_pFOS( NULL )
{
	m_pClient = FKCW_Network_HttpClient::Create();
	CC_SAFE_RETAIN(m_pClient);

	// ������
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FKCW_Network_FileDownLoader::_OnHttpDone), NotificationHttpRequestCompleted, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FKCW_Network_FileDownLoader::_OnHttpData), NotificationHttpDataReceived, NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(FKCW_Network_FileDownLoader::_OnHttpHeaders), NotificationHttpDidReceiveResponse, NULL);
}
//--------------------------------------------------------------------
// ��ʼ��
bool FKCW_Network_FileDownLoader::_Init()
{
	return true;
}
//--------------------------------------------------------------------
// ֪ͨ
void FKCW_Network_FileDownLoader::_OnHttpDone( FKCW_Network_HttpResponse* p_pResponse )
{
	// ���û�����ص�Ԫ�������Ϣ�����Լ��ġ�
	if(!m_pEntry)
		return;

	// ʧ����
	if(!p_pResponse->isSuccess()) 
	{
		m_vecFailedEntries.addObject(m_pEntry);
	}

	// �ر���
	CC_SAFE_RELEASE_NULL(m_pFOS);
	m_pEntry = NULL;

	// �Ƴ���һ�����ص�Ԫ
	m_vecEntries.removeObjectAtIndex(0);

	// ������һ��
	if(m_vecEntries.count() > 0) 
	{
		_DownloadNext();
	} 
	else 
	{
		m_bIsDownloading = false;
	}
}
//--------------------------------------------------------------------
void FKCW_Network_FileDownLoader::_OnHttpData( FKCW_Network_HttpResponse* p_pResponse )
{
	if( m_pFOS ) 
	{
		FKCW_Base_Data* data = p_pResponse->getData();
		m_pFOS->Write((const char*)data->getBytes(), data->getSize());
		m_nTotalDownloadedSize += data->getSize();
	}
}
//--------------------------------------------------------------------
void FKCW_Network_FileDownLoader::_OnHttpHeaders( CCObject* p )
{
	FKCW_Network_HttpResponse* response = (FKCW_Network_HttpResponse*)p;
	if( m_pEntry ) 
	{
		if(m_pEntry->m_unSize == 0) 
		{
			string contentLength = response->GetHeader("Content-Length");
			m_pEntry->m_unSize = atoi(contentLength.c_str());
		}
	}
}
//--------------------------------------------------------------------
// ������һ��ʵ��
void FKCW_Network_FileDownLoader::_DownloadNext()
{
	// ��ȡ��һ�����ض���
	m_pEntry = (FKCW_Network_DownloadEntry*)m_vecEntries.objectAtIndex(0);

	// ������
	string path = m_strFolder + m_pEntry->m_strDstName;
	m_pFOS = FKCW_IO_AssetOutputStream::Create( path, m_pEntry->m_bAppend );
	CC_SAFE_RETAIN(m_pFOS);

	// ��ʼ����
	FKCW_Network_HttpRequest* request = FKCW_Network_HttpRequest::Create();
	request->setUrl(m_pEntry->m_strUrl);
	request->setMethod(FKCW_Network_HttpRequest::eHttpMethod_Get);
	m_pClient->AsyncExecute(request);
}
//--------------------------------------------------------------------
FKCW_Network_FileDownLoader::~FKCW_Network_FileDownLoader()
{
	CC_SAFE_RELEASE(m_pClient);
	s_Instance = NULL;
}
//--------------------------------------------------------------------
FKCW_Network_FileDownLoader* FKCW_Network_FileDownLoader::GetInstance()
{
	if(!s_Instance) 
	{
		s_Instance = new FKCW_Network_FileDownLoader();
	}
	return s_Instance;
}
//--------------------------------------------------------------------
// ����ļ�����������
void FKCW_Network_FileDownLoader::Purge()
{
	if(s_Instance) 
	{
		// �Ƴ�������
		CCNotificationCenter::sharedNotificationCenter()->removeObserver(s_Instance, NotificationHttpRequestCompleted);
		CCNotificationCenter::sharedNotificationCenter()->removeObserver(s_Instance, NotificationHttpDataReceived);
		CCNotificationCenter::sharedNotificationCenter()->removeObserver(s_Instance, NotificationHttpDidReceiveResponse);

		CC_SAFE_RELEASE(s_Instance);
	}
}
//--------------------------------------------------------------------
// ���һ����Ҫ���صĶ���
// ������p_strUrl ��Ҫ���ص��ļ�url���ļ�������url�����һ��
//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
void FKCW_Network_FileDownLoader::AddFile( const string& p_strUrl, bool p_bIsAppend )
{
	string str = p_strUrl;
	string dst = FKCW_Base_Utils::LastPathOfComponent(str);
	AddFile(p_strUrl, dst, p_bIsAppend);
}
//--------------------------------------------------------------------
// ���һ����Ҫ���صĶ���
// ������p_strUrl ��Ҫ���ص��ļ�url
//		p_strFileName �����ļ��󣬸���Ϊ�µ��ļ���
//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
void FKCW_Network_FileDownLoader::AddFile( const string& p_strUrl, const string& p_strFileName, bool p_bIsAppend )
{
	AddFile(p_strUrl, p_strFileName, 0, p_bIsAppend);
}
//--------------------------------------------------------------------
// ���һ����Ҫ���صĶ���
// ������p_strUrl ��Ҫ���ص��ļ�url
//		p_strFileName �����ļ��󣬸���Ϊ�µ��ļ���
//		p_unSize Ҫ���ص��ļ���С
//		p_bIsAppend ����ֵΪtrue������ζ�����غ���ļ�������ڱ��ص�ͬ��ԭ�ļ����棬��Ϊfalse�����滻
void FKCW_Network_FileDownLoader::AddFile( const string& p_strUrl, const string& p_strFileName, size_t p_unSize, bool p_bIsAppend )
{
	FKCW_Network_DownloadEntry* e = FKCW_Network_DownloadEntry::Create();
	e->m_strUrl			= p_strUrl;
	e->m_strDstName		= p_strFileName;
	e->m_unSize			= p_unSize;
	e->m_bAppend		= p_bIsAppend;
	m_nTotalSize		+= p_unSize;
	m_vecEntries.addObject(e);
}
//--------------------------------------------------------------------
// ��ʼ����
void FKCW_Network_FileDownLoader::Start()
{
	if(!m_bIsDownloading) 
	{
		// �������Ҫ���ص�ʵ�壬��go..
		if(m_vecEntries.count() > 0) 
		{
			m_vecFailedEntries.removeAllObjects();
			_DownloadNext();
			m_bIsDownloading = true;
		}
	}
}
//--------------------------------------------------------------------
// �ж�����
void FKCW_Network_FileDownLoader::Abort()
{
	if(m_bIsDownloading) 
	{
		m_pClient->CancelAll();
		CC_SAFE_RELEASE_NULL(m_pFOS);
		m_pEntry = NULL;
		m_vecEntries.removeAllObjects();
		m_bIsDownloading = false;
	}
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�����ļ������صĴ�С
size_t FKCW_Network_FileDownLoader::GetCurrentDownloadedSize()
{
	return m_pFOS ? m_pFOS->GetPosition() : 0;
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�������ص��ļ���
string FKCW_Network_FileDownLoader::GetCurrentDownloadingFileName()
{
	return m_pEntry ? FKCW_Base_Utils::LastPathOfComponent( m_pEntry->m_strDstName ) : "";
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�������ص��ļ���������ȫ��·��
string FKCW_Network_FileDownLoader::GetCurrentDownloadingFileFullPath()
{
	return m_pEntry ? m_pEntry->m_strDstName : "";
}
//--------------------------------------------------------------------
// ��ȡ��ǰ�����ļ����ܴ�С
// ע������δ֪�����ļ���С�����ֵ����Ϊ0
size_t FKCW_Network_FileDownLoader::GetCurrentDownloadingFileSize()
{
	return m_pEntry ? m_pEntry->m_unSize : 0;
}
//--------------------------------------------------------------------