//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	INetworkSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/*
	TODO
*/
//-------------------------------------------------------------------------
class INetworkSocket;
// ��Ϣ�ص���
class INetworkMsgHandler
{
public:
	// �ͻ��˽��յ�����
	virtual void			OnRecv( const char* szBuf, int nLen ) = 0;
	// ���ӳɹ���Ϣ
	virtual void			OnConnencted( INetworkSocket* pSocket ) = 0;
	// ���ӹر���Ϣ
	virtual void			OnClose() = 0;
	// ���Ӵ�����Ϣ
	virtual void			OnConnectError( int nErrorCode, const char* strErrorMsg ) = 0;
};
//-------------------------------------------------------------------------
// ��һ����socket
class INetworkSocket
{
public:
	// �ͷ�����
	virtual void			Release() = 0;
	// ���ӷ�����
	virtual bool			Connect( const char* szServerIP, unsigned short usPort ) = 0;
	// �����ر�����
	virtual void			CloseConnect() = 0;
	// ��������
	virtual bool			Send( const char* szBuf, int nLen ) = 0;
	// �Ƿ�ǰ����������
	virtual bool			IsConnecting() = 0;
	// ��ȡID
	virtual int				GetSocketID() = 0;

	// ������Ϣ�ص�����
	virtual void			SetMsgHandler( INetworkMsgHandler* pMsgHandler ) = 0;
};
//-------------------------------------------------------------------------
// ����ģ��ϵͳ
class INetworkSystem
{
public:
	// ��������ϵͳ
	virtual void			Release() = 0;
	// �����ͻ�������socket
	virtual INetworkSocket*	CreateSocket( INetworkMsgHandler* pMsgHandler ) = 0;
	// ����ͻ���ָ������
	virtual void			ClearSocketByID( int nSocketID ) = 0;
	// ����ָ�����ӵĻص�
	virtual void			SetMsgHandler( int nSocketID, INetworkMsgHandler* pMsgHandler ) = 0;

	// �߼�����
	virtual void			UpdateEvent() = 0;
};
//-------------------------------------------------------------------------
// ��ȡ����ӿ�
extern INetworkSystem* GetNetworkSystem();
//-------------------------------------------------------------------------