//*************************************************************************
//	��������:	2014-8-13   15:52
//	�ļ�����:	FrameEvent.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	d
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Event.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class CBone;
class CArmature;
class CAnimationState;
class CFrameEvent : public CEvent
{
public:
	const static string ANIMATION_FRAME_EVENT;
	const static string BONE_FRAME_EVENT;
public:
	string				m_szFrameLabel;
	CBone*				m_pBone;
	CArmature*			m_pArmature;
	CAnimationState*	m_pAnimationState;
public:
	CFrameEvent( const string& p_szType )
		: CEvent( p_szType )
		, m_pBone ( NULL )
		, m_pAnimationState( NULL )
		, m_pArmature( NULL )
	{
		m_szFrameLabel.clear();
	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------