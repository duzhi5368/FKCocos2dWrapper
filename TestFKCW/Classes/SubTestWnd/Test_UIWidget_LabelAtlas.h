//*************************************************************************
//	��������:	2014-12-15
//	�ļ�����:	Test_UIWidget_LabelAtlas.h
//  �� �� ��:   WilhanTIan
//	��Ȩ����:	MIT
//	˵    ��:	
//  ���Խ��:		
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UIWidget_LabelAtlasLayer : public CCLayer
{
public:
	bool init()
	{
		//������������
		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		this->addChild(m_pWindow);

		m_atlas = FKCW_UIWidget_LabelAtlas::create("0123456789", s_szMathLabelAtlasPath, 15, 26, '0');
		m_atlas->setPosition(SCREEN_CENTER_POS);
		m_atlas->setOnClickListener(this,fkcw_uiwidget_click_selector(CTest_UIWidget_LabelAtlasLayer::onClick));
		m_atlas->setTouchEnabled(true);
		m_pWindow->addChild(m_atlas);


		m_label = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("").c_str(), "", 26);
		m_label->setColor(ccc3(230,255,3));
		m_label->setPosition(SCREEN_CENTER_POS + ccp(0,50));
		this->addChild(m_label);

		CCLabelTTF* label = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���Ҹı�����").c_str(), "", 26);
		label->setColor(ccc3(230,155,3));
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(CTest_UIWidget_LabelAtlasLayer::menuChangeValue));
		item->setPosition(CCPoint(0, -100));

		CCMenu* menu = CCMenu::create(item, NULL);
		this->addChild(menu);

		return true;
	}
public:
	void onClick(CCObject* pSender)
	{
		m_label->setString(FKCW_Base_StringConvert::a2u("���������").c_str());
	}
	void menuChangeValue(CCObject* pSender)
	{
		char buf[20];
		int i = static_cast<int>(FKCW_Base_Utils::RandomInRange(0.0f, 1000000.0f));
		sprintf(buf, "%d", i);
		m_atlas->setString(buf);
		m_label->setString("");
	}
public:
	CREATE_FUNC( CTest_UIWidget_LabelAtlasLayer );
public:
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	FKCW_UIWidget_LabelAtlas* m_atlas;
	CCLabelTTF* m_label; 
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UIWidget, LabelAtlas, ��̬��ǩ��)