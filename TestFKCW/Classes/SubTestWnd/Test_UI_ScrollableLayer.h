//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_ScrollableLayer.h
//  �� �� ��:   WilhanTian
//	��Ȩ����:	MIT
//	˵    ��:	���������
//	���� ���:	��������	ENUM_ScrollableLayerBindingType ����˼
//				�������϶���ʱ�� ���ȴ�������ϽǶ���
//				
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UI_ScrollableLayerLayer : public CCLayer
{
public:
	virtual bool init()
	{
		FKCW_UI_ScrollableLayer* scrollableLayer = FKCW_UI_ScrollableLayer::create(CCSize(SCERRN_WIDTH, SCERRN_HEIGHT),
			CCSize(SCERRN_WIDTH*2, SCERRN_HEIGHT*2), 
			ENUM_ScrollableLayerBindingType::eScrollableLayerBindingType_BottomRight);
		scrollableLayer->setPosition(SCREEN_CENTER_POS);
		
		CCSprite* sp1 = CCSprite::create(s_szLetterAImagePath);
		CCSprite* sp2 = CCSprite::create(s_szHalfPhotoPath);
		CCSprite* sp3 = CCSprite::create(s_szLetterCImagePath);
		
		sp1->setPosition(SCREEN_LEFT_DOWN_POS);
		sp2->setPosition(SCREEN_CENTER_POS);
		sp3->setPosition(SCREEN_RIGHT_UP_POS);

		scrollableLayer->addChild(sp1);
		scrollableLayer->addChild(sp2);
		scrollableLayer->addChild(sp3);
		
		this->addChild(scrollableLayer);

		return true;
	}
public:
	CREATE_FUNC( CTest_UI_ScrollableLayerLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, ScrollableLayer, ������ - �û������϶��Ķ�̬�㣬���������ε�ͼ�Ĳ�����ʽ)
//-------------------------------------------------------------------------