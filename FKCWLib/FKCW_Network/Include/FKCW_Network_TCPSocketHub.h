/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network_TCPSocketHub
	author:		FreeKnight
	
	purpose:	����һ��TCPsocket
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_TCPSocket.h"
#include "FKCW_Network_Packet.h"
#include "FKCW_Network_NetworkCommon.h"
//--------------------------------------------------------------------
// ������һ�������е��׽���
#define NotificationTCPSocketConnected		"NotificationTCPSocketConnected"
// ������һ���Ͽ����׽���
#define NotificationTCPSocketDisconnected	"NotificationTCPSocketDisconnected"
// ������һ����
#define NotificationPacketReceived			"NotificationPacketReceived"
//--------------------------------------------------------------------
// ������socket�Ĺ����������ù���������������������֤ÿ��socketÿ֡���и���
class FKCW_Network_TCPSocketHub : public CCObject
{
	friend class FKCW_Network_TCPSocket;
private:
	pthread_mutex_t			m_Mutex;					// �߳��ٽ�����
	CCArray					m_vecConnectedSockets;		// �����е��׽��ֶ���
	CCArray					m_vecDisConnectedSockets;	// �Ͽ����׽��ֶ���
	CCArray					m_vecPackets;				// ��Ϣ������
	CC_SYNTHESIZE_PASS_BY_REF(CCArray, m_vecSockets, Sockets);		// �׽��ֶ���
	CC_SYNTHESIZE_BOOL(m_bIsRawPolicy, RawPolicy);		// ���Ϊtrue�����ʾ�յ��İ�������Ԥ��İ�ͷ�����ɿ��������н�������
protected:
	FKCW_Network_TCPSocketHub();

	// �����׽��֣������ж�д����
	void			_MainLoop( float p_fDelta );
	// ���һ���׽��ֵ���������
	bool			_AddSocket( FKCW_Network_TCPSocket* p_pSocket );
	// �ṩ��socket���õĺ����������ɹ���������ʱ���øú���֪ͨsocket��������
	void			_OnSocketConnectedThreadSafe( FKCW_Network_TCPSocket* p_pSocket );
	// �ṩ��socket���õĺ����������Ͽ�����ʱ���øú���֪ͨsocket��������
	void			_OnSocketDisConnectedThreadSafe( FKCW_Network_TCPSocket* p_pSocket );
	// �ṩ��socket���õĺ���������׼������һ����ʱ���øú���֪ͨsocket��������
	void			_OnPacketReceivedThreadSafe( FKCW_Network_Packet* p_pPacket );

public:
	virtual ~FKCW_Network_TCPSocketHub();
	static FKCW_Network_TCPSocketHub* Create( MULTI_ENCRYPT_FUNC p_pEncryptFunc = NULL,
		MULTI_DECRYPT_FUNC p_pDecryptFunc = NULL );
	static MULTI_ENCRYPT_FUNC		GetEncryptFunc();
	static MULTI_DECRYPT_FUNC		GetDecryptFunc();

	// �����׽��ֲ���������������
	/* ������
			p_strHostName Զ����������IPv4 IP��ַ
			p_nPort Զ�̶˿�
			p_nTag �׽��ֱ�ǩ
			p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
			p_bIsKeepAlive �Ƿ񱣳ָ��׽��ִ��
	*/
	FKCW_Network_TCPSocket*	CreateSocket(const string& p_strHostName, int p_nPort, int p_nTag,
		int p_nBlockSec = SocketDefaultTimeout, bool p_bIsKeepAlive = false );
	// �Ͽ�һ��socket
	void			Disconnect( int p_nTag );
	// ֹͣȫ��socket
	void			StopAll();
	// ͨ��tag��ȡsocket����ָ��
	FKCW_Network_TCPSocket*		GetSocket( int p_nTag );
	// ����һ����Ϣ��
	void			SendPacket( int p_nTag, FKCW_Network_Packet* p_pPacket );
};