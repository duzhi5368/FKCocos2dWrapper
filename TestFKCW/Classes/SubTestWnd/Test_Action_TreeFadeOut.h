//*************************************************************************
//	��������:	2014-12-12
//	�ļ�����:	Test_Action_TreeFadeOut.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	���Խڵ��������Ըýڵ�������ӽڵ�
//  ���Խ��: 
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Action_TreeFadeOutLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_pRootSprite = CCSprite::create(s_szLetterAImagePath);
		CCSprite* pSpriteB = CCSprite::create(s_szLetterBImagePath);
		CCSprite* pSpriteC = CCSprite::create(s_szLetterCImagePath);
		
		m_pRootSprite->setPosition(SCREEN_CENTER_POS);
		
		this->addChild(m_pRootSprite);
		m_pRootSprite->addChild(pSpriteB);
		pSpriteB->addChild(pSpriteC);

		CCLabelTTF* lable = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҶԾ���Aִ�н�������").c_str(), "Arial", 26 );
		lable->setColor(ccc3(230,155,3));

		CCMenuItemLabel* itemLable = CCMenuItemLabel::create(lable, this, menu_selector(CTest_Action_TreeFadeOutLayer::menuCallFunc));
		CCMenu* menu = CCMenu::create(itemLable, NULL);
		menu->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		this->addChild(menu);

		return true;
	}
public:
	void menuCallFunc(CCObject* pSender)
	{
		m_pRootSprite->runAction(FKCW_Action_TreeFadeOut::Create(3.0f));
	}
public:
	CREATE_FUNC( CTest_Action_TreeFadeOutLayer );
private:
	CCSprite* m_pRootSprite;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, TreeFadeOut, �����ڵ����������ýڵ�������ӽڵ㣨A�Ǹ��ڵ㡢B�ĸ��ڵ���A��C�ĸ��ڵ���B��)
//-------------------------------------------------------------------------