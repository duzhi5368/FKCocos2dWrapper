//*************************************************************************
//	��������:	2014-8-11   14:58
//	�ļ�����:	Frame.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// �ؼ�֡
class CFrame
{
public:
	f32			m_fPos;			// ֡��λ��
	f32			m_fDuration;	// ֡����ʱ��
public:
	string		m_szAction;		// ������
	string		m_szEvent;		// �¼�
	string		m_szSound;		// ��Ч
public:
	CFrame()
		: m_fPos( 0.0f )
		, m_fDuration( 0.0f )
	{
		m_szAction.clear();
		m_szEvent.clear();
		m_szSound.clear();
	}

	virtual ~CFrame()
	{
		Clear();
	}

	virtual void Clear()
	{
		m_fPos = m_fDuration = 0.0f;
		m_szAction.clear();
		m_szEvent.clear();
		m_szSound.clear();
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------