/********************************************************************
	created:	2014/10/29
	file base:	FKCW_Database_ResultSet
	author:		FreeKnight
	
	purpose:	�����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Database_Macros.h"
//--------------------------------------------------------------------
class FKCW_Database_Statement;
class FKCW_Database_Database;
//--------------------------------------------------------------------
class FKCW_Database_ResultSet : public CCObject
{
	friend class FKCW_Database_Database;

private:
	typedef vector<string>		StringList;

	StringList		m_ColumnNames;		// �������������
	string			m_strSQL;			// ���ɸý������SQL���
	CC_SYNTHESIZE_READONLY(FKCW_Database_Database*, m_pDatabase, Database);
	CC_SYNTHESIZE_READONLY(FKCW_Database_Statement*, m_pStatement, Statement);

protected:
	FKCW_Database_ResultSet( FKCW_Database_Database* p_pDB, FKCW_Database_Statement* p_pSM );
	static FKCW_Database_ResultSet* Create( FKCW_Database_Database* p_pDB, FKCW_Database_Statement* p_pSM );
	// �ر�һ�������
	// ע���رպ󣬸ý����������ʹ�á�
	// ע��������������øú���
	void			Close();
public:
	virtual ~FKCW_Database_ResultSet();
	// �ƶ���ǰָ�뵽��һ��
	// ����ֵ����Ϊfalse���ʾ��û�����ݡ�true��ʾ�ɹ���
	bool			Next();
	// �Ƿ���һ������
	bool			IsHasAnotherRow();
	// ��ȡ�����������
	int				ColumnCount();
	// �ж�ָ�����Ƿ�Ϊ��
	bool			IsColumnIndexIsNull( int p_nColumnIndex );
	bool			IsColumnIsNull( string p_strColumnName );
	// ����������ȡָ���е�������
	int				ColumnIndexByName( string p_strColumnName );
	// ��ȡָ�������ŵ�����
	string			ColumnNameByIndex( int p_nColumnIndex );

	// ��ȡ��ǰָ�������� �� ָ������int����
	int				IntFromColumnName( string p_strColumnName );
	int				IntFromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������long����
	long			LongFromColumnName( string p_strColumnName );
	long			LongFromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������int64_t����
	int64_t			Int64FromColumnName( string p_strColumnName );
	int64_t			Int64FromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������bool����
	bool			BoolFromColumnName( string p_strColumnName );
	bool			BoolFromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������double����
	double			DoubleFromColumnName( string p_strColumnName );
	double			DoubleFromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������string����
	string			StringFromColumnName( string p_strColumnName );
	string			StringFromColumnIndex( int p_nColumnIndex );
	// ��ȡ��ǰָ�������� �� ָ������Blob����
	// ע: ����ֵ�Ǵ�Դ�����п����ģ����Ե�������Ҫ�ֶ�ɾ��
	const void*		DataFromColumnName( string p_strColumnName, size_t* p_pOutLen );
	const void*		DataFromColumnIndex( int p_nColumnIndex, size_t* p_pOutLen );
	// ��ȡ��ǰָ�������� �� ָ������Blob����
	// ע: ����ֵ�Ǿ���ԭ���ݣ����Ե����������ֶ�ɾ��
	const void*		DataNoCopyFromColumnName( string p_strColumnName, size_t* p_pOutLen );
	const void*		DataNoCopyFromColumnIndex( int p_nColumnIndex, size_t* p_pOutLen );
};