/********************************************************************
	created:	2014/10/22
	created:	2014:10:22   23:08
	file base:	FKCocos2dxWrapper
	author:		FreeKnight
	
	purpose:	����Ψһͷ��
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
/*
	��Ƴ��ԣ���cocos2dx-2.x����չ��
	1��������Ⱦԭ��cocos2dxԴ���롣
	2������ʹ�õ������⣬��������������ʹ��
	���Ҫ��
	1���ļ��������㹻ע��˵������Ӣ�ľ��ɣ���
	2������һ�µı���淶��
	TODO:
	1: �����������SpriteX, Motion welder�ȸ�ʽ��֧��
	2��TMX��ͼ��ʽ֧��
	3�����°�ķ�װ�ͶԹ��°��Lua�ű�ע��
	4: ģ�������
	5��DargonBones��DebugDraw
*/
//--------------------------------------------------------------------
#pragma warning ( disable : 4251 )
//--------------------------------------------------------------------
#include "FKCW_Base/FKCW_Base.h"
#include "FKCW_IO/FKCW_IO.h"

#include "FKCW_Shader/FKCW_Shader.h"
#include "FKCW_Database/FKCW_Database.h"
#include "FKCW_Json/FKCW_Json.h"
#include "FKCW_Network/FKCW_Network.h"
#include "FKCW_SimpleNet/FKCW_SimpleNet.h"
#include "FKCW_Action/FKCW_Action.h"
#include "FKCW_RenderEx/FKCW_RenderEx.h"
#include "FKCW_UI/FKCW_UI.h"
#include "FKCW_GR/FKCW_GR.h"
#include "FKCW_SceneExMgr/FKCW_SceneExMgr.h"
#include "FKCW_EffectNode/FKCW_EffectNode.h"
#include "FKCW_UIWidget/FKCW_UIWidget.h"
#include "FKCW_3D/FKCW_3D.h"
#include "FKCW_TMX/FKCW_TMX.h"
#include "FKCW_Font/FKCW_Font.h"
#include "FKCW_RichHtml/FKCW_RichHtml.h"
#include "FKCW_Story/FKCW_Story.h"
#include "FKCW_Pixel/FKCW_Pixel.h"
//--------------------------------------------------------------------
// ������һЩȫ�ֵ���������
//--------------------------------------------------------------------
/*
// �����ֵΪ��0����LOG��¼ȫ�����ڴ���䡣
g_bISFlagAllocationLog = true;
// �Ƿ���FONT_debug
g_bIsFKCWFontDebug = true;
// �Ƿ���ʾ����Pixel��Χ��
g_isShowBoundingBox = true;
// �Ƿ����Pixel��DEBUGƬ����ɫ����
g_isPrintFragMat = false;
// �Ƿ���RichHtml��Debugģʽ
g_bIsFKCWRichHtmlDebug = true;

// �Ƿ�ʹ��RichHtml��Lua��Ϣ֪ͨ
#define  FKCW_RICHHTML_USING_LUA
// �Ƿ���DEBUG�ڴ����
#define FKCW_MEMORY_TRACKING
*/