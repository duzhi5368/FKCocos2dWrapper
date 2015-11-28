//*************************************************************************
//	��������:	2015-1-10
//	�ļ�����:	FKNetworkSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
#include "../Common/TSwitchList.h"
#include "FKNetworkCommand.h"
//-------------------------------------------------------------------------
class FKNetworkSystem : public INetworkSystem
{
public:
	FKNetworkSystem();
	~FKNetworkSystem();
public:
	// ��������ϵͳ
	virtual void			Release();
	// �����ͻ�������socket
	virtual INetworkSocket*	CreateSocket( INetworkMsgHandler* pMsgHandler );
	// ����ͻ���ָ������
	virtual void			ClearSocketByID( int nSocketID );
	// ����ָ�����ӵĻص�
	virtual void			SetMsgHandler( int nSocketID, INetworkMsgHandler* pMsgHandler );
	// �߼�����
	virtual void			UpdateEvent();
public:
	// ���ӳɹ�����
	void	PushConnectSuccessMsg( unsigned int unIndex, INetworkSocket* pClientSocket );
	// ���Ӵ�����
	void	PushConnectErrorMsg( unsigned int unIndex, int nError, const char* lpErrorMsg );
	// �������ݴ���
	void	PushRecvMsg( unsigned int unIndex, const char* szBuf, int nLen );
	// ���ӹرմ���
	void	PushCloseMsg( unsigned int unIndex );
private:
	void	__HandleConnectSuccess( unsigned int unIndex, INetworkSocket* pClientSocket );
	void	__HandleConnectErrorMsg( unsigned int unIndex, int nError, const char* lpErrorMsg );
	void	__HandleRecvMsg( unsigned int unIndex, const char* szBuf, int nLen );
	void	__HandleCloseMsg( unsigned int unIndex );
private:
	unsigned int					m_unCurSocketID;		// �����socket�����
	vector<INetworkMsgHandler*>		m_vecMsgHandlers;		// ��Ϣ�ص������б�
	TSwitchList<FKNetworkCommand>	m_listCommandList;		// ����״̬��Ϣ����
};