//*************************************************************************
//	��������:	2014-8-11   14:07
//	�ļ�����:	Transform.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Matrix.h"
#include <math.h>
//-------------------------------------------------------------------------
class CTransform
{
public:
	f32			m_fPosX;		// ����
	f32			m_fPosY;
	f32			m_fSkewX;		// X��ƫ����
	f32			m_fSkewY;
	f32			m_fScaleX;		// X�����ű���
	f32			m_fScaleY;
public:
	CTransform()
		: m_fPosX( 0.0f )
		, m_fPosY( 0.0f )
		, m_fScaleX( 1.0f )
		, m_fScaleY( 1.0f )
		, m_fSkewX( 0.0f )
		, m_fSkewY( 0.0f )
	{

	}
	CTransform( const CTransform& p_Transform )
	{
		m_fPosX			= p_Transform.m_fPosX;
		m_fPosY			= p_Transform.m_fPosY;
		m_fSkewX		= p_Transform.m_fSkewX;
		m_fSkewY		= p_Transform.m_fSkewY;
		m_fScaleX		= p_Transform.m_fScaleX;
		m_fScaleY		= p_Transform.m_fScaleY;
	}
public:
	bool operator == ( const CTransform& p_Other )
	{
		return (fabs(this->m_fPosX		- p_Other.m_fPosX	) < FK_EPSILON)
			&& (fabs(this->m_fPosY		- p_Other.m_fPosY	) < FK_EPSILON)
			&& (fabs(this->m_fSkewX		- p_Other.m_fSkewX	) < FK_EPSILON)
			&& (fabs(this->m_fSkewY		- p_Other.m_fSkewY	) < FK_EPSILON)
			&& (fabs(this->m_fScaleX	- p_Other.m_fScaleX	) < FK_EPSILON)
			&& (fabs(this->m_fScaleY	- p_Other.m_fScaleY	) < FK_EPSILON);
	}
public:
	// ת�� Transform Ϊ ����
	static void			TransformTransformToMatrix( CTransform& p_tagTransform, FK_OUT CMatrix& p_OutMatrix );
	// ת�� ���൱ǰ���� Ϊ ��������
	static void			TransformPointWithParent( CTransform& p_tagTransform, CTransform& p_tagParent );

	static f32			GetEaseValue( f32 p_fValue, f32 p_fEasing );
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------