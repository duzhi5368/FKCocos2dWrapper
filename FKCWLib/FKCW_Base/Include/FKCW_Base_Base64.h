/********************************************************************
	created:	2014/10/27
	file base:	FKCW_Base_Base64
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//--------------------------------------------------------------------
class FKCW_Base_Base64
{
public:
	// ����һ������
	static string Encode( const void* p_pData, int p_nLen );
	// ����һ������
	static const char* Decode( const string& p_strData, int* p_pOutLen );
	// ����һ�����ݣ���˻Ჹ'/0'��������
	static const char* DecodeAsCString( const string& p_strData, int* p_pOutLen );
};