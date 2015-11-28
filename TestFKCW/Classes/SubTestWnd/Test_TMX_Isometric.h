//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	Test_TMX_Isometric.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_TMX_IsometricLayer : public CCLayer
{
public:
	FKCW_TMX_Map* createMap()
	{
		return FKCW_TMX_Map::createWithXMLFile( s_szIsoMapFile );
	}
public:
	virtual bool init()
	{
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		// ���Map
		m_map = createMap();
		m_map->setPosition(ccp( SCREEN_CENTER_POS_X / 2, SCREEN_CENTER_POS_Y / 2 ));
		m_map->setDebugDrawObjects(true);
		addChild(m_map);

		// ������ʾ
		m_sprite = CCSprite::create( s_szLetterAImagePath );
		m_sprite->setVisible(false);
		m_sprite->setScale( 0.372f );
		m_map->addChild(m_sprite, MAX_INT);

		setTouchEnabled(true);
		setTouchMode(kCCTouchesOneByOne);

		FKCW_TMX_ObjectGroup* og = m_map->getObjectGroup("Object Layer 1");
		FKLOG( "���������ԣ�weather=%s", og->getProperty("weather").c_str());
		FKLOG( "������� = %d", og->getObjectCount());
		FKCW_TMX_Object* obj = og->getObjectAt(0);
		FKLOG("��һ�������� = %s, ���� = %s, ����: favorite = %s",
			obj->getName().c_str(),
			obj->getType().c_str(),
			obj->getProperty("favorite").c_str());

		return true;
	}
public:
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
	{
		m_lastLoc = pTouch->getLocation();

		FKCW_TMX_Layer* layer = m_map->getLayerAt(0);
		CCPoint loc = layer->convertToNodeSpace(m_lastLoc);
		CCPoint d = layer->getTileCoordinateAt(loc.x, loc.y);
		CCPoint pos = layer->getPositionAt(static_cast<int>(d.x), static_cast<int>(d.y));
		if(d.x != -1) {
			m_sprite->setVisible(true);
			m_sprite->setPosition(ccp(pos.x + layer->getTileWidth() / 2, pos.y + layer->getTileHeight() / 2));
		} else {
			m_sprite->setVisible(false);
		}

		return true;
	}
public:
	CREATE_FUNC( CTest_TMX_IsometricLayer );
protected:
	CCSprite* m_sprite;
	FKCW_TMX_Map* m_map;
	CCPoint m_lastLoc;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(TMX, Isometric, б45�ȵ�ͼ����)
//-------------------------------------------------------------------------