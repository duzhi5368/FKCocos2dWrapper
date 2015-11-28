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
FKCW_Json_Array::FKCW_Json_Array()
{

}
//-------------------------------------------------------------------------
FKCW_Json_Array::~FKCW_Json_Array()
{
	for(vector<FKCW_Json_Object::SKeyValue>::iterator iter = m_ArrayKeyValue.begin(); 
		iter != m_ArrayKeyValue.end(); iter++) 
	{
		ReleaseKeyValue(*iter);
	}
}
//-------------------------------------------------------------------------
// ����һ���յ�json�������
FKCW_Json_Array* FKCW_Json_Array::Create()
{
	FKCW_Json_Array* a = new FKCW_Json_Array();
	return (FKCW_Json_Array*)a->autorelease();
}
//-------------------------------------------------------------------------
// ����һ��json��ʽ�ڴ�
// ע����CCObject��FKCW_Json_Object���ͣ����ֵ����Ϊ��������ĵ�һ��Ԫ�ء�
FKCW_Json_Array* FKCW_Json_Array::Create( const char* p_szJson, size_t p_unLength )
{
	CCObject* obj = FKCW_Json_Parser::Load(p_szJson, p_unLength);
	return SafeCast(obj);
}
//-------------------------------------------------------------------------
// ����һ��Json��ʽ�ļ�
FKCW_Json_Array* FKCW_Json_Array::Create( const string& p_strPath )
{
	CCObject* obj = FKCW_Json_Parser::Load(p_strPath);
	return SafeCast(obj);
}
//-------------------------------------------------------------------------
// ת��CCObjectΪFKCW_Json_Array��
// ע����CCObject��FKCW_Json_Object���ͣ����ֵ����Ϊ��������ĵ�һ��Ԫ�ء�
FKCW_Json_Array* FKCW_Json_Array::SafeCast( CCObject* p_pObj )
{
	FKCW_Json_Array* ja = dynamic_cast<FKCW_Json_Array*>(p_pObj);
	if(ja) 
	{
		return ja;
	} 
	else 
	{
		FKCW_Json_Object* jo = dynamic_cast<FKCW_Json_Object*>(p_pObj);
		if(jo) 
		{
			FKCW_Json_Array* ja = FKCW_Json_Array::Create();
			ja->AddObject(jo);
			return ja;
		} 
		else 
		{
			return NULL;
		}
	}
}
//-------------------------------------------------------------------------
//  �Ƴ�һ����ֵ
void FKCW_Json_Array::ReleaseKeyValue( FKCW_Json_Object::SKeyValue& p_KV )
{
	switch(p_KV.t) {
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
// ����json�����Ԫ�ظ���
int FKCW_Json_Array::GetLength()
{
	return m_ArrayKeyValue.size();
}
//-------------------------------------------------------------------------
// ���json����ȫ������ֵ
// ������p_pAOS �����
void FKCW_Json_Array::Output( FKCW_IO_AssetOutputStream* p_pAOS, int p_nLevel )
{
	// ����֧��
	s_szArrayBuf[0] = '[';
	s_szArrayBuf[1] = '\n';
	p_pAOS->Write(s_szArrayBuf, 2);

	for(vector<FKCW_Json_Object::SKeyValue>::iterator iter = m_ArrayKeyValue.begin();
		iter != m_ArrayKeyValue.end(); iter++) 
	{
		// ����հ׸�
		for(int i = 0; i < p_nLevel; i++) {
			s_szArrayBuf[i] = '\t';
		}
		p_pAOS->Write(s_szArrayBuf, p_nLevel);

		switch(iter->t) 
		{
		case FKCW_Json_Object::eJsonValueType_Object:
			iter->v.jo->Output(p_pAOS, p_nLevel + 1);

			// ����
			if(m_ArrayKeyValue.end() - iter != 1)
				p_pAOS->Write(",", 1);

			break;
		case FKCW_Json_Object::eJsonValueType_Array:
			iter->v.ja->Output(p_pAOS, p_nLevel + 1);

			// ����
			if(m_ArrayKeyValue.end() - iter != 1)
				p_pAOS->Write(",", 1);

			break;
		case FKCW_Json_Object::eJsonValueType_Boolean:
			if(m_ArrayKeyValue.end() - iter == 1)
				sprintf(s_szArrayBuf, "%s\n", iter->v.b ? "true" : "false");
			else
				sprintf(s_szArrayBuf, "%s,\n", iter->v.b ? "true" : "false");
			p_pAOS->Write(s_szArrayBuf, strlen(s_szArrayBuf));
			break;
		default:
			if(m_ArrayKeyValue.end() - iter == 1)
				sprintf(s_szArrayBuf, "\"%s\"\n", FKCW_Json_Value::CastToString(*iter));
			else
				sprintf(s_szArrayBuf, "\"%s\",\n", FKCW_Json_Value::CastToString(*iter));
			p_pAOS->Write(s_szArrayBuf, strlen(s_szArrayBuf));
			break;
		}
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
string FKCW_Json_Array::ToString()
{
	FKCW_IO_MemoryOutputStream mos;
	Output(&mos);
	return string(mos.GetBuffer(), mos.GetLength());
}
//-------------------------------------------------------------------------
// �����������һ����ֵ
void FKCW_Json_Array::AddNull()
{
	FKCW_Json_Object::Value v;
	memset(&v, 0, sizeof(FKCW_Json_Object::Value));
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_Nil,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��boolֵ
void FKCW_Json_Array::AddBool( bool p_bValue )
{
	FKCW_Json_Object::Value v;
	v.b = p_bValue;
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_Boolean,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��intֵ
void FKCW_Json_Array::AddInt( int p_nValue )
{
	char buf[32];
	sprintf(buf, "%d", p_nValue);
	FKCW_Json_Object::Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��longֵ
void FKCW_Json_Array::AddLong( long p_lValue )
{
	char buf[32];
	sprintf(buf, "%ld", p_lValue);
	FKCW_Json_Object::Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��floatֵ
void FKCW_Json_Array::AddFloat( float p_fValue )
{
	char buf[32];
	sprintf(buf, "%f", p_fValue);
	FKCW_Json_Object::Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��doubleֵ
void FKCW_Json_Array::AddDouble( double p_dValue )
{
	char buf[32];
	sprintf(buf, "%lf", p_dValue);
	FKCW_Json_Object::Value v;
	v.s = FKCW_Base_Utils::Copy(buf);
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��stringֵ
void FKCW_Json_Array::AddString( const char* p_szValue )
{
	FKCW_Json_Object::Value v;
	v.s = FKCW_Base_Utils::Copy(p_szValue);
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_String,
		v
	};
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��objectֵ
void FKCW_Json_Array::AddObject( FKCW_Json_Object* p_pJO )
{
	FKCW_Json_Object::Value v;
	v.jo = p_pJO;
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_Object,
		v
	};
	CC_SAFE_RETAIN(p_pJO);
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// �����������һ��arrayֵ
void FKCW_Json_Array::AddArray( FKCW_Json_Array* p_pJA )
{
	FKCW_Json_Object::Value v;
	v.ja = p_pJA;
	FKCW_Json_Object::SKeyValue kv = {
		NULL,
		FKCW_Json_Object::eJsonValueType_Array,
		v
	};
	CC_SAFE_RETAIN(p_pJA);
	m_ArrayKeyValue.push_back(kv);
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��boolֵ
bool FKCW_Json_Array::GetBool( int p_nIndex, bool p_bDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_bDefault;
	}

	return FKCW_Json_Value::CastToBool(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��intֵ
int FKCW_Json_Array::GetInt( int p_nIndex, int p_nDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_nDefault;
	}

	return FKCW_Json_Value::CastToInt(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��longֵ
long FKCW_Json_Array::GetLong( int p_nIndex, long p_lDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_lDefault;
	}

	return FKCW_Json_Value::CastToLong(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��floatֵ
float FKCW_Json_Array::GetFloat( int p_nIndex, bool p_fDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_fDefault;
	}

	return FKCW_Json_Value::CastToFloat(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��doubleֵ
double FKCW_Json_Array::GetDouble( int p_nIndex, bool p_dDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_dDefault;
	}

	return FKCW_Json_Value::CastToDouble(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��JsonObjectֵ
FKCW_Json_Object* FKCW_Json_Array::GetObject( int p_nIndex )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return NULL;
	}

	return FKCW_Json_Value::CastToObject(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��JsonArrayֵ
FKCW_Json_Array* FKCW_Json_Array::GetArray( int p_nIndex )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return NULL;
	}

	return FKCW_Json_Value::CastToArray(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------
// ��ȡָ����Ŷ�Ӧ��stringֵ
string FKCW_Json_Array::GetString( int p_nIndex, const char* p_szDefault )
{
	if( p_nIndex < 0 || p_nIndex >= m_ArrayKeyValue.size()) 
	{
		return p_szDefault;
	}

	return FKCW_Json_Value::CastToString(m_ArrayKeyValue.at(p_nIndex));
}
//-------------------------------------------------------------------------