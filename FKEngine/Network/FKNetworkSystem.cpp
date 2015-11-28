//-------------------------------------------------------------------------
#include "FKNetworkSystem.h"
#include "FKNetworkMacros.h"
#include "FKNetworkSocket.h"
//-------------------------------------------------------------------------
INetworkSystem*	gs_pNetworkSystem = NULL;
FKNetworkSystem	gs_FKNetworkSystem;
//-------------------------------------------------------------------------
// ��ȡ����ӿ�
INetworkSystem* GetNetworkSystem()
{
	return gs_pNetworkSystem;
}
//-------------------------------------------------------------------------
FKNetworkSystem::FKNetworkSystem()
	: m_unCurSocketID( 0 )
{
	m_vecMsgHandlers.resize( gs_MAX_CLIENT_SOCKET_NUM );
	memset( &m_vecMsgHandlers[0], 0, gs_MAX_CLIENT_SOCKET_NUM * sizeof(INetworkMsgHandler*) );

	gs_pNetworkSystem = this;
}
//-------------------------------------------------------------------------
FKNetworkSystem::~FKNetworkSystem()
{
	gs_pNetworkSystem = NULL;
}
//-------------------------------------------------------------------------
// ��������ϵͳ
void FKNetworkSystem::Release()
{
	m_vecMsgHandlers.clear();
}
//-------------------------------------------------------------------------
// �����ͻ�������socket
INetworkSocket*	FKNetworkSystem::CreateSocket( INetworkMsgHandler* pMsgHandler )
{
	if( pMsgHandler == NULL || m_unCurSocketID >= gs_MAX_CLIENT_SOCKET_NUM )
		return NULL;
	FKNetworkSocket* p = new FKNetworkSocket( ++m_unCurSocketID, this );
	if( p == NULL )
		return NULL;
	m_vecMsgHandlers[m_unCurSocketID-1] = pMsgHandler;
	return p;
}
//-------------------------------------------------------------------------
// ����ͻ���ָ������
void FKNetworkSystem::ClearSocketByID( int nSocketID )
{
	if (nSocketID <= gs_MAX_CLIENT_SOCKET_NUM && nSocketID > 0)
	{
		m_vecMsgHandlers[nSocketID-1] = NULL;
	}
}
//-------------------------------------------------------------------------
// ����ָ�����ӵĻص�
void FKNetworkSystem::SetMsgHandler( int nSocketID, INetworkMsgHandler* pMsgHandler )
{
	m_vecMsgHandlers[nSocketID-1] = pMsgHandler;
}
//-------------------------------------------------------------------------
// �߼�����
void FKNetworkSystem::UpdateEvent()
{
	m_listCommandList.SwitchState();

	int i = 0;
	while( !m_listCommandList.GetOutList().empty() )
	{
		FKNetworkCommand& tagCmd = m_listCommandList.GetOutList().front();
		switch ( tagCmd.m_unType )
		{
		case eCNMT_RecvMsg:
			__HandleRecvMsg( tagCmd.m_unSocketID, &tagCmd.m_szMsg[0], tagCmd.m_unLen );
			break;
		case eCNMT_ConnectSuccess:
			__HandleConnectSuccess( tagCmd.m_unSocketID, (INetworkSocket*)tagCmd.m_unSocket );
			break;
		case eCNMT_Close:
			__HandleCloseMsg( tagCmd.m_unSocketID );
			break;
		case eCNMT_Error:
			__HandleConnectErrorMsg( tagCmd.m_unSocketID, tagCmd.m_unSocket, &tagCmd.m_szMsg[0] );
			break;
		default:
			break;
		}

		m_listCommandList.GetOutList().pop_front();
	}
}
//-------------------------------------------------------------------------
// ���ӳɹ�����
void FKNetworkSystem::PushConnectSuccessMsg( unsigned int unIndex, INetworkSocket* pClientSocket )
{
	FKNetworkCommand tagCommand;
	tagCommand.m_unType				= eCNMT_ConnectSuccess;
	tagCommand.m_unSocketID			= unIndex;
	tagCommand.m_unSocket			= (unsigned int)pClientSocket;
	m_listCommandList.PushBack(&tagCommand);
}
//-------------------------------------------------------------------------
// ���Ӵ�����
void FKNetworkSystem::PushConnectErrorMsg( unsigned int unIndex, int nError, const char* lpErrorMsg )
{
	FKNetworkCommand tagCommand;
	tagCommand.m_unType				= eCNMT_Error;
	tagCommand.m_unSocketID			= unIndex;
	tagCommand.m_unSocket			= (unsigned int)nError;
	tagCommand.m_unLen				= (int)strlen( lpErrorMsg ) + 1;
	tagCommand.m_szMsg.resize( tagCommand.m_unLen );
	if( (int)tagCommand.m_szMsg.capacity() >= (int)strlen(lpErrorMsg) )
	{
		memcpy( &tagCommand.m_szMsg[0], lpErrorMsg, strlen( lpErrorMsg ) );
	}
	else
	{
		return;
	}
	m_listCommandList.PushBack(&tagCommand);
}
//-------------------------------------------------------------------------
// �������ݴ���
void FKNetworkSystem::PushRecvMsg( unsigned int unIndex, const char* szBuf, int nLen )
{
	if( szBuf == NULL || nLen <= 0 || nLen > SOCKET_READ_BUFFER_SIZE )
		return;

	FKNetworkCommand tagCommand;
	tagCommand.m_unType				= eCNMT_RecvMsg;
	tagCommand.m_unSocketID			= unIndex;
	tagCommand.m_unSocket			= 0;
	tagCommand.m_unLen				= nLen;
	tagCommand.m_szMsg.resize( nLen );
	if( (int)tagCommand.m_szMsg.capacity() >= nLen )
	{
		memcpy( &tagCommand.m_szMsg[0], szBuf, nLen );
	}
	else
	{
		return;
	}
	m_listCommandList.PushBack(&tagCommand);
}
//-------------------------------------------------------------------------
// ���ӹرմ���
void FKNetworkSystem::PushCloseMsg( unsigned int unIndex )
{
	FKNetworkCommand tagCommand;
	tagCommand.m_unType				= eCNMT_Close;
	tagCommand.m_unSocketID			= unIndex;
	tagCommand.m_unSocket			= 0;
	m_listCommandList.PushBack(&tagCommand);
}
//-------------------------------------------------------------------------
void FKNetworkSystem::__HandleConnectSuccess( unsigned int unIndex, INetworkSocket* pClientSocket )
{
	if( unIndex >= gs_MAX_CLIENT_SOCKET_NUM )
		return;
	INetworkMsgHandler* p = m_vecMsgHandlers[unIndex-1];
	if( p == NULL )
		return;
	p->OnConnencted( pClientSocket );
}
//-------------------------------------------------------------------------
void FKNetworkSystem::__HandleConnectErrorMsg( unsigned int unIndex, int nError, const char* lpErrorMsg )
{
	if( unIndex >= gs_MAX_CLIENT_SOCKET_NUM )
		return;
	INetworkMsgHandler* p = m_vecMsgHandlers[unIndex-1];
	if( p == NULL )
		return;
	p->OnConnectError( nError, lpErrorMsg );
}
//-------------------------------------------------------------------------
void FKNetworkSystem::__HandleRecvMsg( unsigned int unIndex, const char* szBuf, int nLen )
{
	if( unIndex >= gs_MAX_CLIENT_SOCKET_NUM )
		return;
	INetworkMsgHandler* p = m_vecMsgHandlers[unIndex-1];
	if( p == NULL )
		return;
	p->OnRecv( szBuf, nLen );
}
//-------------------------------------------------------------------------
void FKNetworkSystem::__HandleCloseMsg( unsigned int unIndex )
{
	if( unIndex >= gs_MAX_CLIENT_SOCKET_NUM )
		return;
	INetworkMsgHandler* p = m_vecMsgHandlers[unIndex-1];
	if( p == NULL )
		return;
	p->OnClose();
}
//-------------------------------------------------------------------------