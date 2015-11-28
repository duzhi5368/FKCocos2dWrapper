#ifndef _NET_SERVER_OBJECT_H_
#define _NET_SERVER_OBJECT_H_
//-------------------------------------------------------------------------
#include "FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class NetServerObject;
//-------------------------------------------------------------------------
struct NetServerParams
{
	NetServerObject* netServerObject;
	short post;
	string ip;
};
//-------------------------------------------------------------------------
DWORD WINAPI threadFunc(LPVOID pM);
//-------------------------------------------------------------------------
//ע�� close������رյ�ǰ���ӡ���ǰ������delete�����ʵ��
//Ҫ����NetServerObject�������࣬close������
class NetServerObject
{
public:
	NetServerObject();
	virtual ~NetServerObject();
public:
	// �յ���Ϣ���Ļص�
	virtual void onMessageReceived(FKCW_SimpleNet_Buffer& oBuffer) = 0;
	// ���ӳɹ�ʱ�Ļص�
	virtual void onConnected() = 0;
	// ���ӹر�ʱ�Ļص�
	virtual void onDisconnected() = 0;
	// ���ӽ���ʱ�Ļص�
	virtual void onConnectedEnded() = 0;
	// ���ӳ���Ļص�
	virtual void onExceptionCaught() = 0;

	// ��������״̬
	static void setConnected(bool isConnect);
	// �õ�����״̬
	static bool isConnected();

	static SOCKET s_sockConn;			// ��ǰ���ӵ�Socket
	static SOCKET s_serverSocket;		// ������socket
	static bool m_isClose;				// �Ƿ��Ѿ��ֶ����ùر�����
public:
	// ��ʼ��
	virtual bool init();
	// ���ü���IP
	virtual void setListenPost(short post);
	// ���ü���IP
	virtual void setListenIp(const char* ip);
	// ����Ŀ���ַ
	virtual void listen();
	// �رյ�ǰ����
	virtual void close();
	// ������Ϣ����Ŀ��
	virtual void send(FKCW_SimpleNet_Buffer* pBuffer);
protected:
	static bool m_isConnect;		//��ǰ�Ƿ��������
	short		m_post;
	string		m_ip;
	SOCKET		m_ServerSocket;		//�����Socket
};
//-------------------------------------------------------------------------
#endif