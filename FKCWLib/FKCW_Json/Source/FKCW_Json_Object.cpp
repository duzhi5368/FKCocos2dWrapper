//-------------------------------------------------------------------------
#include "../Include/FKCW_Json_Array.h"
#include "../Include/FKCW_Json_Value.h"
#include "../Include/FKCW_Json_Parser.h"
#include "../../FKCW_IO/Include/FKCW_IO_MemoryOutputStream.h"
#include "../../FKCW_Base/Include/FKCW_Base_Utils.h"
//-------------------------------------------------------------------------
#pragma warning( disable : 4018 )
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
// ��ʱ����
static char s_szArrayBuf[4096];
//-------------------------------------------------------------------------
FKCW_Json_Object::FKCW_Json_Object()
{

}
//-------------------------------------------------------------------------
// ת��һ��CCObjectΪFKCW_Json_Object����
// ������ת�������������ᱻ��䵽�����С���CCObject��һ�����飬�����Ϊһ����Ϊ��array����������䵽json��
FKCW_Json_Object* FKCW_Json_Object::SafeCast( CCObject* p_pObj )
{
	FKCW_Json_Object* jo = dynamic_cast<FKCW_Json_Object*>(p_pObj);
	if(jo) 
	{
		return jo;
	} 
	else 
	{
		FKCW_Json_Array* ja = dynamic_cast<FKCW_Json_Array*>(p_pObj);
		if(ja) 
		{
			FKCW_Json_Object* jo = FKCW_Json_Object::Create();
			jo->AddArray("array", ja);
			return jo;
		} 
		else 
		{
			return NULL;
		}
	}
}
//-------------------------------------------------------------------------
// �ͷ�ָ����ֵ
void FKCW_Json_Object::ReleaseKeyValue( const string& p_strKey, SKeyValue& p_KV )
{
	switch(p_KV.t) 
	{
	case FKCW_Json_Object::eJsonValueType_String:
		free((void*)p_KV.v.s);
		break;
	case FKCW_Json_Object::eJsonValueType_Object:
		CC_SAFE_RELEASE(p_KV.v.jo);
		break;
	case FKCW_Json_Object::eJsonValueType_Array:
		CC_SAFE_RELEASE(p_KV.v.ja);
		break;
	default:
		break;
	}
	if(p_KV.k)
		free((void*)p_KV.k);
}
//-------------------------------------------------------------------------
FKCW_Json_Object::~FKCW_Json_Object()
{
	for(PairMap::iterator iter = m_mapPairs.begin(); iter != m_mapPairs.end(); iter++) 
	{
		ReleaseKeyValue(iter->first, iter->second);
	}
}
//-------------------------------------------------------------------------
// ����һ����json����
FKCW_Json_Object* FKCW_Json_Object::Create()
{
	FKCW_Json_Object* jo = new FKCW_Json_Object();
	return ( FKCW_Json_Object* )jo->autorelease();
}
//-------------------------------------------------------------------------
// ����һ��json��ʽ���ڴ��ַ���
// �����json�ڴ���һ�����飬��������齫����Ϊһ����Ϊ"array"���������
FKCW_Json_Object* FKCW_Json_Object::Create( const char* p_szJson, size_t p_unLength )
{
	CCObject* obj = FKCW_Json_Parser::Load(p_szJson, p_unLength);
	return SafeCast(obj);
}
//-------------------------------------------------------------------------
// ����һ��json��ʽ���ļ�
FKCW_Json_Object* FKCW_Json_Object::Create( const string& p_strPath )
{
	CCObject* obj = FKCW_Json_Parser::Load(p_strPath);
	return SafeCast(obj);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ����value
void FKCW_Json_Object::AddNull( const char* p_szKey )
{
	if(!p_szKey)
		return;

	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		p_szKey,
		FKCW_Json_Object::eJsonValueType_Nil,
		{ false }
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��boolֵ
void FKCW_Json_Object::AddBool( const char* p_szKey, bool p_bValue )
{
	if(!p_szKey)
		return;

	Value v;
	v.b = p_bValue;
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_Boolean,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��intֵ
void FKCW_Json_Object::AddInt( const char* p_szKey, int p_nValue )
{
	if(!p_szKey)
		return;

	char buf[32];
	sprintf(buf, "%d", p_nValue);
	Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��longֵ
void FKCW_Json_Object::AddLong( const char* p_szKey, long p_lValue )
{
	if(!p_szKey)
		return;

	char buf[32];
	sprintf(buf, "%ld", p_lValue);
	Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��floatֵ
void FKCW_Json_Object::AddFloat( const char* p_szKey, float p_fValue )
{
	if(!p_szKey)
		return;

	char buf[32];
	sprintf(buf, "%f", p_fValue);
	Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��doubleֵ
void FKCW_Json_Object::AddDouble( const char* p_szKey, double p_dValue )
{
	if(!p_szKey)
		return;

	char buf[32];
	sprintf(buf, "%lf", p_dValue);
	Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��stringֵ
void FKCW_Json_Object::AddString( const char* p_szKey, const char* p_szValue )
{
	if(!p_szKey)
		return;

	Value v;
	v.s = FKCW_Base_Utils::Copy(p_szValue);
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��objectֵ
void FKCW_Json_Object::AddObject( const char* p_szKey, FKCW_Json_Object* p_pJO )
{
	if(!p_szKey)
		return;

	Value v;
	v.jo = p_pJO;
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_Object,
		v
	};
	CC_SAFE_RETAIN(p_pJO);
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// Ϊһ��key���һ��arrayֵ
void FKCW_Json_Object::AddArray( const char* p_szKey, FKCW_Json_Array* p_pJA )
{
	if(!p_szKey)
		return;

	Value v;
	v.ja = p_pJA;
	const char* k = FKCW_Base_Utils::Copy(p_szKey);
	SKeyValue kv = {
		k,
		FKCW_Json_Object::eJsonValueType_Array,
		v
	};
	CC_SAFE_RETAIN(p_pJA);
	m_mapPairs[k] = kv;
	m_vecKeyValues.push_back(kv);
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��boolֵ
bool FKCW_Json_Object::GetBool( const char* p_szKey, bool p_bDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToBool(iter->second);
	} else {
		return p_bDefault;
	}
}
//-------------------------------------------------------------------------
bool FKCW_Json_Object::GetBool( int p_nIndex, bool p_bDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_bDefault;
	}

	return FKCW_Json_Value::CastToBool(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��intֵ
int FKCW_Json_Object::GetInt( const char* p_szKey, int p_nDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToInt(iter->second);
	} else {
		return p_nDefault;
	}
}
//-------------------------------------------------------------------------
int FKCW_Json_Object::GetInt( int p_nIndex, int p_nDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_nDefault;
	}

	return FKCW_Json_Value::CastToInt(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��longֵ
long FKCW_Json_Object::GetLong( const char* p_szKey, long p_lDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToLong(iter->second);
	} else {
		return p_lDefault;
	}
}
//-------------------------------------------------------------------------
long FKCW_Json_Object::GetLong( int p_nIndex, long p_lDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_lDefault;
	}

	return FKCW_Json_Value::CastToLong(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��floatֵ
float FKCW_Json_Object::GetFloat( const char* p_szKey, float p_fDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToFloat(iter->second);
	} else {
		return p_fDefault;
	}
}
//-------------------------------------------------------------------------
float FKCW_Json_Object::GetFloat( int p_nIndex, float p_fDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_fDefault;
	}

	return FKCW_Json_Value::CastToFloat(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��doubleֵ
double	FKCW_Json_Object::GetDouble( const char* p_szKey, double p_dDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToDouble(iter->second);
	} else {
		return p_dDefault;
	}
}
//-------------------------------------------------------------------------
double FKCW_Json_Object::GetDouble( int p_nIndex, double p_dDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_dDefault;
	}

	return FKCW_Json_Value::CastToDouble(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��JsonObjectֵ
FKCW_Json_Object* FKCW_Json_Object::GetObject( const char* p_szKey )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToObject(iter->second);
	} else {
		return NULL;
	}
}
//-------------------------------------------------------------------------
FKCW_Json_Object* FKCW_Json_Object::GetObject( int p_nIndex )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return NULL;
	}

	return FKCW_Json_Value::CastToObject(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��JsonArrayֵ
FKCW_Json_Array* FKCW_Json_Object::GetArray( const char* p_szKey )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToArray(iter->second);
	} else {
		return NULL;
	}
}
//-------------------------------------------------------------------------
FKCW_Json_Array* FKCW_Json_Object::GetArray( int p_nIndex )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return NULL;
	}

	return FKCW_Json_Value::CastToArray(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡһ��Key��Ӧ��stringֵ
string  FKCW_Json_Object::GetString( const char* p_szKey, const char* p_szDefault )
{
	PairMap::iterator iter = m_mapPairs.find(p_szKey);
	if(iter != m_mapPairs.end()) {
		return FKCW_Json_Value::CastToString(iter->second);
	} else {
		return p_szDefault;
	}
}
//-------------------------------------------------------------------------
string FKCW_Json_Object::GetString( int p_nIndex, const char* p_szDefault )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return p_szDefault;
	}

	return FKCW_Json_Value::CastToString(m_vecKeyValues.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡJson�����е�Ԫ�ظ���
int FKCW_Json_Object::GetLength()
{
	return m_vecKeyValues.size();
}
//-------------------------------------------------------------------------
// ��ȡָ����ŵ�Key
const char* FKCW_Json_Object::KeyAt( int p_nIndex )
{
	if(p_nIndex < 0 || p_nIndex >= m_vecKeyValues.size()) {
		return NULL;
	}

	return m_vecKeyValues.at(p_nIndex).k;
}
//-------------------------------------------------------------------------
// ���json����ȫ����ֵ��
// ������p_pAOS �����
void FKCW_Json_Object::Output( FKCW_IO_AssetOutputStream* p_pAOS, int p_nLevel )
{
	// ����֧��
	s_szArrayBuf[0] = '[';
	s_szArrayBuf[1] = '\n';
	p_pAOS->Write(s_szArrayBuf, 2);

	int count = 0;
	for(PairMap::iterator iter = m_mapPairs.begin(); iter != m_mapPairs.end(); iter++)
	{
		// ����հ׸�
		for(int i = 0; i < p_nLevel; i++) {
			s_szArrayBuf[i] = '\t';
		}
		p_pAOS->Write(s_szArrayBuf, p_nLevel);

		// ���Key
		sprintf(s_szArrayBuf, "\"%s\" : ", iter->second.k);
		p_pAOS->Write(s_szArrayBuf, strlen(s_szArrayBuf));

		switch(iter->second.t) 
		{
		case FKCW_Json_Object::eJsonValueType_Object:
			iter->second.v.jo->Output(p_pAOS, p_nLevel + 1);

			// ����
			if(count != m_mapPairs.size() - 1)
				p_pAOS->Write(",", 1);

			break;
		case FKCW_Json_Object::eJsonValueType_Array:
			iter->second.v.ja->Output(p_pAOS, p_nLevel + 1);

			// ����
			if(count != m_mapPairs.size() - 1)
				p_pAOS->Write(",", 1);

			break;
		case FKCW_Json_Object::eJsonValueType_Boolean:
			if(count != m_mapPairs.size() - 1)
				sprintf(s_szArrayBuf, "%s\n", iter->second.v.b ? "true" : "false");
			else
				sprintf(s_szArrayBuf, "%s,\n", iter->second.v.b ? "true" : "false");
			p_pAOS->Write(s_szArrayBuf, strlen(s_szArrayBuf));
			break;
		default:
			if(count != m_mapPairs.size() - 1)
				sprintf(s_szArrayBuf, "\"%s\"\n", FKCW_Json_Value::CastToString(iter->second));
			else
				sprintf(s_szArrayBuf, "\"%s\",\n", FKCW_Json_Value::CastToString(iter->second));
			p_pAOS->Write(s_szArrayBuf, strlen(s_szArrayBuf));
			break;
		}

		count++;
	}

	// β���ո�
	for(int i = 0; i < p_nLevel - 1; i++) {
		s_szArrayBuf[i] = '\t';
	}
	p_pAOS->Write(s_szArrayBuf, p_nLevel - 1);

	// β��ʽ
	s_szArrayBuf[0] = ']';
	s_szArrayBuf[1] = '\n';
	p_pAOS->Write(s_szArrayBuf, 2);
}
//-------------------------------------------------------------------------
// ��Json���л���string
string FKCW_Json_Object::ToString()
{
	FKCW_IO_MemoryOutputStream mos;
	Output(&mos);
	return string(mos.GetBuffer(), mos.GetLength());
}
//-------------------------------------------------------------------------