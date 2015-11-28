//*************************************************************************
//	��������:	2014-8-11   11:09
//	�ļ�����:	ColorTransform.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
//-------------------------------------------------------------------------


class CColorTransform
{
public:
	CColorTransform()
		: m_unColor( 0 )
		, m_cAlphaOffset( 0 )
		, m_cRedOffset( 0 )
		, m_cGreenOffset( 0 )
		, m_cBlueOffset( 0 )
		, m_fAlphaMulti( 0.0f )
		, m_fRedMulti( 0.0f )
		, m_fGreenMulti( 0.0f )
		, m_fBlueMulti( 0.0f )
	{

	}
public:
	uint		m_unColor;				// RGB��ɫֵ
	/**
	* �����offsetȡֵ[-255, 255]������Multi�����˻����ٺͶ�Ӧ�� ͸����ͨ��/��ɫͨ�� ֵ���
	*/
	f32			m_fAlphaMulti;
	f32			m_fRedMulti;
	f32			m_fGreenMulti;
	f32			m_fBlueMulti;
	c8			m_cAlphaOffset;
	c8			m_cRedOffset;
	c8			m_cGreenOffset;
	c8			m_cBlueOffset;
};


	//-------------------------------------------------------------------------