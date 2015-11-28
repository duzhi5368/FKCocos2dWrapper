//--------------------------------------------------------------------
#include "../Include/FKCW_Network_TCPSocketHub.h"
//--------------------------------------------------------------------
static MULTI_ENCRYPT_FUNC s_EncryptFunc = NULL;
static MULTI_DECRYPT_FUNC s_DecryptFunc = NULL;
//--------------------------------------------------------------------
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	#pragma comment(lib, "Ws2_32.lib")
#endif
//-------------------------------------------------------------------------
FKCW_Network_TCPSocketHub::FKCW_Network_TCPSocketHub()
	: m_bIsRawPolicy( false )
{
	// ��ʼ��WSA
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
#endif
	pthread_mutex_init( &m_Mutex, NULL );

	// ������ѭ��
	CCScheduler* s = CCDirector::sharedDirector()->getScheduler();
	s->scheduleSelector(schedule_selector(FKCW_Network_TCPSocketHub::_MainLoop), this, 0, false);
}
//--------------------------------------------------------------------
// �����׽��֣������ж�д����
void FKCW_Network_TCPSocketHub::_MainLoop( float p_fDelta )
{
	pthread_mutex_lock(&m_Mutex);

	// ֪ͨ����
	CCNotificationCenter* nc = CCNotificationCenter::sharedNotificationCenter();

	// ������Ϣ
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecConnectedSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		nc->postNotification( NotificationTCPSocketConnected, s);
	}
	m_vecConnectedSockets.removeAllObjects();

	// �����¼�
	CCARRAY_FOREACH(&m_vecPackets, obj) 
	{
		FKCW_Network_Packet* p = (FKCW_Network_Packet*)obj;
		nc->postNotification( NotificationPacketReceived, p);
	}
	m_vecPackets.removeAllObjects();

	// �Ͽ�������Ϣ
	CCARRAY_FOREACH(&m_vecDisConnectedSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		nc->postNotification( NotificationTCPSocketDisconnected, s);
		m_vecSockets.removeObject(s);
	}
	m_vecDisConnectedSockets.removeAllObjects();

	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// ���һ���׽��ֵ���������
bool FKCW_Network_TCPSocketHub::_AddSocket( FKCW_Network_TCPSocket* p_pSocket )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		if(s->getSocket() == p_pSocket->getSocket()) 
		{
			return false;
		}
	}
	m_vecSockets.addObject(p_pSocket);
	p_pSocket->setHub(this);
	return true;
}
//--------------------------------------------------------------------
// �ṩ��socket���õĺ����������ɹ���������ʱ���øú���֪ͨsocket��������
void FKCW_Network_TCPSocketHub::_OnSocketConnectedThreadSafe( FKCW_Network_TCPSocket* p_pSocket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecConnectedSockets.addObject(p_pSocket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �ṩ��socket���õĺ����������Ͽ�����ʱ���øú���֪ͨsocket��������
void FKCW_Network_TCPSocketHub::_OnSocketDisConnectedThreadSafe( FKCW_Network_TCPSocket* p_pSocket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecDisConnectedSockets.addObject(p_pSocket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �ṩ��socket���õĺ���������׼������һ����ʱ���øú���֪ͨsocket��������
void FKCW_Network_TCPSocketHub::_OnPacketReceivedThreadSafe( FKCW_Network_Packet* p_pPacket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecPackets.addObject(p_pPacket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
FKCW_Network_TCPSocketHub::~FKCW_Network_TCPSocketHub()
{
	// �ͷ���
	pthread_mutex_destroy( &m_Mutex );
}
//--------------------------------------------------------------------
FKCW_Network_TCPSocketHub* FKCW_Network_TCPSocketHub::Create( MULTI_ENCRYPT_FUNC p_pEncryptFunc, MULTI_DECRYPT_FUNC p_pDecryptFunc )
{
	FKCW_Network_TCPSocketHub* h = new FKCW_Network_TCPSocketHub();
	s_EncryptFunc = p_pEncryptFunc;
	s_DecryptFunc = p_pDecryptFunc;
	return (FKCW_Network_TCPSocketHub*)h->autorelease();
}
//--------------------------------------------------------------------
MULTI_ENCRYPT_FUNC FKCW_Network_TCPSocketHub::GetEncryptFunc()
{
	return s_EncryptFunc;
}
//--------------------------------------------------------------------
MULTI_DECRYPT_FUNC FKCW_Network_TCPSocketHub::GetDecryptFunc()
{
	return s_DecryptFunc;
}
//--------------------------------------------------------------------
// �����׽��ֲ���������������
/* ������
p_strHostName Զ����������IPv4 IP��ַ
p_nPort Զ�̶˿�
p_nTag �׽��ֱ�ǩ
p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
p_bIsKeepAlive �Ƿ񱣳ָ��׽��ִ��
*/
FKCW_Network_TCPSocket*	FKCW_Network_TCPSocketHub::CreateSocket(const string& p_strHostName, int p_nPort, int p_nTag,
									 int p_nBlockSec, bool p_bIsKeepAlive )
{
	FKCW_Network_TCPSocket* s = FKCW_Network_TCPSocket::Create(
		p_strHostName, p_nPort, p_nTag, p_nBlockSec, p_bIsKeepAlive );
	if(s)
	{
		_AddSocket(s);
	}
	return s;
}
//--------------------------------------------------------------------
// �Ͽ�һ��socket
void FKCW_Network_TCPSocketHub::Disconnect( int p_nTag )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecPackets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		if(s->getTag() == p_nTag) 
		{
			s->setStop(true);
			break;
		}
	}
}
//--------------------------------------------------------------------
// ֹͣȫ��socket
void FKCW_Network_TCPSocketHub::StopAll()
{
	// �ͷ�socket
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		if(s->isConnected()) 
		{
			s->m_bIsConnected = false;
			s->__CloseSocket();
			CCNotificationCenter::sharedNotificationCenter()->postNotification( NotificationTCPSocketDisconnected, s);
		}
		s->setStop(true);
		s->setHub(NULL);
	}
	m_vecSockets.removeAllObjects();

	// ֹͣ����
	CCScheduler* s = CCDirector::sharedDirector()->getScheduler();
	s->unscheduleSelector(schedule_selector(FKCW_Network_TCPSocketHub::_MainLoop), this);
}
//--------------------------------------------------------------------
// ͨ��tag��ȡsocket����ָ��
FKCW_Network_TCPSocket*	FKCW_Network_TCPSocketHub::GetSocket( int p_nTag )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		if(s->getTag() == p_nTag) 
		{
			return s;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------
// ����һ����Ϣ��
void FKCW_Network_TCPSocketHub::SendPacket( int p_nTag, FKCW_Network_Packet* p_pPacket )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)obj;
		if(s->getTag() == p_nTag)
		{
			s->SendPacket(p_pPacket);
			break;
		}
	}
}
//--------------------------------------------------------------------