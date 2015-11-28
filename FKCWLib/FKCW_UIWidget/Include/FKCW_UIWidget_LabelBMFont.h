//*************************************************************************
//	��������:	2014-12-4
//	�ļ�����:	FKCW_UIWidget_LabelBMFont.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
#include "FKCW_UIWidget_Widget.h"
#include "FKCW_UIWidget_Protocol.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class FKCW_UIWidget_LabelBMFont : public CCLabelBMFont
	, public FKCW_UIWidget_Widget
	, public FKCW_UIWidget_ClickableProtocol
	, public FKCW_UIWidget_LongClickableProtocol
{
public:
	FKCW_UIWidget_LabelBMFont();
	virtual ~FKCW_UIWidget_LabelBMFont();
	virtual bool init();
	static FKCW_UIWidget_LabelBMFont* create(const char *pString, const char *fntFile, float width, CCTextAlignment alignment, CCPoint imageOffset);
	static FKCW_UIWidget_LabelBMFont* create(const char *pString, const char *fntFile, float width, CCTextAlignment alignment);
	static FKCW_UIWidget_LabelBMFont* create(const char *pString, const char *fntFile, float width);
	static FKCW_UIWidget_LabelBMFont* create(const char *pString, const char *fntFile);
	static FKCW_UIWidget_LabelBMFont* create();

public:
	virtual ENUM_WidgetTouchModel onTouchBegan(CCTouch *pTouch);
	virtual void onTouchMoved(CCTouch *pTouch, float fDuration);
	virtual void onTouchEnded(CCTouch *pTouch, float fDuration);
	virtual void onTouchCancelled(CCTouch *pTouch, float fDuration);

	FKCW_UIWIDGET_LONGCLICK_SCHEDULE(FKCW_UIWidget_LabelBMFont);
};
