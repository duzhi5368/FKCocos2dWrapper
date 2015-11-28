//*************************************************************************
//	��������:	2014-12-5
//	�ļ�����:	FKCW_UIWidget_Lua.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UIWidget_Macros.h"
//-------------------------------------------------------------------------
#if FKCW_WIDGET_USING_LUA
#ifdef __cplusplus
	extern "C" {
#endif
	#include "tolua++.h"
#ifdef __cplusplus
	}
#endif

TOLUA_API int FKCW_UIWidget_ToLua_Open(lua_State* tolua_S);
#endif
