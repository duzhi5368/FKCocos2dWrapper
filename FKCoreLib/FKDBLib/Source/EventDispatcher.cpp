//-------------------------------------------------------------------------
#include "../Include/EventDispatcher.h"
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

// ʹ�� EventDispatcher ����ע���¼�������������ʹ�������ܹ������¼�֪ͨ��key������ص���Ψһ��ʾ������removeEventListener��ע���õ�
void CEventDispatcher::AddEventListener( const string& p_szType, CallbackFunc p_pListener, const string& p_szKey )
{
	ListListeners& list = m_mapEventListeners[p_szType];
	list.push_back( Listener(p_pListener, p_szKey));
}
//-------------------------------------------------------------------------
// ������Ϣ�ַ�
void CEventDispatcher::DispatchEvent( CEvent* p_pEvent )
{
	if( p_pEvent == NULL )
		return;
	EventListeners::iterator Ite = m_mapEventListeners.find( p_pEvent->m_szType );
	if( Ite != m_mapEventListeners.end() )
	{
		ListListeners::iterator IteList = Ite->second.begin();
		for( ; IteList != Ite->second.end(); ++IteList )
		{
			IteList->first( p_pEvent );
		}
	}

	// ע�⣬���������ɾ��
	delete p_pEvent;
}
//-------------------------------------------------------------------------
// ����Ƿ�ע����ĳ�����͵��¼��Ļص�
bool CEventDispatcher::IsHadEventListener( const string& p_szType )const
{
	return ( m_mapEventListeners.find( p_szType ) != m_mapEventListeners.end() );
}
//-------------------------------------------------------------------------
// ɾ��������
void CEventDispatcher::RemoveEventListener( const string& p_szType, const string& p_szKey )
{
	EventListeners::iterator Ite = m_mapEventListeners.find( p_szType );
	if( Ite == m_mapEventListeners.end() )
		return;

	ListListeners::iterator IteList = Ite->second.begin();
	for( ; IteList != Ite->second.end();  )
	{
		if( IteList->second == p_szKey )
		{
			IteList = Ite->second.erase( IteList );
		}
		else
		{
			++IteList;
		}
	}
}

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------