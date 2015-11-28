//*************************************************************************
//	��������:	2014-10-30
//	�ļ�����:	FKCW_Json_Object.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Json_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Json_Array;
//-------------------------------------------------------------------------
class FKCW_Json_Object : public CCObject
{
public:
	// Jsonֵ����
	enum ENUM_JsonValueType
	{
		eJsonValueType_Nil		= 0,
		eJsonValueType_Boolean,
		eJsonValueType_String,
		eJsonValueType_Object,
		eJsonValueType_Array,
	};

	// JsonValueֵ�ṹ
	union Value
	{
		bool b;
		const char* s;
		FKCW_Json_Object* jo;
		FKCW_Json_Array* ja;
	};

	// JsonKeyֵ�ṹ
	struct SKeyValue
	{
		const char* k;
		ENUM_JsonValueType t;
		Value v;
	};
private:
	typedef map<string, SKeyValue>	PairMap;
	PairMap			m_mapPairs;				// Json��ֵ��
	typedef vector<SKeyValue>		KeyValueList;
	KeyValueList	m_vecKeyValues;			// Json������
protected:
	FKCW_Json_Object();
	// ת��һ��CCObjectΪFKCW_Json_Object����
	// ������ת�������������ᱻ��䵽�����С���CCObject��һ�����飬�����Ϊһ����Ϊ��array����������䵽json��
	static FKCW_Json_Object*		SafeCast( CCObject* p_pObj );
	// �ͷ�ָ����ֵ
	static void						ReleaseKeyValue( const string& p_strKey, SKeyValue& p_KeyValue );
public:
	virtual ~FKCW_Json_Object();
	// ����һ����json����
	static FKCW_Json_Object* Create();
	// ����һ��json��ʽ���ڴ��ַ���
	// �����json�ڴ���һ�����飬��������齫����Ϊһ����Ϊ"array"���������
	static FKCW_Json_Object* Create( const char* p_szJson, size_t p_unLength );
	// ����һ��json��ʽ���ļ�
	static FKCW_Json_Object* Create( const string& p_strPath );

	// ��ȡJson�����е�Ԫ�ظ���
	int		GetLength();
	// ��ȡָ����ŵ�Key
	const char*		KeyAt( int p_nIndex );
	// ���json����ȫ����ֵ��
	// ������p_pAOS �����
	void	Output( FKCW_IO_AssetOutputStream* p_pAOS, int p_nLevel = 1 );
	// ��Json���л���string
	string	ToString();

	// Ϊһ��key���һ����value
	void	AddNull( const char* p_szKey );
	// Ϊһ��key���һ��boolֵ
	void	AddBool( const char* p_szKey, bool p_bValue );
	// Ϊһ��key���һ��intֵ
	void	AddInt( const char* p_szKey, int p_nValue );
	// Ϊһ��key���һ��longֵ
	void	AddLong( const char* p_szKey, long p_lValue );
	// Ϊһ��key���һ��floatֵ
	void	AddFloat( const char* p_szKey, float p_fValue );
	// Ϊһ��key���һ��doubleֵ
	void	AddDouble( const char* p_szKey, double p_dValue );
	// Ϊһ��key���һ��stringֵ
	void	AddString( const char* p_szKey, const char* p_szValue );
	// Ϊһ��key���һ��objectֵ
	void	AddObject( const char* p_szKey, FKCW_Json_Object* p_pJO );
	// Ϊһ��key���һ��arrayֵ
	void	AddArray( const char* p_szKey, FKCW_Json_Array* p_pJA );
	
	// ��ȡһ��Key��Ӧ��boolֵ
	bool	GetBool( const char* p_szKey, bool p_bDefault = false );
	bool	GetBool( int p_nIndex, bool p_bDefault = false );
	// ��ȡһ��Key��Ӧ��intֵ
	int		GetInt( const char* p_szKey, int p_nDefault = 0 );
	int		GetInt( int p_nIndex, int p_nDefault = 0 );
	// ��ȡһ��Key��Ӧ��longֵ
	long	GetLong( const char* p_szKey, long p_lDefault = 0 );
	long	GetLong( int p_nIndex, long p_lDefault = 0 );
	// ��ȡһ��Key��Ӧ��floatֵ
	float	GetFloat( const char* p_szKey, float p_fDefault = 0.0f );
	float	GetFloat( int p_nIndex, float p_fDefault = 0.0f );
	// ��ȡһ��Key��Ӧ��doubleֵ
	double	GetDouble( const char* p_szKey, double p_dDefault = 0 );
	double	GetDouble( int p_nIndex, double p_dDefault = 0 );
	// ��ȡһ��Key��Ӧ��JsonObjectֵ
	FKCW_Json_Object*	GetObject( const char* p_szKey );
	FKCW_Json_Object*	GetObject( int p_nIndex );
	// ��ȡһ��Key��Ӧ��JsonArrayֵ
	FKCW_Json_Array*	GetArray( const char* p_szKey );
	FKCW_Json_Array*	GetArray( int p_nIndex );
	// ��ȡһ��Key��Ӧ��stringֵ
	string	GetString( const char* p_szKey, const char* p_szDefault = NULL );
	string	GetString( int p_nIndex, const char* p_szDefault = NULL );
};