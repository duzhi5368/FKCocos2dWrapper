//*************************************************************************
//	��������:	2014-12-4
//	�ļ�����:	FKCW_UIWidget_Label.h
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
class FKCW_UIWidget_Label : public CCLabelTTF, public FKCW_UIWidget_Widget, 
	public FKCW_UIWidget_ClickableProtocol, public FKCW_UIWidget_LongClickableProtocol
{
public:
	FKCW_UIWidget_Label();
	virtual ~FKCW_UIWidget_Label();
	virtual bool init();
	static FKCW_UIWidget_Label* create();
	static FKCW_UIWidget_Label* create(const char *pString, const char *pFontName, float fFontSize);
	static FKCW_UIWidget_Label* create(const char *pString, const char *pFontName, float fFontSize,
		const CCSize& tDimensions, CCTextAlignment hAlignment);
	static FKCW_UIWidget_Label* create(const char *pString, const char *pFontName, float fFontSize,
		const CCSize& tDimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment);

public:
	virtual ENUM_WidgetTouchModel onTouchBegan(CCTouch* pTouch);
	virtual void onTouchMoved(CCTouch* pTouch, float fDuration);
	virtual void onTouchEnded(CCTouch* pTouch, float fDuration);
	virtual void onTouchCancelled(CCTouch* pTouch, float fDuration);

	FKCW_UIWIDGET_LONGCLICK_SCHEDULE(FKCW_UIWidget_Label);
};