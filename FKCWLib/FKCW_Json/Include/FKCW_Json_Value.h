//*************************************************************************
//	��������:	2014-10-30
//	�ļ�����:	FKCW_Json_Value.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Json_Array.h"
#include "FKCW_Json_Object.h"
#include "FKCW_Json_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Json_Value
{
public:
	// ת��Ϊ bool
	static bool			CastToBool( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ int
	static int			CastToInt( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ long
	static long			CastToLong( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ float
	static float		CastToFloat( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ double
	static double		CastToDouble( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ json object
	static FKCW_Json_Object*	CastToObject( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ json array
	static FKCW_Json_Array*		CastToArray( FKCW_Json_Object::SKeyValue& p_KV );
	// ת��Ϊ string
	static const char*			CastToString( FKCW_Json_Object::SKeyValue& p_KV );
};