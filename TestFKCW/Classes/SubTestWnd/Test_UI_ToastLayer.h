//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_ToastLayer.h
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
class CTest_UI_ToastLayerLayer : public CCLayer
{
public:
	virtual bool init()
	{
		CCLabelTTF* pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҽ���ʾ��ʾ��").c_str(), "Arial", 36 );
		pLabel->setColor( ccc3(230,155,3) );

		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(pLabel, this, menu_selector(CTest_UI_ToastLayerLayer::ShowToastCallback));
		CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
		pMenu->setPosition( SCREEN_CENTER_POS + ccp( 0, -50 ));
		addChild(pMenu, 1);

		return true;
	}
public:
	void ShowToastCallback(CCObject* pSender)
	{
		CCSprite* pPanel = CCSprite::create( s_szSmallPanelPath );
		pPanel->setPosition( SCREEN_CENTER_POS + ccp(0, 50) );
		CCLabelTTF* pTitle = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("��ʾ").c_str(), "Arial", 36 );
		pTitle->setColor( ccRED );
		pTitle->setPosition( ccp( pPanel->getContentSize().width / 2 , pPanel->getContentSize().height / 2 + 50 ) );
		pPanel->addChild( pTitle );
		CCSprite* pSprite = CCSprite::create( s_szHalfPhotoPath );
		pSprite->setPosition( ccp( pPanel->getContentSize().width / 2 , pPanel->getContentSize().height / 2 ) );
		pSprite->setScale( 0.2f );
		pPanel->addChild( pSprite );
		CCLabelTTF* pInfo = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���� 3 ��").c_str(), "Arial", 26 );
		pInfo->setColor( ccWHITE );
		pInfo->setPosition( ccp( pPanel->getContentSize().width / 2 , pPanel->getContentSize().height / 2 - 60 ) );
		pPanel->addChild( pInfo );

		CCNode* pContextNode = CCNode::create();
		pContextNode->addChild( pPanel );

		FKCW_UI_ToastLayer* p = FKCW_UI_ToastLayer::Create( this, pContextNode, 0, 3.0f );
		// ע�⣺���ﲻҪaddChild����Ϊ�ڲ��Ѿ�addChild��ϡ�
	}
public:
	CREATE_FUNC( CTest_UI_ToastLayerLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, ToastLayer, �����򣺵�����ռ���㣬�������Ϣ�����ж�ѭ������ʾ��Ϣ���������á�)
//-------------------------------------------------------------------------