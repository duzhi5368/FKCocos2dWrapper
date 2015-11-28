//*************************************************************************
//	��������:	2014-11-15
//	�ļ�����:	FKCW_SimpleNet_NetObject.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SimpleNet_Macro.h"
#include "FKCW_SimpleNet_Buffer.h"
#include "FKCW_SimpleNet_InetAddress.h"
#include "FKCW_SimpleNet_TCPSocket.h"
//-------------------------------------------------------------------------
// ������Ҫ���̳У��̳�֮���ʵ�־��庯���Ϳ��Ը����������Ӻ���Ϣ����
class FKCW_SimpleNet_NetObject : public CCObject
{
public:
	FKCW_SimpleNet_NetObject();
	virtual ~FKCW_SimpleNet_NetObject();

public:
	// �յ���Ϣ���Ļص�
	virtual void onMessageReceived(FKCW_SimpleNet_Buffer& oBuffer) = 0;
	// ���ӳɹ�ʱ�Ļص�
	virtual void onConnected() = 0;
	// ���ӳ�ʱʱ�Ļص�
	virtual void onConnectTimeout() = 0;
	// ����ʧ��ʱ�Ļص�
	virtual void onDisconnected() = 0;
	// ����ʱ�Ļص�
	virtual void onExceptionCaught(ENUM_SocketStatus eStatus) = 0;

public:
	// ��������Ŀ���ַ
	void setInetAddress(const FKCW_SimpleNet_InetAddress& oInetAddress);
	// ��ȡ����Ŀ���ַ
	const FKCW_SimpleNet_InetAddress& getInetAddress() const;
	// �������ӳ�ʱʱ��
	void setSoTimeout(float fSoTimeout);
	// ��ȡ���ӳ�ʱʱ��
	float getSoTimeout() const;
	// ������Ϣ����Ŀ��
	void send(char* pBuffer, unsigned int uLen);
	// ������Ϣ����Ŀ��
	void send(FKCW_SimpleNet_Buffer* pBuffer);
	// ��鵱ǰ�Ƿ񱣳�����
	bool isConnected();
	// �رյ�ǰ����
	void close();
	// ����Ŀ���ַ
	bool connect();
	// �Ͽ���ǰ����
	void disconnect();
	// ��ȡ��ǰ����״̬
	ENUM_SocketStatus getSocketStatus(){ return m_eStatus; }

private:
	// ÿ֡��ȡ����
	bool runRead();
	// ÿ֡����Ƿ������ݷ��ͣ���������з���
	bool runWrite();
	// ÿ֡�ص����º���
	void runSchedule(float dt);
	// ע��֡�ص�����
	void registerScheduler();
	// ע��֡�ص�����
	void unregisterScheduler();

private:
	// ������Ϣ������
	struct SSendBuffer
	{
		char* pBuffer;       // ������Ϣ
		int nOffset;         // ��������ƫ��
		int nLength;         // ���ݳ�
	};
	
private:
	bool							m_bRunSchedule;
	float							m_fConnectingDuration;
	float							m_fSoTimeout;
	std::list<SSendBuffer>			m_lSendBuffers;
	FKCW_SimpleNet_Buffer			m_oReadBuffer;
	FKCW_SimpleNet_InetAddress		m_oInetAddress;
	FKCW_SimpleNet_TCPSocket		m_oSocket;
	char							m_pReadBuffer[SOCKET_READ_BUFFER_SIZE];
	ENUM_SocketStatus				m_eStatus;
};