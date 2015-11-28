//*************************************************************************
//	��������:	2014-12-22
//	�ļ�����:	Test_Base_Localization.h
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
class CTest_Base_LocalizationLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_bIsEnglish = false;

		FKCW_Base_Localization* pInstance = FKCW_Base_Localization::GetInstance();
		pInstance->AddPlatformString( "en", s_szLocaliztionENFile, false );
		pInstance->AddPlatformString( "zh", s_szLocaliztionZHFile, false );

		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		addChild(m_pWindow);

		m_pButtonChangeLan = FKCW_UIWidget_Button::createWith9Sprite(CCSize(250, 50),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pButtonChangeLan->setPosition(SCREEN_CENTER_POS+ccp(0, 100));
		m_pButtonChangeLan->setOnClickListener(this, fkcw_uiwidget_click_selector(CTest_Base_LocalizationLayer::onChangeLan));
		m_pButtonChangeLan->initText(FKCW_Base_StringConvert::a2u("��������").c_str(), "", 30);
		m_pWindow->addChild(m_pButtonChangeLan);

		FKCW_UIWidget_Label* pInfoLabel = FKCW_UIWidget_Label::create(
			FKCW_Base_StringConvert::a2u("��ť���ֶ��� Resource/strings.xml ").c_str(), "", 30.0f);
		pInfoLabel->setPosition(SCREEN_CENTER_POS+ccp(0, -100));
		m_pWindow->addChild(pInfoLabel);

		return true;
	}
public:
	void onChangeLan(CCObject* pSender)
	{
		m_bIsEnglish = (!m_bIsEnglish);
		if( m_bIsEnglish )
		{
			m_pButtonChangeLan->setText( FKCW_Base_StringConvert::a2u( 
				FKCW_Base_Localization::GetInstance()->GetString("ChangeLan", "en").c_str() ).c_str() );
		}
		else
		{
			m_pButtonChangeLan->setText( FKCW_Base_StringConvert::a2u( FKCW_LocCharPtr("ChangeLan") ).c_str() );
		}
	}
public:
	CREATE_FUNC( CTest_Base_LocalizationLayer );
private:
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	FKCW_UIWidget_Button*		m_pButtonChangeLan;
	bool						m_bIsEnglish;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Base, Localization, ����Ӧ������Ա�)
//-------------------------------------------------------------------------