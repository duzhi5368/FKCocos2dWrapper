/********************************************************************
	created:	2014/10/29
	file base:	FKCW_Database_Database
	author:		FreeKnight
	
	purpose:	Sqlite3��C++��װ
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_Database_Macros.h"
#include "FKCW_Database_ResultSet.h"
#include "FKCW_Database_Statement.h"
//--------------------------------------------------------------------
struct sqlite3;
//--------------------------------------------------------------------
class FKCW_Database_Database : public CCObject
{
	friend class FKCW_Database_ResultSet;
private:
	bool			m_bIsShouldCacheStatements;		// �Ƿ���Ҫ����statement

	typedef map<string, FKCW_Database_Statement*>	StatementMap;
	StatementMap	m_CachedStatements;				// ������ı������statement
public:
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, m_strDatabasePath, DatabasePath);		// ���ݿ�DB�ļ�·��
	CC_SYNTHESIZE_READONLY(sqlite3*, m_pDB, Sqlite3Handle);								// ���ݿ����
	CC_SYNTHESIZE(int, m_nBusyRetryTimeout, BusyRetryTimeout);							// ������ݿ���æ���ǽ����20�������һ�β������ԡ���ֵΪ����Դ���
	CC_SYNTHESIZE_READONLY_BOOL(m_bIsInTransaction, InTransaction);						// �Ƿ����ݿ����ڴ���������
	CC_SYNTHESIZE_BOOL(m_bIsInUse, InUse);												// �Ƿ����ݿ�����ִ��ĳ����
private:
	// ���һ�����棬��ǰDB���ڱ�ʹ����
	void						__WarnInUse();
	// ��ȡ�����statement
	FKCW_Database_Statement*	__GetCachedStatement( const char* p_szSql );
	// ����statement
	void						__SetCachedStatement( const char* p_szSql, FKCW_Database_Statement* p_pSM );
	// ִ��һ��sql��ѯ
	// ����ֵ�����Ϊ�գ����ѯʧ�ܡ�
	FKCW_Database_ResultSet*	__ExecuteQuery( const char* p_szSql );
	// ִ��һ���ǲ�ѯ��sql���
	bool						__ExecuteUpdate( const char* p_szSql );
	// ���������Ҫ�ر�ʱ����FKCW_Database_ResultSet����
	void						__PostResultSetClosed( FKCW_Database_ResultSet* p_RS );
protected:
	FKCW_Database_Database( string p_strPath );
public:
	virtual			~FKCW_Database_Database();
	// ����һ��DB����
	// ������p_strPath һ��ƽ̨�޹ص�database�ļ�·��
	static FKCW_Database_Database* Create( string p_strPath );
	// �Ƿ��̰߳�ȫ
	static bool		IsThreadSafe();
	// ��ȡsqlite�汾
	static string	SqliteLibVersion();

	// ��ȡsqlite handler
	sqlite3*		SqliteHandler();
	// ��DB
	bool			Open( int p_nFlags = 0 );
	// �ر�DB
	// ע���ú��������������б����ã��ʿ��������ֶ����á�����ر�һ��DB�󣬿��Ե���Open()ֱ���ٴδ�
	bool			Close();
	// ���DB�Ƿ��
	bool			IsDatabaseOpened();
	// ���DB�����Ƿ�����
	bool			IsGoodConnection();
	// ��������statements
	void			ClearCachedStatements();
	// ִ��һ����ѯSQL
	FKCW_Database_ResultSet*	ExecuteQuery( string p_strSql, ... );
	// ִ��һ�ηǲ�ѯSQL
	bool			ExecuteUpdate( string p_strSql, ... );
	// ��ȡ���һ������
	// ����ֵ����û�д�����᷵�ؿ��ַ���
	string			LastErrorMessage();
	// ��ȡ���һ������
	// ����ֵ����û�д�����᷵�� SQLITE_OK
	int				LastErrorCode();
	// �Ƿ���һ�������д���
	// ����ֵ��true���ʾ��һ�������д���
	bool			IsHadError();
	// ��ȡ�������������ID
	int64_t			LastInsertRowID();
	// �Ƿ񻺴���statements
	bool			IsCachedStatements();
	// �����Ƿ񻺴�statements
	void			SetCachedStatements( bool p_bValue );
	// ��ȡ��һ�β���Ӱ�����������
	int				Changes();
	// �ع���һ������
	bool			Rollback();
	// �ύһ������
	bool			Commit();
	// ��ʼһ����������
	// ע������������˼�������޸Ķ�������һ�������ڣ���ȫ���޸Ķ����֮����һ���Խ�����ͬ�������ݿ���
	bool			BeginDeferredTransaction();
	// ��ʼһ������
	bool			BeginTransaction();
	// ���һ�����Ƿ����
	bool			IsTableExists( string p_strTableName );

	// ͨ��һ����ѯ���õ�һ��intֵ
	int				IntFromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��longֵ
	long			LongFromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��int64_tֵ
	int64_t			Int64FromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��boolֵ
	bool			BoolFromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��doubleֵ
	double			DoubleFromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��stringֵ
	string			StringFromQuery( string p_strSql, ... );
	// ͨ��һ����ѯ���õ�һ��blobֵ
	// ע: ����ֵ�Ǵ�Դ�����п����ģ����Ե�������Ҫ�ֶ�ɾ��
	const void*		DataFromQuery( string p_strSql, size_t* p_pOutLen, ... );
	// ͨ��һ����ѯ���õ�һ��blobֵ
	// ע: ����ֵ�Ǿ���ԭ���ݣ����Ե����������ֶ�ɾ��
	const void*		DataNoCopyFromQuery( string p_strSql, size_t* p_pOutLen, ... );

	// ���һ��SQLStatement
	// ����ֵ�������Ч�򷵻ؿ��ַ���
	string			ValidateSQL( string p_strSql, ... );
	// ��ȡDB���
	FKCW_Database_ResultSet*	GetDBSchema();
	// ��ȡ����
	FKCW_Database_ResultSet*	GetTableSchema( string p_strTableName );
	// ���һ�����ֶ��Ƿ����
	bool			IsColumnExists( string p_strTableName, string p_strColumnName );
	// ��ȡ���ݿ�汾
	int				GetVersion();
	// �������ݿ�汾
	// ע��Ĭ�ϴ���ʱ�汾Ϊ1
	void			SetVersion( int p_nVersion );
	// ��������ִ��һ��sql�ļ�
	// ������p_strPath SQL�ļ� p_DeFunc ���ܺ���������sql�ļ�������
	bool			ExecuteSQL( string p_strPath, DECRYPT_FUNC p_DeFunc = NULL );
	// ��������ִ��һ��sql�ļ�
	bool			ExecuteSQL(const void* p_szData, size_t p_unLength );
};