//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	FKNetworkSocketConnecter.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKNetworkSocketConnecter : public FKCW_SimpleNet_NetObject
{
public:
	FKNetworkSocketConnecter( INetworkSocket* pOwner );
public:
	// �յ���Ϣ���Ļص�
	virtual void onMessageReceived(FKCW_SimpleNet_Buffer& oBuffer);
	// ���ӳɹ�ʱ�Ļص�
	virtual void onConnected();
	// ���ӳ�ʱʱ�Ļص�
	virtual void onConnectTimeout();
	// ����ʧ��ʱ�Ļص�
	virtual void onDisconnected();
	// ����ʱ�Ļص�
	virtual void onExceptionCaught(ENUM_SocketStatus eStatus);
private:
	INetworkSocket*				m_pOwner;
};