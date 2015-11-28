//*************************************************************************
//	��������:	2014-8-12   11:51
//	�ļ�����:	TextureAtlasData.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseMacro.h"
#include "Rect.h"
#include <string>
#include <map>
using std::string;
using std::map;
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------

class CTextureAtlasData
{
public:
	string					m_szImagePath;
	string					m_szName;
	map< string, CRect >	m_szRects;
public:
	CTextureAtlasData()
	{

	}

	void AddTextureAtlasData( const string& p_szName, const CRect& p_Rect )
	{
		m_szRects[ p_szName ] = p_Rect;
	}
};

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------