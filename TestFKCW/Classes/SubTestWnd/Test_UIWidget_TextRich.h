//*************************************************************************
//	��������:	2014-12-15
//	�ļ�����:	Test_UIWidget_TextRich.h
//  �� �� ��:   WilhanTIan
//	��Ȩ����:	MIT
//	˵    ��:	���ı�
//  ���Խ��:		
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UIWidget_TextRichLayer : public CCLayer
{
public:
	bool init()
	{
		//������������
		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		this->addChild(m_pWindow);

		FKCW_UIWidget_TextRich* textRich = FKCW_UIWidget_TextRich::create();
		textRich->setPosition(SCREEN_CENTER_POS);
		textRich->setFontSize(12);
		textRich->setFontName("Arial");
		textRich->setMaxLineLength(20);
		textRich->setVerticalSpacing(15.0f);
		textRich->setOnTextRichClickListener(this, fkcw_uiwidget_textrichclick_selector(CTest_UIWidget_TextRichLayer::onClickTextRich));

		textRich->insertElement(FKCW_Base_StringConvert::a2u("����һ��Ĭ�ϰ�ɫ����").c_str());
		textRich->insertElement(FKCW_Base_StringConvert::a2u("��ɫ-��ɫ-�ֺ�-24 ").c_str(), "", 24, ccYELLOW, FKCW_Base_StringConvert::a2u("�����˻�ɫ����").c_str());
		CCSprite* pIcon = CCSprite::create(s_szEmoticon);
		pIcon->runAction(CCRepeatForever::create(CCBlink::create(1.0f, 5)));
		textRich->insertElement(pIcon, 0, FKCW_Base_StringConvert::a2u("�����˱���").c_str());
		textRich->insertElement(FKCW_Base_StringConvert::a2u("������ ").c_str(), "", 30, ccMAGENTA, FKCW_Base_StringConvert::a2u("�����˷ۺ�����").c_str());
		textRich->insertElement(FKCW_Base_StringConvert::a2u("���ÿ�θ��ı����������ͬ�¼�Ŷ").c_str(), "", 26, ccBLUE, FKCW_Base_StringConvert::a2u("��������ɫ����").c_str());
		
		textRich->reloadData();
		m_pWindow->addChild(textRich);


		m_label = CCLabelTTF::create("", "", 26);
		m_label->setColor(ccBLACK);
		m_label->setPosition(SCREEN_CENTER_POS + CCPoint(0, -150));
		this->addChild(m_label);

		return true;
	}
public:
	void onClickTextRich(CCObject* pSender, const char* description)
	{
		if(description == NULL)
			m_label->setString(FKCW_Base_StringConvert::a2u("�����ĸ��ı�û����������").c_str());
		else
			m_label->setString(description);
	}
public:
	CREATE_FUNC( CTest_UIWidget_TextRichLayer );
protected:
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	CCLabelTTF* m_label;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UIWidget, TextRich, ���ı�)