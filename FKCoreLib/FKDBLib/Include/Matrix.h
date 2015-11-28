//*************************************************************************
//	��������:	2014-8-11   11:18
//	�ļ�����:	Matrix.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Point.h"
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
class CMatrix
{
public:
	f32 m_fA, m_fB, m_fC, m_fD;
	f32 m_fX, m_fY;
public:
	CMatrix()
		: m_fA( 0.0f )
		, m_fB( 0.0f )
		, m_fC( 0.0f )
		, m_fD( 0.0f )
		, m_fX( 0.0f )
		, m_fY( 0.0f )
	{

	}
public:
	// ����һ������
	static CMatrix	MakeMatrix( f32 p_fA, f32 p_fB, f32 p_fC, f32 p_fD, f32 p_fX, f32 p_fY );
	// ��һ����ͨ������ת��
	static CPoint	MutilMaxtrix( const CPoint& p_tagPoint, const CMatrix& p_tagMatrix );
	// ����һ����Ԫ����
	static CMatrix	MakeIndentityMatrix();
	// ��Գƾ���
	static CMatrix	TranslateMatrix( const CMatrix& p_tagMatrix, f32 p_fX, f32 p_fY );
	// ��ת����
	static CMatrix	RotateMatrix( const CMatrix& p_tagMatrix, f32 p_fAngle );
	// ���ž���
	static CMatrix	ScaleMatrix( const CMatrix& p_tagMatrix, f32 p_fXScale, f32 p_fYScale );
	// ���Ӿ���
	static CMatrix	ConcatMatrix( const CMatrix& p_tagMatrix1, const CMatrix& p_tagMatrix2 );
	// ��ת����
	static CMatrix	InvertMatrix( const CMatrix& p_tagMatrix );
	// �Ƚ����������Ƿ����
	static bool		IsEqual( const CMatrix& p_tagMatrix1, const CMatrix& p_tagMatrix2 );
};

// ��λ����
extern const CMatrix MatrixIdentity;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------