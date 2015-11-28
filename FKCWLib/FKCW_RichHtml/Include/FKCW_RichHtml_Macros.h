//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_RichHtml_Macros.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCW_Base/FKCW_Base.h"
#include "../../FKCW_Font/FKCW_Font.h"
#include <list>
using std::list;
//-------------------------------------------------------------------------
static const int ZORDER_CONTEXT		= 100;
static const int ZORDER_OVERLAY		= 0;
static const int ZORDER_BACKGROUND	= -100;
//-------------------------------------------------------------------------
// �Ƿ���RichHtml��Debugģʽ
extern bool g_bIsFKCWRichHtmlDebug;
// �Ƿ�ʹ��Lua֧��
#define FKCW_RICHHTML_USING_LUA 0
//-------------------------------------------------------------------------