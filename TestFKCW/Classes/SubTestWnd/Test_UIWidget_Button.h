//*************************************************************************
//	��������:	2014-12-12
//	�ļ�����:	Test_UIWidget_Button.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	UIWidget��ť
//  ���Խ��:	
//*************************************************************************

#pragma once

#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"

class CTest_UIWidget_ButtonLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		addChild(m_pWindow);

		m_pButton = FKCW_UIWidget_Button::create(s_szButtonNormalPath, s_szButtonPressPath, s_szButtonDisablePath);
		m_pButton->initText(FKCW_Base_StringConvert::a2u("���ǰ�ť").c_str(), "", 28);
		m_pButton->setPosition(SCREEN_CENTER_POS);
		//�󶨵���¼�
		m_pButton->setOnClickListener(this, fkcw_uiwidget_click_selector(CTest_UIWidget_ButtonLayer::onClickListener));
		//�󶨳����¼�
		m_pButton->setOnLongClickListener(this, fkcw_uiwidget_longclick_selector(CTest_UIWidget_ButtonLayer::onLongClickListener));
		m_pWindow->addChild(m_pButton);

		m_pButton->setOnTouchBeganListener(this, fkcw_uiwidget_touchbegan_selector(CTest_UIWidget_ButtonLayer::onTouchBegan));
		m_pButton->setOnTouchMovedListener(this, fkcw_uiwidget_touchevent_selector(CTest_UIWidget_ButtonLayer::onTouchMoved));
		m_pButton->setOnTouchEndedListener(this, fkcw_uiwidget_touchevent_selector(CTest_UIWidget_ButtonLayer::onTouchEnded));
		m_pButton->setOnTouchCancelledListener(this, fkcw_uiwidget_touchevent_selector(CTest_UIWidget_ButtonLayer::onTouchCancelled));

		m_pInfo = FKCW_UIWidget_Label::create(FKCW_Base_StringConvert::a2u("��Ϣ������Ϣ��").c_str(), "Altas", 26 );
		m_pInfo->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		m_pWindow->addChild( m_pInfo );

		m_pInfo2 = FKCW_UIWidget_Label::create(FKCW_Base_StringConvert::a2u("��Ϣ������Ϣ��2").c_str(), "Altas", 26 );
		m_pInfo2->setPosition(SCREEN_CENTER_POS + CCPoint(0, -250));
		m_pWindow->addChild( m_pInfo2 );

		return true;
	}
public:
	virtual void onClickListener(CCObject* pSender)
	{
		if( m_pInfo )
			m_pInfo->setString(FKCW_Base_StringConvert::a2u("������Ϣ").c_str());
	}
	virtual bool onLongClickListener(CCObject* pSender, CCTouch* pTouch)
	{
		if( m_pInfo )
			m_pInfo->setString(FKCW_Base_StringConvert::a2u("������Ϣ").c_str());
		//���ð�ť
		m_pButton->setEnabled(false);

		//����true���������click�¼������򲻲����¼�
		return false;
	}
	ENUM_WidgetTouchModel onTouchBegan(CCObject* pSender, CCTouch* pTouch)
	{
		if( m_pInfo2 )
			m_pInfo2->setString(FKCW_Base_StringConvert::a2u("Down��Ϣ").c_str());
		return eWidgetTouchTransient;
	}
	bool onTouchMoved(CCObject* pSender, CCTouch* pTouch, float fDuration)
	{
		if( m_pInfo2 )
			m_pInfo2->setString(FKCW_Base_StringConvert::a2u("Moved��Ϣ").c_str());
		return true;
	}
	bool onTouchEnded(CCObject* pSender, CCTouch* pTouch, float fDuration)
	{
		if( m_pInfo2 )
			m_pInfo2->setString(FKCW_Base_StringConvert::a2u("Ended��Ϣ").c_str());
		return true;
	}
	bool onTouchCancelled(CCObject* pSender, CCTouch* pTouch, float fDuration)
	{
		if( m_pInfo2 )
			m_pInfo2->setString(FKCW_Base_StringConvert::a2u("Cancelled��Ϣ").c_str());
		return true;
	}
public:
	CREATE_FUNC( CTest_UIWidget_ButtonLayer );
private:
	FKCW_UIWidget_Button* m_pButton;
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	FKCW_UIWidget_Label* m_pInfo;
	FKCW_UIWidget_Label* m_pInfo2;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UIWidget, Button, UIWidget��ť|������ť�����øð�ť)