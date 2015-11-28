//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	FKNetworkSocket.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "FKNetworkSocketConnecter.h"
#include "FKNetworkMacros.h"
//-------------------------------------------------------------------------
class FKNetworkSocket : public INetworkSocket
{
	friend class FKNetworkSocketConnecter;
public:
	FKNetworkSocket( unsigned int unSocketID, INetworkSystem* pSystem );
	~FKNetworkSocket();
public:
	// �ͷ�����
	virtual void			Release();
	// ���ӷ�����
	virtual bool			Connect( const char* szServerIP, unsigned short usPort );
	// �����ر�����
	virtual void			CloseConnect();
	// ��������
	virtual bool			Send( const char* szBuf, int nLen );
	// �Ƿ�ǰ����������
	virtual bool			IsConnecting();
	// ��ȡID
	virtual int				GetSocketID();
	// ������Ϣ�ص�����
	virtual void			SetMsgHandler( INetworkMsgHandler* pMsgHandler );
private:
	// �ͻ��˽��յ�����
	void OnRecv( const char* szBuf, int nLen );
	// ���ӳɹ���Ϣ
	void OnConnencted();
	// ���ӹر���Ϣ
	void OnDisConnected();
	// ���ӳ�ʱ��Ϣ
	void OnConnectTimeout();
	// ���Ӵ�����Ϣ
	void OnConnectError( int nErrorCode, const char* strErrorMsg );
private:
	unsigned int				m_unSocketID;		// ��socketΨһ���
	INetworkSystem*				m_pOwner;			// ���������
	FKNetworkSocketConnecter*	m_pConnecter;		// ����������
};