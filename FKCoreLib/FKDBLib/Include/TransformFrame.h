//*************************************************************************
//	��������:	2014-8-11   15:48
//	�ļ�����:	TransformFrame.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Frame.h"
#include "Transform.h"
#include "Point.h"
#include "ColorTransform.h"
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
class CTransformFrame : public CFrame
{
public:
	f32					m_fTweenEasing;
	f32					m_fZOrder;
	int					m_nTweenRotate;
	int					m_nDisplayIndex;
	bool				m_bIsVisible;

	CTransform			m_GlobalTransform;
	CTransform			m_Transform;
	CPoint				m_Pivot;
	CColorTransform*	m_pColorTransform;
public:
	CTransformFrame()
		: m_fTweenEasing( 0.0f )
		, m_nTweenRotate( 0 )
		, m_nDisplayIndex( 0 )
		, m_bIsVisible( true )
		, m_fZOrder( 0.0f )
		, m_pColorTransform( NULL )
	{

	}

	virtual ~CTransformFrame()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		SAFE_DELETE( m_pColorTransform );
		CFrame::Clear();
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------