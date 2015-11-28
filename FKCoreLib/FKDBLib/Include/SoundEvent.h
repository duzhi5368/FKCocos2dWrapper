//*************************************************************************
//	��������:	2014-8-13   16:25
//	�ļ�����:	SoundEvent.h
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

class CArmature;
class CAnimationState;
class CSoundEvent : public CEvent
{
public:
	static const string		SOUND;
public:
	CArmature*				m_pArmature;
	CAnimationState*		m_pAnimationState;
	string					m_szSound;
public:
	CSoundEvent( const string& p_szType )
		: CEvent( p_szType )
		, m_pAnimationState( NULL )
		, m_pArmature( NULL )
	{

	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------