//*************************************************************************
//	��������:	2014-12-5
//	�ļ�����:	FKCW_UIWidget_PageView.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
#include "FKCW_UIWidget_Widget.h"
#include "FKCW_UIWidget_Protocol.h"
#include "FKCW_UIWidget_TableView.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
class FKCW_UIWidget_PageViewCell : public FKCW_UIWidget_TableViewCell
{
public:
	FKCW_UIWidget_PageViewCell(){};
};
//-------------------------------------------------------------------------
class FKCW_UIWidget_PageView : public FKCW_UIWidget_TableView, public FKCW_UIWidget_PageChangeableProtocol
{
public:
	FKCW_UIWidget_PageView();
	static FKCW_UIWidget_PageView* create(const CCSize& tPageSize);
	static FKCW_UIWidget_PageView* create(const CCSize& tPageSize, unsigned int uPageCount,
		CCObject* pListener, SEL_DataSoucreAdapterHandler pHandler);

protected:
	virtual void onScrolling();
	virtual void updateCellAtIndex(unsigned int idx);
};