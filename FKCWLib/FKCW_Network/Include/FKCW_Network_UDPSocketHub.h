/********************************************************************
	created:	2014/11/01
	file base:	FKCW_Network_UDPSocketHub
	author:		FreeKnight
	
	purpose:	����һ��UDPsocket
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Network_Macros.h"
#include "FKCW_Network_UDPSocket.h"
#include "FKCW_Network_Packet.h"
#include "FKCW_Network_NetworkCommon.h"
//--------------------------------------------------------------------
// ������һ�������е��׽���
#define NotificationUDPSocketConnected		"NotificationUDPSocketConnected"
// ������һ���Ͽ����׽���
#define NotificationUDPSocketDisconnected	"NotificationUDPSocketDisconnected"
// ������һ����
#define NotificationPacketReceived			"NotificationPacketReceived"
//--------------------------------------------------------------------
// ������socket�Ĺ����������ù���������������������֤ÿ��socketÿ֡���и���
class FKCW_Network_UDPSocketHub : public CCObject
{
	friend class FKCW_Network_UDPSocket;
private:
	pthread_mutex_t			m_Mutex;					// �߳��ٽ�����
	CCArray					m_vecConnectedSockets;		// �����е��׽��ֶ���
	CCArray					m_vecDisConnectedSockets;	// �Ͽ����׽��ֶ���
	CCArray					m_vecPackets;				// ��Ϣ������
	CC_SYNTHESIZE_PASS_BY_REF(CCArray, m_vecSockets, Sockets);		// �׽��ֶ���
	CC_SYNTHESIZE_BOOL(m_bIsRawPolicy, RawPolicy);		// ���Ϊtrue�����ʾ�յ��İ�������Ԥ��İ�ͷ�����ɿ��������н�������
protected:
	FKCW_Network_UDPSocketHub();

	// �����׽��֣������ж�д����
	void			_MainLoop( float p_fDelta );
	// ���һ���׽��ֵ���������
	bool			_AddSocket( FKCW_Network_UDPSocket* p_pSocket );
	// �ṩ��socket���õĺ����������ɹ���������ʱ���øú���֪ͨsocket��������
	void			_OnSocketConnectedThreadSafe( FKCW_Network_UDPSocket* p_pSocket );
	// �ṩ��socket���õĺ����������Ͽ�����ʱ���øú���֪ͨsocket��������
	void			_OnSocketDisConnectedThreadSafe( FKCW_Network_UDPSocket* p_pSocket );
	// �ṩ��socket���õĺ���������׼������һ����ʱ���øú���֪ͨsocket��������
	void			_OnPacketReceivedThreadSafe( FKCW_Network_Packet* p_pPacket );
public:
	virtual ~FKCW_Network_UDPSocketHub();
	static FKCW_Network_UDPSocketHub* Create( MULTI_ENCRYPT_FUNC p_pEncryptFunc = NULL,
		MULTI_DECRYPT_FUNC p_pDecryptFunc = NULL );
	static MULTI_ENCRYPT_FUNC		GetEncryptFunc();
	static MULTI_DECRYPT_FUNC		GetDecryptFunc();

	// �����׽��ֲ���������������
	/* ������
			p_strHostName Զ����������IPv4 IP��ַ
			p_nPort Զ�̶˿�
			p_nTag �׽��ֱ�ǩ
			p_nBlockSec �׽�������ʱ�ĵȴ�����ʱ�䣬0��ʾ���޵ȴ�
	*/
	FKCW_Network_UDPSocket*	CreateSocket(const string& p_strHostName, int p_nPort, int p_nTag,
		int p_nBlockSec = SocketDefaultTimeout );
	// �Ͽ�һ��socket
	void			Disconnect( int p_nTag );
	// ֹͣȫ��socket
	void			StopAll();
	// ͨ��tag��ȡsocket����ָ��
	FKCW_Network_UDPSocket*		GetSocket( int p_nTag );
	// ����һ����Ϣ��
	void			SendPacket( int p_nTag, FKCW_Network_Packet* p_pPacket );
};
