//*************************************************************************
//	��������:	2014-12-4
//	�ļ�����:	FKCW_UIWidget_ToggleView.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
#include "FKCW_UIWidget_Widget.h"
#include "FKCW_UIWidget_Protocol.h"
#include "FKCW_UIWidget_Button.h"
//-------------------------------------------------------------------------
class FKCW_UIWidget_ToggleView : public FKCW_UIWidget_Button, public FKCW_UIWidget_CheckableProtocol
{
public:
	FKCW_UIWidget_ToggleView();
	virtual ~FKCW_UIWidget_ToggleView();

	static FKCW_UIWidget_ToggleView* create();
	static FKCW_UIWidget_ToggleView* create(const char* pNormal, const char* pSelected = NULL, const char* pDisabled = NULL);
	static FKCW_UIWidget_ToggleView* createWith9Sprite(const CCSize& tSize, const char* pNormal, const char* pSelected = NULL, const char* pDisabled = NULL);
	virtual void setEnabled(bool bEnabled);
	virtual void setChecked(bool bChecked);

public:
	virtual ENUM_WidgetTouchModel onTouchBegan(CCTouch *pTouch);
	virtual void onTouchMoved(CCTouch *pTouch, float fDuration);
	virtual void onTouchEnded(CCTouch *pTouch, float fDuration);
	virtual void onTouchCancelled(CCTouch *pTouch, float fDuration);
};