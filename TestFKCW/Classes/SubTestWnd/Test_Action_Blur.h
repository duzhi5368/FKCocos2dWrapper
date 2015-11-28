//*************************************************************************
//	��������:	2014-12-12
//	�ļ�����:	Test_Action_Blur.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	ģ����������
//*************************************************************************
#pragma once
//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Action_BlurLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_pSprite = CCSprite::create(s_szHalfPhotoPath);
		m_pSprite->setPosition(SCREEN_CENTER_POS - ccp(200,0));
		this->addChild(m_pSprite);

		CCLabelTTF* lable = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҶԳ����еľ���ִ��ģ������").c_str(), "Arial", 26 );
		lable->setColor(ccc3(230,155,3));

		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
			s_szArmatureCowboyPic, s_szArmatureCowboyPlist, s_szArmatureCowboy);
		CCArmature* armature = CCArmature::create("Cowboy");
		armature->getAnimation()->playWithIndex(0);
		armature->setPosition(SCREEN_CENTER_POS + ccp(200,0));
		armature->setScale(0.2f);
		addChild(armature);

		armature->runAction(CCRepeatForever::create(CCSequence::create(
			FKCW_Action_Blur::Create(1, CCSizeZero, CCSizeMake(5, 5)),
			FKCW_Action_Blur::Create(1, CCSizeMake(5, 5), CCSizeZero),
			NULL)));

		CCMenuItemLabel* itemLable = CCMenuItemLabel::create(lable, this, menu_selector(CTest_Action_BlurLayer::menuCallFunc));
		CCMenu* menu = CCMenu::create(itemLable, NULL);
		menu->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		this->addChild(menu);

		return true;
	}
public:
	void menuCallFunc(CCObject* pSender)
	{
		m_pSprite->runAction(FKCW_Action_Blur::Create(1.0f, CCSize(2, 2), CCSize(30, 30)));
	}
public:
	CREATE_FUNC( CTest_Action_BlurLayer );
private:
	CCSprite* m_pSprite;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, Blur, �ڵ�ģ������)
//-------------------------------------------------------------------------