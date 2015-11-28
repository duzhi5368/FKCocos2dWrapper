//*************************************************************************
//	��������:	2014-8-13   15:19
//	�ļ�����:	EventDispatcher.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Event.h"
#include <string>
#include <functional>
#include <list>
#include <map>
using std::string;
using std::list;
using std::map;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class CEventDispatcher
{
public:
	typedef	std::function<void(CEvent*)>		CallbackFunc;
	typedef std::pair<CallbackFunc, string>		Listener;
	typedef std::list<Listener>					ListListeners;
	typedef std::map<string, ListListeners>		EventListeners;
public:
	EventListeners			m_mapEventListeners;
public:
	// ʹ�� EventDispatcher ����ע���¼�������������ʹ�������ܹ������¼�֪ͨ��key������ص���Ψһ��ʾ������removeEventListener��ע���õ�
	void		AddEventListener( const string& p_szType, CallbackFunc p_pListener, const string& p_szKey );
	// ������Ϣ�ַ�
	void		DispatchEvent( CEvent* p_pEvent );
	// ����Ƿ�ע����ĳ�����͵��¼��Ļص�
	bool		IsHadEventListener( const string& p_szType )const;
	// ɾ��������
	void		RemoveEventListener( const string& p_szType, const string& p_szKey );
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------