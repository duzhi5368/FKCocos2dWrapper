//-------------------------------------------------------------------------
#include "FKNetworkSocketConnecter.h"
#include "FKNetworkSocket.h"
#include "FKNetworkMacros.h"
//-------------------------------------------------------------------------
FKNetworkSocketConnecter::FKNetworkSocketConnecter( INetworkSocket* pOwner )
{
	m_pOwner = pOwner;
}
//-------------------------------------------------------------------------
// �յ���Ϣ���Ļص�
void FKNetworkSocketConnecter::onMessageReceived(FKCW_SimpleNet_Buffer& oBuffer)
{
	if( m_pOwner == NULL )
		return;
	FKNetworkSocket* p = dynamic_cast<FKNetworkSocket*>( m_pOwner );
	if( p )
		p->OnRecv( oBuffer.data(), oBuffer.length() );
}
//-------------------------------------------------------------------------
// ���ӳɹ�ʱ�Ļص�
void FKNetworkSocketConnecter::onConnected()
{
	if( m_pOwner == NULL )
		return;

	FKNetworkSocket* p = dynamic_cast<FKNetworkSocket*>( m_pOwner );
	if( p )
		p->OnConnencted();
}
//-------------------------------------------------------------------------
// ���ӳ�ʱʱ�Ļص�
void FKNetworkSocketConnecter::onConnectTimeout()
{
	if( m_pOwner == NULL )
		return;

	FKNetworkSocket* p = dynamic_cast<FKNetworkSocket*>( m_pOwner );
	if( p )
		p->OnConnectTimeout();
}
//-------------------------------------------------------------------------
// ����ʧ��ʱ�Ļص�
void FKNetworkSocketConnecter::onDisconnected()
{
	if( m_pOwner == NULL )
		return;

	FKNetworkSocket* p = dynamic_cast<FKNetworkSocket*>( m_pOwner );
	if( p )
		p->OnDisConnected();
}
//-------------------------------------------------------------------------
// ����ʱ�Ļص�
void FKNetworkSocketConnecter::onExceptionCaught(ENUM_SocketStatus eStatus)
{
	if( m_pOwner == NULL )
		return;

	FKNetworkSocket* p = dynamic_cast<FKNetworkSocket*>( m_pOwner );
	if( p == NULL )
		return;

	if( eStatus == eSocketIoError )
	{
		p->OnConnectError( eCNET_IoError, gs_ClientNetErrorInfo[eCNET_IoError].c_str() );
	}
	else
	{
		p->OnConnectError( eCNET_Unknown, gs_ClientNetErrorInfo[eCNET_Unknown].c_str() );
	}
}
//-------------------------------------------------------------------------