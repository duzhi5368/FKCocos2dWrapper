//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_UIWidget.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	��Cocos2dx��UI��չ�⣬�����һϵ��UI�ؼ���
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_UIWidget_Protocol
		�����Ϣ�������
	FKCW_UIWidget_Widget
		�������
	FKCW_UIWidget_Scale9Sprite
		������������֧��
	FKCW_UIWidget_ColorView
		ɫ��
	FKCW_UIWidget_GradientView
		����ɫ��

	�����
		FKCW_UIWidget_WidgetWindow
			���������
		FKCW_UIWidget_Label
			��̬��ǩ��
		FKCW_UIWidget_LabelAtlas
			��̬��ǩ������������
		FKCW_UIWidget_LabelBMFont
			ʹ����ͼʽ�ľ�̬��ǩ
		FKCW_UIWidget_Button
			��ť��
		FKCW_UIWidget_ToggleView
			���ذ�ť��
		FKCW_UIWidget_Layout
			�����㣬�ؼ������ؼ�
		FKCW_UIWidget_ScrollView
			������������
		FKCW_UIWidget_TableView
			��ֱ��
		FKCW_UIWidget_GridPageView
			����ҳ��������������
		FKCW_UIWidget_GridView
			���������ؼ�
		FKCW_UIWidget_ImageView
			ͼƬ�ؼ�
		FKCW_UIWidget_ImageViewScale9
			�Ź�ͼƬ�ؼ�
		FKCW_UIWidget_PageView
			ҳ�滬���������ؼ�
		FKCW_UIWidget_ListView
			����������
		FKCW_UIWidget_CheckBox
			ѡ���
		FKCW_UIWidget_ControlView
			��Ϸ������
		FKCW_UIWidget_ProgressBar
			������
		FKCW_UIWidget_Slider
			������
		FKCW_UIWidget_TextRich
			���ı�
		FKCW_UIWidget_ExpandableListView
			��չ���������б�����
====================================
������Ŀ/�⣺
====================================
	FKCW_Base
====================================
todo:
====================================
	Lua֧�֣�ʹ��ToLua++
*/ 
//-------------------------------------------------------------------------
#include "Include/FKCW_UIWidget_Protocol.h"
#include "Include/FKCW_UIWidget_Widget.h"
#include "Include/FKCW_UIWidget_Scale9Sprite.h"
#include "Include/FKCW_UIWidget_ColorView.h"
#include "Include/FKCW_UIWidget_GradientView.h"

#include "Include/FKCW_UIWidget_WidgetWindow.h"
#include "Include/FKCW_UIWidget_Label.h"
#include "Include/FKCW_UIWidget_LabelAtlas.h"
#include "Include/FKCW_UIWidget_LabelBMFont.h"
#include "Include/FKCW_UIWidget_Button.h"
#include "Include/FKCW_UIWidget_ToggleView.h"
#include "Include/FKCW_UIWidget_Layout.h"
#include "Include/FKCW_UIWidget_ScrollView.h"
#include "Include/FKCW_UIWidget_TableView.h"
#include "Include/FKCW_UIWidget_GridPageView.h"
#include "Include/FKCW_UIWidget_GridView.h"
#include "Include/FKCW_UIWidget_ImageView.h"
#include "Include/FKCW_UIWidget_ImageViewScale9.h"
#include "Include/FKCW_UIWidget_PageView.h"
#include "Include/FKCW_UIWidget_ListView.h"
#include "Include/FKCW_UIWidget_CheckBox.h"
#include "Include/FKCW_UIWidget_ControlView.h"
#include "Include/FKCW_UIWidget_ProgressBar.h"
#include "Include/FKCW_UIWidget_Slider.h"
#include "Include/FKCW_UIWidget_TextRich.h"
#include "Include/FKCW_UIWidget_ExpandableListView.h"