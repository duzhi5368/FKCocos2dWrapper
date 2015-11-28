//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_MapInfo.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
// tmx����
enum ENUM_TMXOrientation
{
	eTMXOrientationOrthogonal = 1,			// ֱ��
	eTMXOrientationIsometric,				// б45��
	eTMXOrientationHexagonal				// ������
};
// tmx���ӱ�ʾ
enum ENUM_TMXTileFlag
{
	eTMXTileFlagFlipH = 0x80000000,			// ˮƽ��ת
	eTMXTileFlagFlipV = 0x40000000,			// ��ֱ��ת
	eTMXTileFlagFlipDiagonal = 0x20000000,	// б�߷�ת
	eTMXTileFlagFlipAll = (eTMXTileFlagFlipH | eTMXTileFlagFlipV | eTMXTileFlagFlipDiagonal),
	eTMXTileFlagFlipMask = ~(eTMXTileFlagFlipAll)
};
//-------------------------------------------------------------------------
class FKCW_TMX_MapInfo : public CCObject
{
protected:
	FKCW_TMX_MapInfo();
	
public:
	virtual ~FKCW_TMX_MapInfo();
	static FKCW_TMX_MapInfo* create();
	
	// ����Key��ȡһ������ֵ
	string getProperty(const string& key);
	// ���һ������
	void addProperty(const string& key, const string& value);

	// ����GridID��ȡ��TileSet����
	int getTileSetIndex(int gid);
	
	// ��ȡһ��Tile�����ԡ�
	// ������δ�ҵ����򷵻ؿ��ַ���
	string getTileProperty(int gid, const string& key);
	// Ϊһ��Tile�������
	void addTileProperty(int gid, const string& key, const string& value);

public:
	CC_SYNTHESIZE(string, m_filename, TMXFilename);									// tmx�ļ���
	CC_SYNTHESIZE(ENUM_TMXOrientation, m_orientation, Orientation);					// Map����
	CC_SYNTHESIZE(int, m_mapWidth, MapWidth);										// Map��Tiles������
	CC_SYNTHESIZE(int, m_mapHeight, MapHeight);										// Map�ߣ�Tiles������
	CC_SYNTHESIZE(float, m_tileWidth, TileWidth);									// Tiles�����أ�
	CC_SYNTHESIZE(float, m_tileHeight, TileHeight);									// Tiles�ߣ����أ�
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCArray, m_layers, Layers);						// ���б�
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCArray, m_tilesets, TileSets);					// TilesSet��Ϣ�б�
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCArray, m_objectGroups, ObjectGroups);			// �������б�
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCDictionary, m_properties, Properties);			// Map�����Դʵ�
	CC_SYNTHESIZE_PASS_BY_REF_NC(CCDictionary, m_tileProperties, TileProperties);	// Tile���Դʵ䣬Key����GridID,Value��һ���Ӵʵ�
};