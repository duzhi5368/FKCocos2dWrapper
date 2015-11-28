//*************************************************************************
//	��������:	2014-10-30
//	�ļ�����:	FKCW_Json_Array.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Json_Object.h"
#include "FKCW_Json_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Json_Array : public CCObject
{
private:
	typedef vector<FKCW_Json_Object::SKeyValue>		KeyValueList;
	KeyValueList			m_ArrayKeyValue;
protected:
	FKCW_Json_Array();
	// ת��CCObjectΪFKCW_Json_Array��
	// ע����CCObject��FKCW_Json_Object���ͣ����ֵ����Ϊ��������ĵ�һ��Ԫ�ء�
	static FKCW_Json_Array* SafeCast( CCObject* p_pObj );
	//  �Ƴ�һ����ֵ
	static void	ReleaseKeyValue( FKCW_Json_Object::SKeyValue& p_KV );
public:
	virtual ~FKCW_Json_Array();
	// ����һ���յ�json�������
	static FKCW_Json_Array* Create();
	// ����һ��json��ʽ�ڴ�
	// ע����CCObject��FKCW_Json_Object���ͣ����ֵ����Ϊ��������ĵ�һ��Ԫ�ء�
	static FKCW_Json_Array* Create( const char* p_szJson, size_t p_unLength );
	// ����һ��Json��ʽ�ļ�
	static FKCW_Json_Array*	Create( const string& p_strPath );

	// ����json�����Ԫ�ظ���
	int			GetLength();
	// ���json����ȫ������ֵ
	// ������p_pAOS �����
	void		Output( FKCW_IO_AssetOutputStream* p_pAOS, int p_nLevel = 1 );
	// ��Json���л���string
	string		ToString();

	// �����������һ����ֵ
	void		AddNull();
	// �����������һ��boolֵ
	void		AddBool( bool p_bValue );
	// �����������һ��intֵ
	void		AddInt( int p_nValue );
	// �����������һ��longֵ
	void		AddLong( long p_lValue );
	// �����������һ��floatֵ
	void		AddFloat( float p_fValue );
	// �����������һ��doubleֵ
	void		AddDouble( double p_dValue );
	// �����������һ��stringֵ
	void		AddString( const char* p_szValue );
	// �����������һ��objectֵ
	void		AddObject( FKCW_Json_Object* p_pJO );
	// �����������һ��arrayֵ
	void		AddArray( FKCW_Json_Array* p_pJA );

	// ��ȡָ����Ŷ�Ӧ��boolֵ
	bool	GetBool( int p_nIndex, bool p_bDefault = false );
	// ��ȡָ����Ŷ�Ӧ��intֵ
	int		GetInt( int p_nIndex, int p_nDefault = 0 );
	// ��ȡָ����Ŷ�Ӧ��longֵ
	long	GetLong( int p_nIndex, long p_lDefault = 0 );
	// ��ȡָ����Ŷ�Ӧ��floatֵ
	float	GetFloat( int p_nIndex, bool p_fDefault = 0.0f );
	// ��ȡָ����Ŷ�Ӧ��doubleֵ
	double	GetDouble( int p_nIndex, bool p_dDefault = 0 );
	// ��ȡָ����Ŷ�Ӧ��JsonObjectֵ
	FKCW_Json_Object*	GetObject( int p_nIndex );
	// ��ȡָ����Ŷ�Ӧ��JsonArrayֵ
	FKCW_Json_Array*	GetArray( int p_nIndex );
	// ��ȡָ����Ŷ�Ӧ��stringֵ
	string	GetString( int p_nIndex, const char* p_szDefault = NULL );
};