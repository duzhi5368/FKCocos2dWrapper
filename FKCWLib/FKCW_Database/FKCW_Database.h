/********************************************************************
	created:	2014/10/30
	file base:	FKCW_Database
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
/* 
====================================
ģ��˵����	
====================================
	sqlite3�ķ�װ�����������ݿ�ĸ��ֲ�����
====================================
�ڲ��ļ�����˵����
====================================
	FKCW_Database_Database
		����sqlite3���ݿ����Ψһ�ӿ��ࡣ
====================================
������Ŀ/�⣺
====================================
	sqlite3
	FKCW_Base
====================================
todo:
====================================

*/
//--------------------------------------------------------------------
#include "Include/FKCW_Database_Database.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Include/Android/sqlite3.h"
#endif