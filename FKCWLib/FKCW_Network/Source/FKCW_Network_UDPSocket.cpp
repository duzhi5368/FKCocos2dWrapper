//--------------------------------------------------------------------
#include "../Include/FKCW_Network_UDPSocket.h"
#include "../Include/FKCW_Network_UDPSocketHub.h"
//--------------------------------------------------------------------
// ����������ȴ�ֱ��socket���ӳɹ����߳�ʱ
void* FKCW_Network_UDPSocket::__UdpThreadEntry( void* p_pArg )
{
	// �������ͷų�
	CCThread thread;
	thread.createAutoreleasePool();

	// ��ȡsocket
	FKCW_Network_UDPSocket* s = (FKCW_Network_UDPSocket*)p_pArg;

	// �ͻ��˵�ַ
	sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = INADDR_ANY;
	my_addr.sin_port = 0;

	// ��
	int nRet = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	bind((SOCKET)s->m_nSocket, (sockaddr*)&my_addr, sizeof(my_addr));
	nRet = WSAGetLastError();
#else
	bind((unsigned int)s->m_nSocket, (sockaddr*)&my_addr, sizeof(my_addr));
	nRet = errno;
#endif
	if( nRet != 0 && s->__HasError()) 
	{
		s->__CloseSocket();
	} 
	else 
	{
		// select
		timeval timeout;
		timeout.tv_sec = s->m_nBlockSec;
		timeout.tv_usec = 0;
		fd_set writeset, exceptset;
		FD_ZERO(&writeset);
		FD_ZERO(&exceptset);
		FD_SET(s->m_nSocket, &writeset);
		FD_SET(s->m_nSocket, &exceptset);
		int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
		if (ret == 0 || ret < 0) 
		{
			s->__CloseSocket();
		} else 
		{
			ret = FD_ISSET(s->m_nSocket, &exceptset);
			if(ret) 
			{
				s->__CloseSocket();
			} 
			else 
			{
				s->m_bIsConnected = true;
				if(s->m_pHub)
				{
					s->m_pHub->_OnSocketConnectedThreadSafe(s);
				}
			}
		}
	}

	// ��socket�رգ��ӳ�500ms
	struct linger so_linger;
	so_linger.l_onoff = 1;
	so_linger.l_linger = 500;
	setsockopt(s->m_nSocket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

	// ��дѭ��
	FKCW_Network_Packet* p = NULL;
	while(!s->m_bIsStop && s->m_bIsConnected && s->getSocket() != SocketInvalid) 
	{
		s->__RecvFromSocket();
		if(s->m_nInBufLen > 0) 
		{
			FKCW_Network_Packet* p = NULL;
			if(s->m_pHub) 
			{
				if(s->m_pHub->isRawPolicy()) 
				{
					p = FKCW_Network_Packet::CreateRawPacket(s->m_szInBuf, s->m_nInBufLen);
				} 
				else 
				{
					p = FKCW_Network_Packet::CreateStandardPacket(s->m_szInBuf, s->m_nInBufLen);
				}
				s->m_pHub->_OnPacketReceivedThreadSafe(p);
			}
		}

		// ��ȡ�������͵���Ϣ��
		if(!p && s->m_arrSendQueue.count() > 0) 
		{
			pthread_mutex_lock(&s->m_Mutex);
			p = (FKCW_Network_Packet*)s->m_arrSendQueue.objectAtIndex(0);
			CC_SAFE_RETAIN(p);
			s->m_arrSendQueue.removeObjectAtIndex(0);
			pthread_mutex_unlock(&s->m_Mutex);
		}

		// ���͵�ǰ��Ϣ��
		if(p) 
		{
			ssize_t sent = sendto(s->m_nSocket, p->getBuffer(), p->getPacketLength(), 0, (sockaddr*)&s->m_tagSrvAddr, sizeof(s->m_tagSrvAddr));
			if(sent >= static_cast<ssize_t>(p->getPacketLength())) 
			{
				CC_SAFE_RELEASE(p);
				p = NULL;
			} 
			else 
			{
				if (s->__HasError()) 
				{
					s->__CloseSocket();
				}
			}
		}
	}

	// ��������
	if(s->m_bIsConnected) 
	{
		if(s->m_pHub)
			s->m_pHub->_OnSocketDisConnectedThreadSafe(s);
		s->m_bIsConnected = false;
	}

	s->autorelease();
	pthread_exit(NULL);

	return NULL;
}
//--------------------------------------------------------------------
// ��socket������Ϣֱ��û�����ݣ����߻��������ˣ����߳�����ĳ�ִ���
void FKCW_Network_UDPSocket::__RecvFromSocket()
{
	socklen_t len = sizeof(m_tagSrvAddr);
	m_nInBufLen = recvfrom( m_nSocket, m_szInBuf, SocketInputBufferDefaultSize, 0, (sockaddr*)&m_tagSrvAddr, &len);
}
//--------------------------------------------------------------------
// �ж��Ƿ�����˴���
bool FKCW_Network_UDPSocket::__HasError()
{
	int err = errno;
	if(err != EINPROGRESS && err != EAGAIN) {
		return true;
	}

	return false;
}
//--------------------------------------------------------------------
// �ر��׽���
void FKCW_Network_UDPSocket::__CloseSocket()
{
	if(m_nSocket != SocketInvalid) 
	{

#pragma warning ( disable: 4996 )
		::close(m_nSocket);
#pragma warning ( default : 4996 )
		
		m_nSocket = SocketInvalid; 
	}
}
//--------------------------------------------------------------------
// ��ʼ���׽���
/* ������
		p_strHostName Զ����������IPv4 IP��ַ
		p_nPort Զ�̶˿�
		p_nTag �׽��ֱ�ǩ
		p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
*/
bool FKCW_Network_UDPSocket::_Init( const string& p_strHostName, int p_nPort, int p_nTag, int p_nBlockSec )
{
	if(p_strHostName.empty() || p_strHostName.length() > 15) 
	{
		return false;
	}

	// ����TCP����
	m_nSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(m_nSocket == SocketInvalid) {
		__CloseSocket();
		return false;
	}

	// ���÷�����ģʽ
	unsigned long flags;
	flags = 1;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	ioctlsocket( m_nSocket, FIONBIO, &flags);
#else
	fcntl(m_nSocket, F_SETFL, O_NONBLOCK);
#endif

	// ��֤Host��
	in_addr_t serveraddr = inet_addr(p_strHostName.c_str());
	if(serveraddr == INADDR_NONE) 
	{
		__CloseSocket();
		return false;
	}

	// ��������ַ
	memset((void *)&m_tagSrvAddr, 0, sizeof(m_tagSrvAddr));
	m_tagSrvAddr.sin_family = AF_INET;
	m_tagSrvAddr.sin_port = htons(p_nPort);
	m_tagSrvAddr.sin_addr.s_addr = serveraddr;

	// ������Ϣ
	m_szHostname = p_strHostName;
	m_nPort = p_nPort;
	m_nTag = p_nTag;
	m_nBlockSec = p_nBlockSec;
	m_nInBufLen = 0;

	// ����һ���߳��������socket����
	CC_SAFE_RETAIN(this);
	pthread_t thread;
	pthread_create(&thread, NULL, __UdpThreadEntry, (void*)this);
	pthread_detach(thread);

	return true;
}
//--------------------------------------------------------------------
FKCW_Network_UDPSocket::FKCW_Network_UDPSocket()
	: m_nSocket( SocketInvalid )
	, m_nTag( -1 )
{
	pthread_mutex_init(&m_Mutex, NULL);
}
//--------------------------------------------------------------------
FKCW_Network_UDPSocket::~FKCW_Network_UDPSocket()
{
	pthread_mutex_destroy(&m_Mutex);
}
//--------------------------------------------------------------------
// �����׽���ʵ��
// �����μ� _Init()
FKCW_Network_UDPSocket* FKCW_Network_UDPSocket::Create( const string& p_strHostName, int p_nPort, int p_nTag, int p_nBlockSec )
{
	FKCW_Network_UDPSocket* s = new FKCW_Network_UDPSocket();
	if(s->_Init(p_strHostName, p_nPort, p_nTag)) 
	{
		return (FKCW_Network_UDPSocket*)s->autorelease();
	}

	s->release();
	return NULL;
}
//--------------------------------------------------------------------
// ���һ���������Ͷ���
void FKCW_Network_UDPSocket::SendPacket( FKCW_Network_Packet* p_pPacket )
{
	pthread_mutex_lock(&m_Mutex);
	m_arrSendQueue.addObject(p_pPacket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------