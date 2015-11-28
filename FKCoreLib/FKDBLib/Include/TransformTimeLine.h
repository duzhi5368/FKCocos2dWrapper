//*************************************************************************
//	��������:	2014-8-11   15:22
//	�ļ�����:	TransformTimeLine.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "TimeLine.h"
#include "Transform.h"
#include "Point.h"
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
class CTransformTimeLine : public CTimeLine
{
public:
	static CTransformTimeLine EMPTY_TIMELINE;
public:
	bool		m_bTransformed;			// �Ƿ��Ѿ�ת��������
	CTransform	m_OriginTransform;		// ʱ��������ԭת������
	CPoint		m_OriginPiovt;			// ʱ��������ԭ����
	f32			m_fOffset;				// ƫ����
public:
	CTransformTimeLine()
		: m_fOffset( 0.0f )
		, m_bTransformed( false )
	{

	}
public:
	bool operator == ( const CTransformTimeLine& p_Other )
	{
		return ( m_bTransformed == p_Other.m_bTransformed &&
			m_OriginPiovt == p_Other.m_OriginPiovt &&
			m_OriginTransform == p_Other.m_OriginTransform &&
			(fabs(this->m_fOffset - p_Other.m_fOffset) < FK_EPSILON) );
	}
public:
	virtual void Clear()
	{
		if( this == &EMPTY_TIMELINE )
			return;

		CTimeLine::Clear();
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------