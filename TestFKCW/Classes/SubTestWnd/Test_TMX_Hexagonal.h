//*************************************************************************
//	��������:	2014-12-29
//	�ļ�����:	Test_TMX_Hexagonal.h
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
class CTest_TMX_HexagonalLayer : public CCLayer
{
public:
	FKCW_TMX_Map* createMap()
	{
		return FKCW_TMX_Map::createWithXMLFile( s_szHexaMapFile );
	}
public:
	virtual bool init()
	{
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		// ���Map
		m_map = createMap();
		m_map->setPosition(ccp( SCREEN_CENTER_POS_X / 2, 0 ));
		m_map->setDebugDrawObjects(true);
		addChild(m_map);

		// ������ʾ
		m_sprite = CCSprite::create( s_szLetterAImagePath );
		m_sprite->setVisible(false);
		m_map->addChild(m_sprite, MAX_INT);

		setTouchEnabled(true);
		setTouchMode(kCCTouchesOneByOne);

		return true;
	}
public:
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
	{
		m_lastLoc = pTouch->getLocation();

		FKCW_TMX_Layer* layer = (FKCW_TMX_Layer*)m_map->getLayerAt(0);
		CCPoint loc = layer->convertToNodeSpace(m_lastLoc);
		CCPoint d = layer->getTileCoordinateAt(loc.x, loc.y);

		// ���Ͼ���
		CCPoint pos = layer->getPositionAt(static_cast<int>(d.x), static_cast<int>(d.y));
		if(d.x != -1) {
			m_sprite->setVisible(true);
			m_sprite->setPosition(ccp(pos.x + layer->getTileWidth() / 2,
				pos.y + layer->getTileHeight() / 2));
		} else {
			m_sprite->setVisible(false);
		}

		// ִ����ת
		CCSprite* sprite = layer->tileAt(static_cast<int>(d.x), static_cast<int>(d.y));
		if(sprite) {
			sprite->stopAllActions();
			sprite->setRotation(0);
			CCRotateBy* rotate = CCRotateBy::create(2.f, 360);
			sprite->runAction(rotate);
		}
		return true;
	}
public:
	CREATE_FUNC( CTest_TMX_HexagonalLayer );
protected:
	CCSprite* m_sprite;
	FKCW_TMX_Map* m_map;
	CCPoint m_lastLoc;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(TMX, Hexagonal, �����ε�ͼ���ԣ���������ת)
//-------------------------------------------------------------------------