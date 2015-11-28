//*************************************************************************
//	��������:	2014-10-30
//	�ļ�����:	FKCW_Json_Parser.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Json_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Json_Parser
{
public:
	// ����һ���ڴ��е�json�ַ���
	static CCObject*		Load( const char* p_szJsonString, size_t p_unLength );
	// ����һ��json�ļ�
	static CCObject*		Load( const string& p_szPath );
};