//*************************************************************************
//	��������:	2014-8-12   9:32
//	�ļ�����:	BoneData.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Transform.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class CBoneData
{
public:
	string				m_szName;
	string				m_szParent;
	f32					m_fLength;
	int					m_nScaleMode;
	bool				m_bIsRotationFixed;
	CTransform			m_GlobalTransform;
	CTransform			m_Transform;
public:
	CBoneData()
		: m_fLength( 0.0f )
		, m_nScaleMode( 1 )
		, m_bIsRotationFixed( false )
	{
		m_szName.clear();
		m_szParent.clear();
	}

	virtual ~CBoneData()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		m_szName.clear();
		m_szParent.clear();
		m_fLength = 0.0f;
		m_nScaleMode = 0;
		m_bIsRotationFixed = false;
	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------