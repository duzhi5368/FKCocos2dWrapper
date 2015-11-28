//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	FKCW_TMX_Layer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_TMX_Macros.h"
//-------------------------------------------------------------------------
class FKCW_TMX_MapInfo;
class FKCW_TMX_LayerInfo;
class FKCW_TMX_TileSetInfo;
class FKCW_TMX_SpriteBatchNode;
//-------------------------------------------------------------------------
class FKCW_TMX_Layer : public CCNodeRGBA
{
private:
	typedef struct {
		int atlasIndex;
		int tilesetIndex;
	} STileSetAtlasInfo;
	
private:

	int* m_tiles;					// GridID�б�
	CCSprite* m_reusedTile;
	
private:
	// ��Index����ָ��ֵ���������
	void decreaseIndexIfMoreThan(int tilesetIndex, int index);
	//  ��IndexС��ָ��ֵ����������
	void increaseIndexIfEqualOrMoreThan(int tilesetIndex, int index);
	// ���һ��CCSprite��Tile��
	void setupTileSprite(CCSprite* sprite, CCPoint pos, int gid);
	// ��ȡ���õ�Tile
	CCSprite* reusedTile(CCRect rect, FKCW_TMX_SpriteBatchNode* bn);
	
protected:
	FKCW_TMX_Layer(int layerIndex, FKCW_TMX_MapInfo* mapInfo);

	// ��ֱ�ǵ�ͼ�л�ȡһ��Tile�����½���������
	CCPoint getPositionForOrthoAt(int posX, int posY);
	// ��б45��ͼ�л�ȡһ��Tile�����½���������
	CCPoint getPositionForIsoAt(int posX, int posY);
	// �������ε�ͼ�л�ȡһ��Tile�����½���������
	CCPoint getPositionForHexAt(int posX, int posY);
	// ��ȡһ��Tile��Zֵ
	float getVertexZAt(int x, int y);
	// ���һ��Tile
	void appendTileForGid(int tilesetIndex, int gid, int x, int y);
	// ����һ��Tile����
    void setTileAt(int tilesetIndex, int gid, int x, int y, int z);
	// ��������
	void parseInternalProperties();
	// ����Tile��������ڲ������ƫ��ֵ
	CCPoint calculateLayerOffset(float x, float y);
	// ��ʼ��GridIndex
	void setupTiles();
	 
public:
	virtual ~FKCW_TMX_Layer();
	// ����Layer��Index��0��ʼ����
	static FKCW_TMX_Layer* create(int layerIndex, FKCW_TMX_MapInfo* mapInfo);
	// ��ȡ������
	string getProperty(const string& key);

	// ���������Layer��ƫ������λ�ã�����Tile��λ�ñ��ֵ
	CCPoint getTileCoordinateAt(float x, float y);
	// ���ݸ�����Tile��λ�ñ��ֵ����ȡTile
	// ����ʱ��ͬʱ�����ص�CCSprite����Sprite�Ѿ���ӵ�Layer��
	// ���Ե��� layer->removeChild(sprite, true); ����layer->removeTileAt(x, y);������ɾ��
	CCSprite* tileAt(int x, int y);
	// ��Layerɾ��һ��Tile
	void removeTile(CCSprite* sprite);
	// ����Tile�ı��ֵ��ȡ��GridID
	int getGidAt(int x, int y);
	// ��ȡһ��GridID����
	// ��������СΪ layerWidth * layerHeight
	const int* getGids();
	// ����һ��GridID����
	// ��������Ҫ�ͷ�������ص�ָ��
	const int* copyGids();

	//  ɾ��ָ��λ�õ�Tile
	void removeTileAt(int x, int y);
	// ����ָ��Tileλ�ã���Tile���ڣ��������updateTileAt
	void setTileAt(int gid, int x, int y);
	// ����ָ��Tileλ�ã���Tile�����ڣ��������Tile
	void updateTileAt(int gid, int x, int y);
	// ��ȡָ��Tile���������Layer�����½�λ��
	CCPoint getPositionAt(int x, int y);
	// ����ָ��Tile����ɫ
	void setTileColorAt(ccColor4B c, int x, int y);
	
public:
	CC_SYNTHESIZE(int, m_layerWidth, LayerWidth);							// Layer��ȣ�Tiles����)
	CC_SYNTHESIZE(int, m_layerHeight, LayerHeight);							// Layer�߶ȣ�Tiles����)
	CC_SYNTHESIZE(int, m_tileWidth, TileWidth);								// Layer��ȣ�����ֵ)
	CC_SYNTHESIZE(int, m_tileHeight, TileHeight);							// Layer�߶ȣ�����ֵ)
	CC_SYNTHESIZE(int, m_minGid, MinGid);									// ��СGridID
	CC_SYNTHESIZE(int, m_maxGid, MaxGid);									// ���GridID
	CC_SYNTHESIZE(FKCW_TMX_MapInfo*, m_mapInfo, MapInfo);
	CC_SYNTHESIZE(FKCW_TMX_LayerInfo*, m_layerInfo, LayerInfo);
	CC_SYNTHESIZE(STileSetAtlasInfo*, m_atlasInfos, AtlasInfos);
	CC_SYNTHESIZE(FKCW_TMX_SpriteBatchNode**, m_batchNodes, BatchNodes);	// BatchNode��
	CC_SYNTHESIZE_BOOL(m_useAutomaticVertexZ, UseAutomaticVertexZ);			// �Զ������Zֵ
	CC_SYNTHESIZE(float, m_vertexZ, VertexZ);								// ������Ķ���Zֵ
	CC_SYNTHESIZE(float, m_alphaFuncValue, AlphaFuncValue);					// Alphaֵ
};
//-------------------------------------------------------------------------
class FKCW_TMX_SpriteBatchNode : public CCSpriteBatchNode
{
	friend class FKCW_TMX_Layer;
	
public:
    FKCW_TMX_SpriteBatchNode();
    virtual ~FKCW_TMX_SpriteBatchNode();

    static FKCW_TMX_SpriteBatchNode* createWithTexture(CCTexture2D* tex, unsigned int capacity);
    static FKCW_TMX_SpriteBatchNode* createWithTexture(CCTexture2D* tex) {
        return FKCW_TMX_SpriteBatchNode::createWithTexture(tex, kDefaultSpriteBatchCapacity);
    }

    static FKCW_TMX_SpriteBatchNode* create(const char* fileImage, unsigned int capacity);
    static FKCW_TMX_SpriteBatchNode* create(const char* fileImage) {
        return FKCW_TMX_SpriteBatchNode::create(fileImage, kDefaultSpriteBatchCapacity);
    }
};
//-------------------------------------------------------------------------