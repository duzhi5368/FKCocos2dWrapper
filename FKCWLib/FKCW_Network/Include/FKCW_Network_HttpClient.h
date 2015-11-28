/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network_HttpClient
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_HttpRequest.h"
#include "FKCW_Network_HttpResponse.h"
//--------------------------------------------------------------------
// ������һ��HttpӦ������Ҫ�����ɹ���ʾ
#define NotificationHttpRequestCompleted	"NotificationHttpRequestCompleted"
// ������һ��HttpӦ������Դ��л�ȡ����Ƭ��
#define NotificationHttpDataReceived		"NotificationHttpDataReceived"
// ��ͷ����ʵ������֮ǰ�Ƚ��յ�ʱ������һ��HttpӦ������Դ��л��ͷ
#define NotificationHttpDidReceiveResponse	"NotificationHttpDidReceiveResponse"
//--------------------------------------------------------------------
/*
	�����cocos2dx��չ���е�CCHttpClient��ͬ���У�
	1�������ڲ��������н��лص������������ڽ���ʱ�лص�
	2����������ȡ����
	3�������ǵ���
	˵����
	ʹ�������豣��һ��httpClientʵ����Http���󽫻���һ���߳���ִ�У�
	�����㱣��һ��httpClientʵ��������retain����û��ʲô���塣
*/
//--------------------------------------------------------------------
class FKCW_Network_HttpClient : public CCObject
{
private:
	vector<void*>			m_vecActiveContexts;		// �����̱߳�key�Ǳ�ǩ
	pthread_mutex_t			m_Mutex;					// �̻߳�����
	CC_SYNTHESIZE(float, m_fConnectTimeout, ConnectTimeout);	// ���ӳ�ʱʱ��
	CC_SYNTHESIZE(float, m_fReadTimeout, ReadTimeout);			// ��ȡ��ʱʱ��
private:
	// �߳����
	static void* __HttpThreadEntry( void* p_pArg );
protected:
	FKCW_Network_HttpClient();
public:
	virtual ~FKCW_Network_HttpClient();
	static FKCW_Network_HttpClient* Create();

	// ��ʼ��
	virtual bool	Init();
	// ִ��һ��Http���󣬸�������һ���������߳���ִ��
	// ������p_pRequest Http������󡣰�������url����Ӧ�ص��ȶ�������
	// ע���뱣֤��ִ�б�����֮ǰ�������е� p_pRequest->m_pRequestData �ѱ����
	void			AsyncExecute( FKCW_Network_HttpRequest* p_pRequest );
	// ȡ��һ������
	void			Cancel( int p_nTag );
	// ȡ��ȫ��http����
	void			CancelAll();
	// �Ƴ��߳�������
	void			RemoveContext( void* p_pContext );
};