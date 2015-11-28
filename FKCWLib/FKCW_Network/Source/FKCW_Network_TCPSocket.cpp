//--------------------------------------------------------------------
#include "../Include/FKCW_Network_TCPSocket.h"
#include "../Include/FKCW_Network_NetworkCommon.h"
#include "../Include/FKCW_Network_TCPSocketHub.h"
//--------------------------------------------------------------------
#pragma warning( disable : 4996 )
#pragma warning( disable : 4013 )
//--------------------------------------------------------------------
FKCW_Network_TCPSocket::FKCW_Network_TCPSocket()
	: m_nSocket( SocketInvalid )
	, m_bIsConnected( false )
	, m_bIsStop( false )
{
	pthread_mutex_init(&m_Mutex, NULL);
	memset(m_szInBuf, 0, sizeof(m_szInBuf));
}
//--------------------------------------------------------------------
FKCW_Network_TCPSocket::~FKCW_Network_TCPSocket()
{
	__CloseSocket();
	pthread_mutex_destroy(&m_Mutex);
}
//--------------------------------------------------------------------
// �����׽���ʵ�� 
// �����μ� _Init()
FKCW_Network_TCPSocket* FKCW_Network_TCPSocket::Create( const string& p_strHostName, int p_nPort,
			int p_nTag, int p_nBlockSec, bool p_bIsKeepAlive )
{
	FKCW_Network_TCPSocket* s = new FKCW_Network_TCPSocket();
	if(s->_Init(p_strHostName, p_nPort, p_nTag, p_nBlockSec, p_bIsKeepAlive)) 
	{
		return (FKCW_Network_TCPSocket*)s->autorelease();
	}

	s->release();
	return NULL;
}
//--------------------------------------------------------------------
// ���һ���������Ͷ���
void FKCW_Network_TCPSocket::SendPacket( FKCW_Network_Packet* p_pPacket )
{
	pthread_mutex_lock(&m_Mutex);
	m_arrSendQueue.addObject((CCObject*)p_pPacket);
	pthread_mutex_unlock(&m_Mutex);
}
//--------------------------------------------------------------------
// �ж��׽����Ƿ���
// ����ֵ��true��ʾsocket��Ч��false��ʾsocket�ѹر�
bool FKCW_Network_TCPSocket::IsHasAvailable()
{
	if (m_nSocket == SocketInvalid) 
	{
		return false;
	}

	char buf[1];
	ssize_t ret = recv(m_nSocket, buf, 1, MSG_PEEK);
	if(ret == 0) 
	{
		__CloseSocket();
		return false;
	} 
	else if(ret < 0) 
	{
		if (__HasError()) 
		{
			__CloseSocket();
			return false;
		} else 
		{
			return true;
		}
	} 
	else 
	{
		return true;
	}
}
//--------------------------------------------------------------------
// ����������ȴ�ֱ��socket���ӳɹ����߳�ʱ
void* FKCW_Network_TCPSocket::__TcpThreadEntry( void* p_pArg )
{
	// �������ͷų�
	CCThread thread;
	thread.createAutoreleasePool();

	// ��ȡ���߳�������socket
	FKCW_Network_TCPSocket* s = (FKCW_Network_TCPSocket*)p_pArg;

	// ������ַ����
	sockaddr_in addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(s->m_nPort);
	addr_in.sin_addr.s_addr = inet_addr( s->m_szHostname.c_str() );

	// ��������
	// ���ʧ����ر�����;���ɹ�����ָ��ʱ����select
	int nRet = connect(s->m_nSocket, (sockaddr*)&addr_in, sizeof(addr_in));
	if( nRet == SocketError && s->__HasError() )
	{
#if( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
		int nError = WSAGetLastError();
		if( nError ==  WSAEWOULDBLOCK )
		{
			// wait....
		}
		else
		{
			s->__CloseSocket();
		}
#endif
#if( CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
		if( errno == EINPROGRESS )
		{
			// wait....
		}
		else
		{
			s->__CloseSocket();
		}
#endif
	}
	else
	{
		// ��socket�رգ��ӳ�500ms
		struct linger so_linger;
		so_linger.l_onoff = 1;
		so_linger.l_linger = 500;
		setsockopt(s->m_nSocket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

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
		if (ret < 0) 
		{
			s->__CloseSocket();
		}
		else 
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

	// ��дѭ��
	FKCW_Network_Packet* p = NULL;
	ssize_t sent = 0;
	while(!s->m_bIsStop && s->m_bIsConnected && s->getSocket() != SocketInvalid)
	{
		s->__RectFromSocket();
		if(s->m_nInBufLen > 0) 
		{
			FKCW_Network_Packet* p = NULL;
			if(s->m_pHub->isRawPolicy()) 
			{
				p = FKCW_Network_Packet::CreateRawPacket(s->m_szInBuf, s->m_nInBufLen);
			} 
			else 
			{
				p = FKCW_Network_Packet::CreateStandardPacket(s->m_szInBuf, s->m_nInBufLen);
			}
			s->__CompactInBuf(p->getPacketLength());
			if(s->m_pHub)
			{
				s->m_pHub->_OnPacketReceivedThreadSafe(p);
			}
		}

		// ��ȡ��Ҫ���͵���Ϣ��
		if(!p && s->m_arrSendQueue.count() > 0) 
		{
			pthread_mutex_lock(&s->m_Mutex);
			p = (FKCW_Network_Packet*)s->m_arrSendQueue.objectAtIndex(0);
			CC_SAFE_RETAIN(p);
			s->m_arrSendQueue.removeObjectAtIndex(0);
			sent = 0;
			pthread_mutex_unlock(&s->m_Mutex);
		}

		// ���͵�ǰ��
		if(p) 
		{
			ssize_t outsize = send(s->m_nSocket, p->getBuffer() + sent, p->getPacketLength() - sent, 0);
			if(outsize > 0) 
			{
				// �ƶ�ָ��
				sent += outsize;

				if (sent >= static_cast<ssize_t>(p->getPacketLength())) 
				{
					CC_SAFE_RELEASE(p);
					p = NULL;
				}
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

	// �Ͽ�����֪ͨ��������
	if(s->m_bIsConnected)
	{
		if(s->m_pHub)
			s->m_pHub->_OnSocketDisConnectedThreadSafe(s);
		s->m_bIsConnected = false;
	}

	// �ͷ�socket
	s->autorelease();

	// �˳�
	pthread_exit(NULL);

	return NULL;
}
//--------------------------------------------------------------------
// ��socket������Ϣֱ��û�����ݣ����߻��������ˣ����߳�����ĳ�ִ���
bool FKCW_Network_TCPSocket::__RectFromSocket()
{
	// �������
	if (m_nInBufLen >= SocketInputBufferDefaultSize || m_nSocket == SocketInvalid) {
		return false;
	}

	int savelen = SocketInputBufferDefaultSize - m_nInBufLen;

	// ����������β
	int savepos = m_nInBufLen;
	ssize_t inlen = recv(m_nSocket, m_szInBuf + savepos, savelen, 0);
	if(inlen > 0) 
	{
		m_nInBufLen += inlen;
		if (m_nInBufLen > SocketInputBufferDefaultSize) 
		{
			return false;
		}
	} 
	else if(inlen == 0) 
	{
		__CloseSocket();
		return false;
	} 
	else 
	{
		if (__HasError()) 
		{
			__CloseSocket();
			return false;
		}
	}

	return true;
}
//--------------------------------------------------------------------
// �ж��Ƿ�����˴���
bool FKCW_Network_TCPSocket::__HasError()
{
	int err = errno;
	if(err != EINPROGRESS && err != EAGAIN) {
		return true;
	}

	return false;
}
//--------------------------------------------------------------------
// �ر��׽���
void FKCW_Network_TCPSocket::__CloseSocket()
{
	if( m_nSocket != SocketInvalid )
	{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
		closesocket( m_nSocket );
#else
		close( m_nSocket );
#endif
		m_nSocket = SocketInvalid;
	}
}
//--------------------------------------------------------------------
// ���������ڵ���Ч���������������ײ�
void FKCW_Network_TCPSocket::__CompactInBuf( int p_nConsumed )
{
	if( p_nConsumed < m_nInBufLen )
	{
		memmove(m_szInBuf, m_szInBuf + p_nConsumed, m_nInBufLen - p_nConsumed);
		m_nInBufLen -= p_nConsumed;
	}
	else
	{
		m_nInBufLen = 0;
	}
}
//--------------------------------------------------------------------
// ��ʼ���׽���
/* ������
p_strHostName Զ����������IPv4 IP��ַ
p_nPort Զ�̶˿�
p_nTag �׽��ֱ�ǩ
p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
p_bIsKeepAlive �Ƿ񱣳ָ��׽��ִ��
*/

bool FKCW_Network_TCPSocket::_Init( const string& p_strHostName, 
		int p_nPort, int p_nTag, int p_nBlockSec, bool p_bIsKeepAlive )
{
	if( p_strHostName.empty() || p_strHostName.length() > 15) 
	{
		return false;
	}

	// ����TCPSocket
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	m_nSocket = socket(AF_INET, SOCK_STREAM, 0);
#else
	m_nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif
	if(m_nSocket == SocketInvalid) 
	{
		__CloseSocket();
		return false;
	}

	// ���汾�߳�
	if(p_bIsKeepAlive) 
	{
		int optVal = 1;
		if(setsockopt(m_nSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&optVal, sizeof(optVal)))
		{
			__CloseSocket();
			return false;
		}
	}

	// ��֤Host��
	in_addr_t serveraddr = inet_addr(p_strHostName.c_str());
	if(serveraddr == INADDR_NONE) 
	{
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

	// ���沿����Ϣ
	m_szHostname = p_strHostName;
	m_nPort = p_nPort;
	m_nTag = p_nTag;
	m_nBlockSec = p_nBlockSec;

	// ���û�����
	m_nInBufLen = 0;

	// ����һ���߳��������socket����
	CC_SAFE_RETAIN(this);
	pthread_t thread;
	pthread_create(&thread, NULL, __TcpThreadEntry, (void*)this);
	pthread_detach(thread);

	return true;
}
//--------------------------------------------------------------------