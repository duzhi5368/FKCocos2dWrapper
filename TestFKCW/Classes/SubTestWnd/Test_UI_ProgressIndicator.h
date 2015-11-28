//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_ProgressIndicator.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	������ʾ������
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UI_ProgressIndicatorLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_pMenu = CCMenu::create();
		m_pMenu->setPosition(CCPointZero);
		addChild(m_pMenu);

		CCMenuItemImage* pBtn = CCMenuItemImage::create(s_szToggle1Path, s_szToggle2Path);
		pBtn->setTarget(this, menu_selector(CTest_UI_ProgressIndicatorLayer::onBegin));
		pBtn->setPosition(SCREEN_CENTER_POS + ccp(0, -50));
		m_pMenu->addChild(pBtn);
		

		onBegin(NULL);
		
		return true;
	}

public:
	CREATE_FUNC( CTest_UI_ProgressIndicatorLayer );
public:
	void onBegin(CCObject* sender)
	{
		if (m_pMenu)
		{
			m_pMenu->setVisible(false);
		}

		FKCW_UI_ProgressIndicator* progressIndicator = FKCW_UI_ProgressIndicator::CreateInstance( "This is a progressIndicator", this );
		progressIndicator->setPanelColor( ccc4(255, 0, 0,255) );
		runAction(CCSequence::create(CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::changeMessage)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::changePanelColor)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::changeDimColor)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::forceSquare)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::changeIcon)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::beforeHide)),
			CCDelayTime::create(2),
			CCCallFunc::create(this, callfunc_selector(CTest_UI_ProgressIndicatorLayer::hide)),
			NULL));
	}

	void changeMessage() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setMessage( FKCW_Base_StringConvert::a2u("�������ʱ�ı���ʾ��Ϣ"));
	}

	void changeDimColor() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setMessage(FKCW_Base_StringConvert::a2u("���Ըı����屳��ɫ"));
		hud->setDimColor(ccc4(0, 0, 200, 100));
	}

	void changePanelColor() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setMessage(FKCW_Base_StringConvert::a2u("���Ըı���屳��ɫ"));
		hud->setPanelColor(ccc4(127, 183, 90, 200));
	}

	void forceSquare() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setMessage(FKCW_Base_StringConvert::a2u("ǿ��Ϊ������"));
		hud->setForceSquare(true);
	}

	void changeIcon() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setMessage(FKCW_Base_StringConvert::a2u("����ʹ���Զ���ͼ��"));
		hud->setIcon(CCSprite::create(s_szLetterAImagePath));
	}

	void beforeHide() {
		FKCW_UI_ProgressIndicator* hud = FKCW_UI_ProgressIndicator::GetInstance();
		hud->setIcon(NULL);
		hud->setMessage(FKCW_Base_StringConvert::a2u("2�����ʧ"));
	}

	void hide() {
		FKCW_UI_ProgressIndicator::Hide();

		if (m_pMenu)
		{
			m_pMenu->setVisible(true);
		}
	}

private:
	CCMenu* m_pMenu;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, ProgressIndicator, ������ʾ�� ��Ĭ�϶��������Ըı䱳����ɫ����ʾ�������ı������ʾ����״)
//-------------------------------------------------------------------------