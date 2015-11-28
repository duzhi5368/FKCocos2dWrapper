//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_Map.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_MapInfo.h"
//-------------------------------------------------------------------------
class FKCW_TMX_Layer;
class FKCW_TMX_ObjectGroup;
//-------------------------------------------------------------------------
class FKCW_TMX_Map : public CCNodeRGBA
{
protected:
	FKCW_TMX_Map();
	
public:
	virtual ~FKCW_TMX_Map();

	static FKCW_TMX_Map* createWithXMLFile(const string& file);
	
	virtual bool initWithXMLFile(const string& file);

	// ͨ�����ֻ�ȡһ��Layer
	FKCW_TMX_Layer* getLayer(const string& name);
	// ͨ��������ȡһ��Layer
	FKCW_TMX_Layer* getLayerAt(int index);
	// ͨ�����ֻ�ȡһ��ObjectGroup
	FKCW_TMX_ObjectGroup* getObjectGroup(const string& name);
	// ��ȡһ������
	string getProperty(const string& name);
	// ΪTile����һ������
	string getTileProperty(int gid, const string& name);
	// ��ȡTMX��������
	ENUM_TMXOrientation getOrientation() { return m_mapInfo->getOrientation(); }
	// ��һ����ת��ΪTMX�����ռ�����
	CCPoint nodeToTMXSpace(CCPoint p);
	// ��һ��������TMX�����ռ�����ת��Ϊ��ǰ����
	CCPoint tmxToNodeSpace(CCPoint p);
	
public:
	CC_SYNTHESIZE(int, m_mapWidth, MapWidth);				// ��ͼ��Tiles������
	CC_SYNTHESIZE(int, m_mapHeight, MapHeight);				// ��ͼ�ߣ�Tiles������
	CC_SYNTHESIZE(float, m_tileWidth, TileWidth);			// ��ͼ�����أ�
	CC_SYNTHESIZE(float, m_tileHeight, TileHeight);			// ��ͼ�ߣ����أ�
    CC_SYNTHESIZE(FKCW_TMX_MapInfo*, m_mapInfo, MapInfo);	// ��ͼ��Ϣ
    CC_SYNTHESIZE_BOOL_SETTER(m_debugDrawObjects, DebugDrawObjects);	// �Ƿ���DugDraw
};