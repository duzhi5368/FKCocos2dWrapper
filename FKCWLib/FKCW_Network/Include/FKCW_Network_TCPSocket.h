/********************************************************************
	created:	2014/10/31
	file base:	FKCW_Network_TCPSocket
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_NetworkCommon.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
//--------------------------------------------------------------------
class FKCW_Network_TCPSocketHub;
class FKCW_Network_Packet;
//--------------------------------------------------------------------
class FKCW_Network_TCPSocket : public CCObject
{
	friend class FKCW_Network_TCPSocketHub;
private:
	char			m_szInBuf[SocketInputBufferDefaultSize];				// ��ȡ��״����
	int				m_nInBufLen;											// ��ȡ�����е���Ч���ݳ���
	int				m_nBlockSec;											// �ȴ�socket���ӵ�����ʱ��
	pthread_mutex_t	m_Mutex;												// �̻߳�����
	CC_SYNTHESIZE_READONLY(int, m_nSocket, Socket);							// socket���
	CC_SYNTHESIZE_READONLY(int, m_nTag, Tag);								// socket��ǩ
	CC_SYNTHESIZE(FKCW_Network_TCPSocketHub*, m_pHub, Hub);					// ��������ָ��
	CC_SYNTHESIZE_READONLY_BOOL(m_bIsConnected, Connected);					// �Ƿ�����
	CC_SYNTHESIZE_BOOL(m_bIsStop, Stop);									// �Ƿ�Ͽ�
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, m_szHostname, Hostname);		// ��������
	CC_SYNTHESIZE_READONLY(int, m_nPort, Port);								// �������˿�
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(CCArray, m_arrSendQueue, SendQueue);	// ���Ͷ���
private:
	// ����������ȴ�ֱ��socket���ӳɹ����߳�ʱ
	static void*	__TcpThreadEntry( void* p_pArg );
	// ��socket������Ϣֱ��û�����ݣ����߻��������ˣ����߳�����ĳ�ִ���
	bool			__RectFromSocket();
	// �ж��Ƿ�����˴���
	bool			__HasError();
	// �ر��׽���
	void			__CloseSocket();
	// ���������ڵ���Ч���������������ײ�
	void			__CompactInBuf( int p_nConsumed );
protected:
	// ��ʼ���׽���
	/* ������
			p_strHostName Զ����������IPv4 IP��ַ
			p_nPort Զ�̶˿�
			p_nTag �׽��ֱ�ǩ
			p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
			p_bIsKeepAlive �Ƿ񱣳ָ��׽��ִ��
	*/

	bool			_Init( const string& p_strHostName, int p_nPort, int p_nTag = -1,
		int p_nBlockSec = SocketDefaultTimeout, bool p_bIsKeepAlive = false );
public:
	FKCW_Network_TCPSocket();
	virtual ~FKCW_Network_TCPSocket();

	// �����׽���ʵ�� 
	// �����μ� _Init()
	static FKCW_Network_TCPSocket* Create( const string& p_strHostName, int p_nPort, int p_nTag = -1,
		int p_nBlockSec = SocketDefaultTimeout, bool p_bIsKeepAlive = false );
	// ���һ���������Ͷ���
	void			SendPacket( FKCW_Network_Packet* p_pPacket );
	// �ж��׽����Ƿ���
	// ����ֵ��true��ʾsocket��Ч��false��ʾsocket�ѹر�
	bool			IsHasAvailable();
};