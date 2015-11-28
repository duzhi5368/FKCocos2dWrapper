//*************************************************************************
//	��������:	2014-8-19   19:22
//	�ļ�����:	Cocos2dxDBTextureAtlas.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "CommonHead.h"
#include <map>
using std::map;
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class CCocos2dxDBTextureAtlas : public ITextureAtlas
{
protected:
	CTextureAtlasData*			m_pTextureAtlasData;
	map<string, uint>			m_mapTextureNames;
	CCTextureAtlas*				m_pTextureAtlas;
	CCTexture2D*				m_pTexture2D;
public:
	CCocos2dxDBTextureAtlas( CTextureAtlasData* p_pData );
	virtual ~CCocos2dxDBTextureAtlas();
public:
	// TextureAtlas������
	virtual const string&	GetName();
	// ��ȡָ������Դ��ռ�������
	virtual CRect			GetRegion( const string& p_szName );
	// ��Դ����
	virtual void			Clear();
public:
	uint					GetQuadIndex( const string& p_szName );
	CCTextureAtlas*			GetTextureAtlas();
	CCTexture2D*			GetTexture2D();
};
//-------------------------------------------------------------------------