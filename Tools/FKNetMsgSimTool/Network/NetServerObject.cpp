#include "NetServerObject.h"

NetServerObject::NetServerObject()
{
	init();
}

bool NetServerObject::init()
{
	m_isConnect = false;
	m_isClose = false;

	WSADATA wsad;
	WORD wVersionRequested; 
	wVersionRequested = MAKEWORD( 2, 0 );  
	if (WSAStartup(wVersionRequested , &wsad)!=0) 
	{
		return false;
	}
	return true;
}
//���ü����˿�
void NetServerObject::setListenPost( short post )
{
	m_post = post;
}

void NetServerObject::setListenIp(const char* ip)
{
	m_ip = ip;
}

void NetServerObject::close()
{
	::closesocket(s_sockConn);		//�رյ�ǰ����
	::closesocket(s_serverSocket);	//�رշ���������
	m_isClose = true;
}

void NetServerObject::send( FKCW_SimpleNet_Buffer* pBuffer )
{
	if(s_sockConn != NULL)
		::send(s_sockConn, pBuffer->data(), pBuffer->length(), 0);
	else
		FKLOG("m_sockConn is null");
}

DWORD WINAPI threadFunc( LPVOID pM )
{
	NetServerParams params = *(NetServerParams*)pM;
	delete pM;

	do
	{
		bool isContinue = true;
	
		//���������SOCKET
		NetServerObject::s_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

		//���ü�����ַ�Ͷ˿�
		SOCKADDR_IN serverAddr;
		ZeroMemory((char *)&serverAddr,sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(params.post);					//���ؼ����˿�
		serverAddr.sin_addr.S_un.S_addr = inet_addr(params.ip.c_str());
		//serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		
		//�󶨼���SOCKET//
		::bind(NetServerObject::s_serverSocket,(struct sockaddr *)&serverAddr, sizeof(serverAddr));

		int error = listen(NetServerObject::s_serverSocket, 1);
		if (error != SOCKET_ERROR)			//����SCOKET������
		{
			SOCKADDR_IN addrClient;
			int len = sizeof(SOCKADDR);

			//��ʼ�������� 
			NetServerObject::s_sockConn = accept(NetServerObject::s_serverSocket, (SOCKADDR*)&addrClient, &len);

			params.netServerObject->onConnected();	//���ӳɹ��ص�

			while (isContinue)
			{
				char recvBuf[4096];
				int erro = recv(NetServerObject::s_sockConn, recvBuf, 4096, 0);	//�ȴ��ͻ�����Ϣ
				if (erro < 0)
				{
					params.netServerObject->onExceptionCaught();	//���ӳ���ص�
					isContinue = false;
					break;
				}
				else if(erro == 0)
				{
					params.netServerObject->onDisconnected();	//���ӹر�
					isContinue = false;
					break;
				}
				else
				{
					FKCW_SimpleNet_Buffer buffer(recvBuf, 4096);
					params.netServerObject->onMessageReceived(buffer);	//�õ���Ϣ�ص�
				}
			}
		}
		else
			MessageBox(NULL, L"����˶˿ڱ�ռ��/IP����", L"", 1);

		params.netServerObject->onConnectedEnded();	//���ӽ����ص�
		
		closesocket(NetServerObject::s_sockConn);
		closesocket(NetServerObject::s_serverSocket);

	} while (!NetServerObject::m_isClose);

	WSACleanup();	//���WSAD

	params.netServerObject->setConnected(true);	//����������ɱ�ʶ

	delete params.netServerObject;
	params.netServerObject = NULL;

	return 0;
}

void NetServerObject::listen()
{
	NetServerParams* params = new NetServerParams;
	params->post = m_post;
	params->netServerObject = this;
	params->ip = m_ip;

	HANDLE buf = CreateThread(NULL, 0, threadFunc, params, 0, NULL);
}

void NetServerObject::setConnected( bool isConnect )
{
	m_isConnect = isConnect;
}

bool NetServerObject::isConnected()
{
	return m_isConnect;
}

NetServerObject::~NetServerObject()
{
}

bool NetServerObject::m_isClose;

SOCKET NetServerObject::s_serverSocket;

bool NetServerObject::m_isConnect = false;

SOCKET NetServerObject::s_sockConn;
