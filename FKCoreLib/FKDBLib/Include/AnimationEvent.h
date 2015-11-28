//*************************************************************************
//	��������:	2014-8-13   16:19
//	�ļ�����:	AnimationEvent.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Event.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class CAnimationState;
class CArmature;
class CAnimateEvent : public CEvent
{
public:
	const static string	FADE_IN;
	const static string	FADE_OUT;
	const static string	START;
	const static string	COMPLETE;
	const static string	LOOP_COMPLETE;
	const static string FADE_IN_COMPLETE;
	const static string FADE_OUT_COMPLETE;
public:
	CAnimationState*	m_pAnimationState;
	CArmature*			m_pArmature;
public:
	CAnimateEvent( const string& p_szType )
		: CEvent( p_szType )
		, m_pArmature( NULL )
		, m_pAnimationState( NULL )
	{

	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------