//*************************************************************************
//	��������:	2014-8-11   16:15
//	�ļ�����:	DisplayData.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Transform.h"
#include "Point.h"
#include <string>
using std::string;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
class CDisplayData
{
public:
	string			m_szName;
	string			m_szType;
	CTransform		m_Transform;
	CPoint			m_Pivot;
public:
	CDisplayData()
	{
		m_szName.clear();
		m_szType.clear();
	}

	virtual ~CDisplayData()
	{
		Clear();
	}
public:
	virtual void Clear()
	{
		m_szName.clear();
		m_szType.clear();
	}
};
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------