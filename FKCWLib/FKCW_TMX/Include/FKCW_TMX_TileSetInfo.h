//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_TileSetInfo.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_TileSetInfo : public CCObject
{
protected:
	FKCW_TMX_TileSetInfo();
	
public:
	virtual ~FKCW_TMX_TileSetInfo();
	static FKCW_TMX_TileSetInfo* create();
	
	// ��ȡTileSet��ͼƬ��С
	// ������TileSet��ʼ��GridID
	CCRect getRect(int gid);										
	
	CC_SYNTHESIZE(string, m_name, Name);							// TileSet����
	CC_SYNTHESIZE(int, m_firstGid, FirstGid);						// TileSet��ʼ��GridID����0��ʼ����
	CC_SYNTHESIZE(float, m_tileWidth, TileWidth);					// Tile��ȣ����أ�	
	CC_SYNTHESIZE(float, m_tileHeight, TileHeight);					// Tile�߶ȣ����أ�
	CC_SYNTHESIZE(float, m_spacing, Spacing);						// TileSetͼƬ�е����� Tile ֮��ļ����С�����أ�
	CC_SYNTHESIZE(float, m_margin, Margin);							// TileSetͼƬ��Ե��С�����أ�
	CC_SYNTHESIZE(string, m_sourceImagePath, SourceImagePath);		// Դ�ļ�·�����Ǿ���·���������·��ȡ����tmx�ļ���·�����ͣ�
	CC_SYNTHESIZE(float, m_imageWidth, ImageWidth);					// ������
	CC_SYNTHESIZE(float, m_imageHeight, ImageHeight);				// ����߶ȣ����أ�
	CC_SYNTHESIZE(CCTexture2D*, m_texture, Texture);				// ����
};