//--------------------------------------------------------------------
#include "../Include/FKCW_Network_UDPSocketHub.h"
//--------------------------------------------------------------------
static MULTI_ENCRYPT_FUNC s_EncryptFunc = NULL;
static MULTI_DECRYPT_FUNC s_DecryptFunc = NULL;
//--------------------------------------------------------------------
FKCW_Network_UDPSocketHub::FKCW_Network_UDPSocketHub()
	: m_bIsRawPolicy( false )
{
	pthread_mutex_init( &m_Mutex, NULL );

	CCScheduler* s = CCDirector::sharedDirector()->getScheduler();
	s->scheduleSelector(schedule_selector(FKCW_Network_UDPSocketHub::_MainLoop), this, 0, false);
}
//--------------------------------------------------------------------
// �����׽��֣������ж�д����
void FKCW_Network_UDPSocketHub::_MainLoop( float p_fDelta )
{
	pthread_mutex_lock(&m_Mutex);

	// ��Ϣ֪ͨ����
	CCNotificationCenter* nc = CCNotificationCenter::sharedNotificationCenter();

	// �����¼�
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecConnectedSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		nc->postNotification( NotificationUDPSocketConnected, s );
	}
	m_vecConnectedSockets.removeAllObjects();

	// �����¼�
	CCARRAY_FOREACH(&m_vecPackets, obj) 
	{
		FKCW_Network_UDPSocket* p = (FKCW_Network_UDPSocket*)obj;
		nc->postNotification( NotificationPacketReceived, p );
	}
	m_vecPackets.removeAllObjects();

	// �Ͽ������¼�
	CCARRAY_FOREACH(&m_vecDisConnectedSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		nc->postNotification( NotificationUDPSocketDisconnected, s );
		m_vecSockets.removeObject(s);
	}
	m_vecDisConnectedSockets.removeAllObjects();

	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// ���һ���׽��ֵ���������
bool FKCW_Network_UDPSocketHub::_AddSocket( FKCW_Network_UDPSocket* p_pSocket )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
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
void FKCW_Network_UDPSocketHub::_OnSocketConnectedThreadSafe( FKCW_Network_UDPSocket* p_pSocket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecConnectedSockets.addObject(p_pSocket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �ṩ��socket���õĺ����������Ͽ�����ʱ���øú���֪ͨsocket��������
void FKCW_Network_UDPSocketHub::_OnSocketDisConnectedThreadSafe( FKCW_Network_UDPSocket* p_pSocket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecDisConnectedSockets.addObject(p_pSocket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �ṩ��socket���õĺ���������׼������һ����ʱ���øú���֪ͨsocket��������
void FKCW_Network_UDPSocketHub::_OnPacketReceivedThreadSafe( FKCW_Network_Packet* p_pPacket )
{
	pthread_mutex_lock(&m_Mutex);
	m_vecPackets.addObject(p_pPacket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
FKCW_Network_UDPSocketHub::~FKCW_Network_UDPSocketHub()
{
	pthread_mutex_destroy( &m_Mutex );
}
//--------------------------------------------------------------------
FKCW_Network_UDPSocketHub* FKCW_Network_UDPSocketHub::Create( MULTI_ENCRYPT_FUNC p_pEncryptFunc, MULTI_DECRYPT_FUNC p_pDecryptFunc)
{
	FKCW_Network_UDPSocketHub* p = new FKCW_Network_UDPSocketHub();
	s_EncryptFunc = p_pEncryptFunc;
	s_DecryptFunc = p_pDecryptFunc;
	return ( FKCW_Network_UDPSocketHub* )p->autorelease();
}
//--------------------------------------------------------------------
MULTI_ENCRYPT_FUNC FKCW_Network_UDPSocketHub::GetEncryptFunc()
{
	return s_EncryptFunc;
}
//--------------------------------------------------------------------
MULTI_DECRYPT_FUNC FKCW_Network_UDPSocketHub::GetDecryptFunc()
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
*/
FKCW_Network_UDPSocket*	FKCW_Network_UDPSocketHub::CreateSocket(const string& p_strHostName, int p_nPort, int p_nTag, int p_nBlockSec )
{
	FKCW_Network_UDPSocket* p = FKCW_Network_UDPSocket::Create( p_strHostName, p_nPort, p_nTag, p_nBlockSec );
	if( p )
	{
		_AddSocket( p );
	}
	return p;
}
//--------------------------------------------------------------------
// �Ͽ�һ��socket
void FKCW_Network_UDPSocketHub::Disconnect( int p_nTag )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecPackets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		if(s->getTag() == p_nTag) 
		{
			s->setStop(true);
			break;
		}
	}
}
//--------------------------------------------------------------------
// ֹͣȫ��socket
void FKCW_Network_UDPSocketHub::StopAll()
{
	// �ͷ�socket
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		if(s->isConnected()) 
		{
			s->m_bIsConnected = false;
			s->__CloseSocket();
			CCNotificationCenter::sharedNotificationCenter()->postNotification(NotificationUDPSocketDisconnected, s);
		}
		s->setStop(true);
		s->setHub(NULL);
	}
	m_vecSockets.removeAllObjects();

	// ֹͣ����
	CCScheduler* s = CCDirector::sharedDirector()->getScheduler();
	s->unscheduleSelector(schedule_selector(FKCW_Network_UDPSocketHub::_MainLoop), this);
}
//--------------------------------------------------------------------
// ͨ��tag��ȡsocket����ָ��
FKCW_Network_UDPSocket* FKCW_Network_UDPSocketHub::GetSocket( int p_nTag )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		if(s->getTag() == p_nTag) 
		{
			return s;
		}
	}
	return NULL;
}
//--------------------------------------------------------------------
// ����һ����Ϣ��
void FKCW_Network_UDPSocketHub::SendPacket( int p_nTag, FKCW_Network_Packet* p_pPacket )
{
	CCObject* obj;
	CCARRAY_FOREACH(&m_vecSockets, obj) 
	{
		FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)obj;
		if(s->getTag() == p_nTag) 
		{
			s->SendPacket(p_pPacket);
			break;
		}
	}
}
//--------------------------------------------------------------------