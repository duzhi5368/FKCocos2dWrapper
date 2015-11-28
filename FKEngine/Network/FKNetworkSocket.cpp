//-------------------------------------------------------------------------
#include "FKNetworkSocket.h"
#include "FKNetworkSystem.h"
//-------------------------------------------------------------------------
FKNetworkSocket::FKNetworkSocket( unsigned int unSocketID, INetworkSystem* pSystem )
{
	m_unSocketID	= unSocketID;
	m_pOwner		= pSystem;
	m_pConnecter	= new FKNetworkSocketConnecter( this );
}
//-------------------------------------------------------------------------
FKNetworkSocket::~FKNetworkSocket()
{
	CC_SAFE_DELETE( m_pConnecter );
}
//-------------------------------------------------------------------------
// �ͻ��˽��յ�����
void FKNetworkSocket::OnRecv( const char* szBuf, int nLen )
{
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->PushRecvMsg( m_unSocketID, szBuf, nLen );
}
//-------------------------------------------------------------------------
// ���ӳɹ���Ϣ
void FKNetworkSocket::OnConnencted()
{
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;
	
	p->PushConnectSuccessMsg( m_unSocketID, this );
}
//-------------------------------------------------------------------------
// ���ӹر���Ϣ
void FKNetworkSocket::OnDisConnected()
{
	// ֪ͨsystem
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->PushCloseMsg( m_unSocketID );
}
//-------------------------------------------------------------------------
// ���ӳ�ʱ��Ϣ
void FKNetworkSocket::OnConnectTimeout()
{
	// ֪ͨsystem
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->PushConnectErrorMsg( m_unSocketID, eCNET_ConnectTimeout, gs_ClientNetErrorInfo[eCNET_ConnectTimeout].c_str() );
}
//-------------------------------------------------------------------------
// ���Ӵ�����Ϣ
void FKNetworkSocket::OnConnectError( int nErrorCode, const char* strErrorMsg )
{
	CloseConnect();

	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->PushConnectErrorMsg( m_unSocketID, nErrorCode, strErrorMsg );
}
//-------------------------------------------------------------------------
// �ͷ�����
void FKNetworkSocket::Release()
{
	CloseConnect();
}
//-------------------------------------------------------------------------
// ���ӷ�����
bool FKNetworkSocket::Connect( const char* szServerIP, unsigned short usPort )
{
	if( m_pConnecter == NULL )
		return false;
	FKCW_SimpleNet_InetAddress oAddres;
	oAddres.setIp( szServerIP );
	oAddres.setPort( usPort );
	m_pConnecter->setInetAddress( oAddres );
	m_pConnecter->setSoTimeout( gs_MAX_TIMEOUT_TIME );
	return m_pConnecter->connect();
}
//-------------------------------------------------------------------------
// �����ر�����
void FKNetworkSocket::CloseConnect()
{
	if( m_pConnecter == NULL )
		return;
	m_pConnecter->disconnect();

	// ֪ͨsystem
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->PushCloseMsg( m_unSocketID );
}
//-------------------------------------------------------------------------
// ��������
bool FKNetworkSocket::Send( const char* szBuf, int nLen )
{
	if( m_pConnecter == NULL )
		return false;
	m_pConnecter->send( const_cast<char*>(szBuf), nLen );
	return true;
}
//-------------------------------------------------------------------------
// �Ƿ�ǰ����������
bool FKNetworkSocket::IsConnecting()
{
	if( m_pConnecter == NULL )
		return false;
	return m_pConnecter->isConnected();
}
//-------------------------------------------------------------------------
// ��ȡID
int FKNetworkSocket::GetSocketID()
{
	return m_unSocketID;
}
//-------------------------------------------------------------------------
// ������Ϣ�ص�����
void FKNetworkSocket::SetMsgHandler( INetworkMsgHandler* pMsgHandler )
{
	if ( m_pOwner == NULL )
		return;
	FKNetworkSystem* p = dynamic_cast<FKNetworkSystem*>( m_pOwner );
	if( p == NULL )
		return;

	p->SetMsgHandler( m_unSocketID, pMsgHandler );
}
//-------------------------------------------------------------------------