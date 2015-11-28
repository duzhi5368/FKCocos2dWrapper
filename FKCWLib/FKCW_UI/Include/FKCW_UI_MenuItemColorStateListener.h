//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_UI_MenuItemColorStateListener.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
// �������� FKCW_UI_MenuItemColor �ؼ��¼��Ľӿ���
// �û���������²���Ҫʹ�ø��࣬����FKCW_UI_MenuItemColor�ڲ�ʹ�á�
class FKCW_UI_MenuItemColor;
class FKCW_UI_MenuItemColorStateListener
{
public:
	virtual void onMenuItemColorSelected(FKCW_UI_MenuItemColor* item) = 0;
	virtual void onMenuItemColorDeselected(FKCW_UI_MenuItemColor* item) = 0;
	virtual void onMenuItemColorFocused(FKCW_UI_MenuItemColor* item) = 0;
	virtual void onMenuItemColorUnfocused(FKCW_UI_MenuItemColor* item) = 0;
	virtual void onMenuItemColorEnabled(FKCW_UI_MenuItemColor* item) = 0;
	virtual void onMenuItemColorDisabled(FKCW_UI_MenuItemColor* item) = 0;
};