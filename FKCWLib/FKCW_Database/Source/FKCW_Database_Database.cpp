//--------------------------------------------------------------------
#include "../Include/FKCW_Database_Database.h"
#include "sqlite3/include/sqlite3.h"
//--------------------------------------------------------------------
#pragma warning( disable:4018 )
//--------------------------------------------------------------------
FKCW_Database_Database::FKCW_Database_Database( string p_strPath )
	: m_pDB( NULL )
	, m_strDatabasePath( p_strPath )
	, m_bIsInUse( false )
	, m_bIsInTransaction( false )
	, m_bIsShouldCacheStatements( false )
	, m_nBusyRetryTimeout( 0 )
{

}
//--------------------------------------------------------------------
FKCW_Database_Database::~FKCW_Database_Database()
{
	Close();

	// �ͷ�statements
	for(StatementMap::iterator iter = m_CachedStatements.begin(); iter != m_CachedStatements.end(); iter++) 
	{
		iter->second->release();
	}
}
//--------------------------------------------------------------------
// ����һ��DB����
// ������p_strPath һ��ƽ̨�޹ص�database�ļ�·��
FKCW_Database_Database* FKCW_Database_Database::Create( string p_strPath )
{
	FKCW_Database_Database* d = new FKCW_Database_Database(p_strPath);
	return (FKCW_Database_Database*)d->autorelease();
}
//--------------------------------------------------------------------
// �Ƿ��̰߳�ȫ
bool FKCW_Database_Database::IsThreadSafe()
{
	return sqlite3_threadsafe() != SQLITE_CONFIG_SINGLETHREAD;
}
//--------------------------------------------------------------------
// ��ȡsqlite�汾
string FKCW_Database_Database::SqliteLibVersion()
{
	return sqlite3_libversion();
}
//--------------------------------------------------------------------
// ��ȡsqlite handler
sqlite3* FKCW_Database_Database::SqliteHandler()
{
	return m_pDB;
}
//--------------------------------------------------------------------
// ��DB
bool FKCW_Database_Database::Open( int p_nFlags )
{
	if( m_pDB ) 
	{
		return true;
	}

	string path = m_strDatabasePath;

	// ���·�������ڣ��򴴽����ڴ��У�������ָ��·��
	if(path.empty())
	{
		path = ":memory:";
	}
	else 
	{
		// �����ļ���·��
		//if(!CCUtils::CreateIntermediateFolders(path)) {
		//	CCLOGERROR("failed to create containing directory for database");
		//	return false;
		//}
	}

	// ����DB��
	int err = SQLITE_OK;
#if SQLITE_VERSION_NUMBER >= 3005000
	if(p_nFlags != 0)
		err = sqlite3_open_v2(path.c_str(), &m_pDB, p_nFlags, NULL);
	else
#endif
		err = sqlite3_open(path.c_str(), &m_pDB);

	// ������
	if(err != SQLITE_OK) 
	{
		CCLOGERROR("CCDatabase:open: error opening: %d", err);
		m_pDB = NULL;
		return false;
	}

	return true;
}
//--------------------------------------------------------------------
// �ر�DB
// ע���ú��������������б����ã��ʿ��������ֶ����á�����ر�һ��DB�󣬿��Ե���Open()ֱ���ٴδ�
bool FKCW_Database_Database::Close()
{
	ClearCachedStatements();

	// ���DB
	if( !m_pDB ) 
	{
		return true;
	}

	int rc;
	bool retry;
	int numberOfRetries = 0;

	// ����ȥ�ر�DB
	// ���DB������æ������������һ��ʱ���������ԣ����д������ƣ�������ѭ����
	do 
	{
		retry = false;
		rc = sqlite3_close( m_pDB );
		if(SQLITE_BUSY == rc || SQLITE_LOCKED == rc) 
		{
			retry = true;
			SLEEP(20);
			if( m_nBusyRetryTimeout && (numberOfRetries++ > m_nBusyRetryTimeout)) 
			{
				CCLOGWARN("CCDatabase:close: Database busy, unable to close");
				return false;
			}
		} 
		else if(SQLITE_OK != rc) 
		{
			CCLOGWARN("CCDatabase:close: error closing!: %d", rc);
		}
	} while(retry);

	m_pDB = NULL;

	return true;
}
//--------------------------------------------------------------------
// ���DB�Ƿ��
bool FKCW_Database_Database::IsDatabaseOpened()
{
	if (!m_pDB) 
	{
		CCLOGWARN("The CCDatabase %p is not open.", this);
		return false;
	}

	return true;
}
//--------------------------------------------------------------------
// ���DB�����Ƿ�����
bool FKCW_Database_Database::IsGoodConnection()
{
	if(!m_pDB) 
	{
		return false;
	}

	// �����򵥵Ĳ�ѯ���ж�����״��
	FKCW_Database_ResultSet* rs = ExecuteQuery("select name from sqlite_master where type='table'");

	// ����õ�����������Ϊ��������
	if(rs) 
	{
		rs->release();
		return true;
	}

	return false;
}
//--------------------------------------------------------------------
// ��������statements
void FKCW_Database_Database::ClearCachedStatements()
{
	for(StatementMap::iterator iter = m_CachedStatements.begin(); iter != m_CachedStatements.end(); iter++) 
	{
		iter->second->release();
	}
	m_CachedStatements.clear();
}
//--------------------------------------------------------------------
// ִ��һ�ηǲ�ѯSQL
bool FKCW_Database_Database::ExecuteUpdate( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	// ִ������sql���
	return __ExecuteUpdate(buf);
}
//--------------------------------------------------------------------
// ִ��һ���ǲ�ѯ��sql���
bool FKCW_Database_Database::__ExecuteUpdate( const char* p_szSql )
{
	// ���ȼ�����ݿ�
	if ( !IsDatabaseOpened() ) 
	{
        return false;
    }

    // �Ƿ�����ʹ����
    if ( m_bIsInUse ) 
	{
        __WarnInUse();
        return false;
    }

    // ����������ʹ��״̬
    setInUse(true);

    int rc = 0;
	sqlite3_stmt* pStmt = NULL;
	FKCW_Database_Statement* cachedStmt = NULL;

	// ��ȡ�������sqlStatement
	cachedStmt = __GetCachedStatement(p_szSql);
	pStmt = cachedStmt ? cachedStmt->getStatement() : NULL;

	// �����sqlStatementȷʵ��������
	if(cachedStmt)
		cachedStmt->Reset();
	
    int numberOfRetries = 0;
	bool retry = false;

	// ����statement
    if(!pStmt) 
	{
		do 
		{
			// ׼��statement
			retry = false;
			rc = sqlite3_prepare_v2( m_pDB, p_szSql, -1, &pStmt, 0);

			// �����æµ״̬��������ȴ�
			if(SQLITE_BUSY == rc || SQLITE_LOCKED == rc) 
			{
				retry = true;
				SLEEP(20);

				if(m_nBusyRetryTimeout && (numberOfRetries++ > m_nBusyRetryTimeout)) 
				{
					CCLOGWARN("CCDatabase:_executeUpdate: Database busy");
					sqlite3_finalize(pStmt);
					setInUse(false);
					return false;
				}
			} 
			else if(SQLITE_OK != rc) 
			{
				CCLOGERROR("CCDatabase:_executeUpdate: DB Error: %d \"%s\"", LastErrorCode(), LastErrorMessage().c_str());

				sqlite3_finalize(pStmt);

				// �޸�ʹ��״̬
				setInUse(false);
				return false;
			}
		} while(retry);
	}

	// ���� sqlite3_step() ִ���������
	// ��Ϊ���õ�sqlδ����select�����ǲ���֤һ�������ݷ��ء�
    numberOfRetries = 0;
	do 
	{
		rc = sqlite3_step(pStmt);
		retry = false;

		if(SQLITE_BUSY == rc || SQLITE_LOCKED == rc) 
		{
			// ���DB��������ôÿ20�������ٳ���һ��
			retry = true;
			if(SQLITE_LOCKED == rc) 
			{
				rc = sqlite3_reset(pStmt);
				if(rc != SQLITE_LOCKED) 
				{
					CCLOGERROR("CCDatabase:_executeUpdate: Unexpected result from sqlite3_reset (%d) eu", rc);
				}
			}
			SLEEP(20);

			if(m_nBusyRetryTimeout && (numberOfRetries++ > m_nBusyRetryTimeout)) 
			{
				CCLOGWARN("CCDatabase:_executeUpdate: Database busy 2");
				retry = false;
			}
		} 
		else if(SQLITE_DONE == rc || SQLITE_ROW == rc) 
		{
			// һ������������
		} 
		else if(SQLITE_ERROR == rc) 
		{
			CCLOGERROR("Error calling sqlite3_step (%d: %s) SQLITE_ERROR", rc, LastErrorMessage().c_str());
		} 
		else if(SQLITE_MISUSE == rc) 
		{
			CCLOGERROR("Error calling sqlite3_step (%d: %s) SQLITE_MISUSE", rc, LastErrorMessage().c_str());
		} 
		else {
			CCLOGERROR("Unknown error calling sqlite3_step (%d: %s) eu", rc, LastErrorMessage().c_str());
		}
	} while(retry);

	// ����statement
    if(m_bIsShouldCacheStatements && !cachedStmt) 
	{
		cachedStmt = new FKCW_Database_Statement();
		cachedStmt->SetStatement(pStmt);
		cachedStmt->setQuery(p_szSql);
		cachedStmt->m_nUseCount = 1;
		__SetCachedStatement(p_szSql, cachedStmt);
	}

    // ���statement�Ѿ������棬ע�ⲻҪ�ͷ���
    if(cachedStmt) 
	{
		rc = sqlite3_reset(pStmt);
	} 
	else 
	{
		// �ͷ�������������ͷ�ȫ���ڴ��Լ�sqlite3_prepare()���õ���Դ
		rc = sqlite3_finalize(pStmt);
	}

    // �޸�ռ��״̬
    setInUse(false);

    return rc == SQLITE_OK;
}
//--------------------------------------------------------------------
// ִ��һ��sql��ѯ
// ����ֵ�����Ϊ�գ����ѯʧ�ܡ�
FKCW_Database_ResultSet* FKCW_Database_Database::__ExecuteQuery( const char* p_szSql )
{
	// ���ȼ�����ݿ�
	if ( !IsDatabaseOpened() ) 
	{
		return NULL;
	}

	// �Ƿ�����ʹ����
	if ( m_bIsInUse ) 
	{
		__WarnInUse();
		return NULL;
	}

	// ����������ʹ��״̬
	setInUse(true);

	FKCW_Database_ResultSet* rs = NULL;
	int rc = 0;
	sqlite3_stmt* pStmt = NULL;
	FKCW_Database_Statement* cachedStmt = NULL;

	// ��ȡ�������sqlStatement
	cachedStmt = __GetCachedStatement(p_szSql);
	pStmt = cachedStmt ? cachedStmt->getStatement() : NULL;

	// �����sqlStatementȷʵ��������
	if(cachedStmt)
		cachedStmt->Reset();

	int numberOfRetries = 0;
	bool retry = false;

	// ����statement
	if(!pStmt) 
	{
		do 
		{
			// Ԥ׼��statement
			retry = false;
			rc = sqlite3_prepare_v2( m_pDB, p_szSql, -1, &pStmt, 0);

			// ���DB��æ����ȴ�
			if(SQLITE_BUSY == rc || SQLITE_LOCKED == rc) 
			{
				retry = true;
				SLEEP(20);

				if(m_nBusyRetryTimeout && (numberOfRetries++ > m_nBusyRetryTimeout)) 
				{
					CCLOGWARN("CCDatabase:_executeQuery: Database busy");
					sqlite3_finalize(pStmt);
					setInUse(false);
					return NULL;
				}
			} 
			else if(SQLITE_OK != rc) 
			{
				CCLOGERROR("CCDatabase:_executeQuery: DB Error: %d \"%s\"", LastErrorCode(), LastErrorMessage().c_str());

				// �ͷ�statement
				sqlite3_finalize(pStmt);

				// �޸�use״̬
				setInUse(false);
				return NULL;
			}
		} while(retry);
	}

	// ���� Statement
	if (!cachedStmt) {
		cachedStmt = new FKCW_Database_Statement();
		cachedStmt->SetStatement(pStmt);
		cachedStmt->setQuery(p_szSql);
		cachedStmt->m_nUseCount = 1;
		__SetCachedStatement(p_szSql, cachedStmt);
	} else {
		cachedStmt->m_nUseCount++;
	}

	rs = FKCW_Database_ResultSet::Create(this, cachedStmt);

	// �޸�ʹ��״̬
	setInUse(false);

	return rs;
}
//--------------------------------------------------------------------
// ִ��һ����ѯSQL
FKCW_Database_ResultSet* FKCW_Database_Database::ExecuteQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	// ʵ��ִ�����sql��ѯ
	return __ExecuteQuery(buf);
}
//--------------------------------------------------------------------
// ���������Ҫ�ر�ʱ����FKCW_Database_ResultSet����
void FKCW_Database_Database::__PostResultSetClosed( FKCW_Database_ResultSet* p_RS )
{
	StatementMap::iterator iter = m_CachedStatements.find(p_RS->m_strSQL);
	if(iter != m_CachedStatements.end()) 
	{
		// ɾ�����ü�����������ü���Ϊ0����ӻ���statement����ɾ��
		iter->second->m_nUseCount--;
		if(iter->second->m_nUseCount <= 0 && !m_bIsShouldCacheStatements) 
		{
			iter->second->release();
			m_CachedStatements.erase(iter);
		}
	}
}
//--------------------------------------------------------------------
// ���һ�����棬��ǰDB���ڱ�ʹ����
void FKCW_Database_Database::__WarnInUse()
{
	CCLOGWARN("The CCDatabase %p is currently in use.", this);
}
//--------------------------------------------------------------------
// ��ȡ���һ������
// ����ֵ����û�д�����᷵�ؿ��ַ���
string FKCW_Database_Database::LastErrorMessage()
{
	if(m_pDB)
		return sqlite3_errmsg(m_pDB);
	else
		return "";
}
//--------------------------------------------------------------------
// ��ȡ���һ������
// ����ֵ����û�д�����᷵�� SQLITE_OK
int FKCW_Database_Database::LastErrorCode()
{
	if(m_pDB)
		return sqlite3_errcode(m_pDB);
	else
		return SQLITE_OK;
}
//--------------------------------------------------------------------
// �Ƿ���һ�������д���
// ����ֵ��true���ʾ��һ�������д���
bool FKCW_Database_Database::IsHadError()
{
	int lastErrCode = LastErrorCode();
	return (lastErrCode > SQLITE_OK && lastErrCode < SQLITE_ROW);
}
//--------------------------------------------------------------------
// ��ȡ�������������ID
int64_t FKCW_Database_Database::LastInsertRowID()
{
	if(m_bIsInUse) 
	{
		__WarnInUse();
		return false;
	}

	setInUse(true);
	sqlite_int64 ret = sqlite3_last_insert_rowid( m_pDB );
	setInUse(false);

	return (int64_t)ret;
}
//--------------------------------------------------------------------
// ��ȡ�����statement
FKCW_Database_Statement* FKCW_Database_Database::__GetCachedStatement( const char* p_szSql )
{
	StatementMap::iterator iter = m_CachedStatements.find(p_szSql);
	if(iter != m_CachedStatements.end()) 
	{
		return iter->second;
	} 
	else 
	{
		return NULL;
	}
}
//--------------------------------------------------------------------
// ����statement
void FKCW_Database_Database::__SetCachedStatement( const char* p_szSql, FKCW_Database_Statement* p_pSM )
{
	// ������ϵģ����ͷ�
	StatementMap::iterator iter = m_CachedStatements.find(p_szSql);
	if(iter != m_CachedStatements.end()) 
	{
		iter->second->release();
		m_CachedStatements.erase(iter);
	}

	m_CachedStatements[p_szSql] = p_pSM;
}
//--------------------------------------------------------------------
// �Ƿ񻺴���statements
bool FKCW_Database_Database::IsCachedStatements()
{
	return m_bIsShouldCacheStatements;
}
//--------------------------------------------------------------------
// �����Ƿ񻺴�statements
void FKCW_Database_Database::SetCachedStatements( bool p_bValue )
{
	m_bIsShouldCacheStatements = p_bValue;

	if(!m_bIsShouldCacheStatements) 
	{
		ClearCachedStatements();
	}
}
//--------------------------------------------------------------------
// ��ȡ��һ�β���Ӱ�����������
int FKCW_Database_Database::Changes()
{
	if (m_bIsInUse) 
	{
		__WarnInUse();
		return 0;
	}

	setInUse(true);
	int ret = sqlite3_changes( m_pDB );
	setInUse(false);

	return ret;
}
//--------------------------------------------------------------------
// �ع���һ������
bool FKCW_Database_Database::Rollback()
{
	bool b = ExecuteUpdate("ROLLBACK TRANSACTION;");
	if (b) 
	{
		m_bIsInTransaction = false;
	}
	return b;
}
//--------------------------------------------------------------------
// �ύһ������
bool FKCW_Database_Database::Commit()
{
	bool b = ExecuteUpdate("COMMIT TRANSACTION;");
	if (b) 
	{
		m_bIsInTransaction = false;
	}
	return b;
}
//--------------------------------------------------------------------
// ��ʼһ����������
// ע������������˼�������޸Ķ�������һ�������ڣ���ȫ���޸Ķ����֮����һ���Խ�����ͬ�������ݿ���
bool FKCW_Database_Database::BeginDeferredTransaction()
{
	bool b = ExecuteUpdate("BEGIN DEFERRED TRANSACTION;");
	if (b) 
	{
		m_bIsInTransaction = true;
	}
	return b;
}
//--------------------------------------------------------------------
// ��ʼһ������
bool FKCW_Database_Database::BeginTransaction()
{
	bool b = ExecuteUpdate("BEGIN EXCLUSIVE TRANSACTION;");
	if (b) 
	{
		m_bIsInTransaction = true;
	}
	return b;
}
//--------------------------------------------------------------------
// ���һ�����Ƿ����
bool FKCW_Database_Database::IsTableExists( string p_strTableName )
{
	bool returnBool;

	// ��sqlite_master����ȥ��ñ��Ƿ����
	FKCW_Base_Utils::ToLowerCase(p_strTableName);
	FKCW_Database_ResultSet* rs = ExecuteQuery("select [sql] from sqlite_master where [type] = 'table' and lower(name) = '%s'", p_strTableName.c_str());

	// ����Ƿ�������
	returnBool = rs->Next();

	rs->Close();

	return returnBool;
}
//--------------------------------------------------------------------
// ���һ��SQLStatement
// ����ֵ�������Ч�򷵻ؿ��ַ���
string FKCW_Database_Database::ValidateSQL( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	sqlite3_stmt* pStmt = NULL;
	bool keepTrying = true;
	int numberOfRetries = 0;
	string ret;

	// ����ʹ�ñ�ʾ
	setInUse(true);

	// ��������
	while(keepTrying) 
	{
		keepTrying = false;
		int rc = sqlite3_prepare_v2( m_pDB, buf, -1, &pStmt, 0);
		if(rc == SQLITE_BUSY || rc == SQLITE_LOCKED) 
		{
			keepTrying = true;
			SLEEP(20);

			if(m_nBusyRetryTimeout && (numberOfRetries++ > m_nBusyRetryTimeout)) 
			{
				CCLOGWARN("CCDatabase::validateSQL: Database busy");
			}
		} 
		else if(rc != SQLITE_OK) 
		{
			ret = LastErrorMessage();
		}
	}

	// �޸�ʹ�ñ�ʾ
	setInUse(false);

	// �ͷ�statement
	sqlite3_finalize(pStmt);

	return ret;
}
//--------------------------------------------------------------------
// ��ȡDB���
FKCW_Database_ResultSet* FKCW_Database_Database::GetDBSchema()
{
	FKCW_Database_ResultSet* rs = ExecuteQuery("SELECT type, name, tbl_name, rootpage, sql FROM (SELECT * FROM sqlite_master UNION ALL SELECT * FROM sqlite_temp_master) WHERE type != 'meta' AND name NOT LIKE 'sqlite_%' ORDER BY tbl_name, type DESC, name");
	return rs;
}
//--------------------------------------------------------------------
// ��ȡ����
FKCW_Database_ResultSet* FKCW_Database_Database::GetTableSchema( string p_strTableName )
{
	FKCW_Database_ResultSet* rs = ExecuteQuery("PRAGMA table_info(%s)", p_strTableName.c_str());
	return rs;
}
//--------------------------------------------------------------------
// ���һ�����ֶ��Ƿ����
bool FKCW_Database_Database::IsColumnExists( string p_strTableName, string p_strColumnName )
{
	bool existent = false;

	// תСд
	FKCW_Base_Utils::ToLowerCase(p_strTableName);
	FKCW_Base_Utils::ToLowerCase(p_strColumnName);

	// ��ȡ����
	FKCW_Database_ResultSet* rs = GetTableSchema( p_strTableName );

	// ���м���Ƿ��ڱ�����
	while(rs->Next()) 
	{
		string column = rs->StringFromColumnName("name");
		FKCW_Base_Utils::ToLowerCase(column);
		if(column == p_strColumnName) 
		{
			existent = true;
			break;
		}
	}

	return existent;
}
//--------------------------------------------------------------------
// ��ȡ���ݿ�汾
int FKCW_Database_Database::GetVersion()
{
	return IntFromQuery("PRAGMA user_version;");
}
//--------------------------------------------------------------------
// �������ݿ�汾
// ע��Ĭ�ϴ���ʱ�汾Ϊ1
void FKCW_Database_Database::SetVersion( int p_nVersion )
{
	ExecuteUpdate("PRAGMA user_version = %d;", p_nVersion);
}
//--------------------------------------------------------------------
// ��������ִ��һ��sql�ļ�
// ������p_strPath SQL�ļ� p_DeFunc ���ܺ���������sql�ļ�������
bool FKCW_Database_Database::ExecuteSQL( string p_strPath, DECRYPT_FUNC p_DeFunc )
{
	unsigned long len;
	unsigned char* raw = FKCW_Base_ResourceLoader::LoadRow(p_strPath, &len, p_DeFunc);
	bool ret = ExecuteSQL(raw, len);
	free(raw);
	return ret;
}
//--------------------------------------------------------------------
// ��������ִ��һ��sql�ļ�
bool FKCW_Database_Database::ExecuteSQL(const void* p_szData, size_t p_unLength )
{
	// ��ʼ����
	if(!BeginTransaction()) 
	{
		CCLOGERROR("CCDatabase::executeSQL: failed to start transaction");
		return false;
	}

	// ����ִ��
	char* tmp = (char*)p_szData;
	int start = 0;
	for(int i = 0; i < p_unLength; i++) 
	{
		if(isspace(tmp[i]) && i == start) 
		{
			start++;
		} 
		else if(tmp[i] == ';') 
		{
			tmp[i] = 0;
			// ִ��
			bool success = ExecuteUpdate(tmp + start);
			tmp[i] = ';';

			// ���ִ�гɹ�����ִ����һ������ʧ�ܣ����˳�
			if(success) 
			{
				start = i + 1;
			} else 
			{
				// ʧ�ܣ���ع�
				if(!Rollback()) 
				{
					CCLOGERROR("CCDatabase::executeSQL: failed to rollback transaction");
				}

				return false;
			}
		}
	}

	// �ύ����
	if(!Commit()) {
		CCLOGERROR("CCDatabase::executeSQL: failed to commit transaction");
		return false;
	}

	return true;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��intֵ
int FKCW_Database_Database::IntFromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->IntFromColumnIndex(0);
	else
		return 0;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��longֵ
long FKCW_Database_Database::LongFromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->LongFromColumnIndex(0);
	else
		return 0;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��int64_tֵ
int64_t FKCW_Database_Database::Int64FromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->Int64FromColumnIndex(0);
	else
		return 0;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��boolֵ
bool FKCW_Database_Database::BoolFromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->BoolFromColumnIndex(0);
	else
		return false;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��doubleֵ
double FKCW_Database_Database::DoubleFromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->DoubleFromColumnIndex(0);
	else
		return 0;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��stringֵ
string FKCW_Database_Database::StringFromQuery( string p_strSql, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->StringFromColumnIndex(0);
	else
		return "";
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��blobֵ
// ע: ����ֵ�Ǵ�Դ�����п����ģ����Ե�������Ҫ�ֶ�ɾ��
const void* FKCW_Database_Database::DataFromQuery( string p_strSql, size_t* p_pOutLen, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->DataFromColumnIndex(0, p_pOutLen);
	else
		return NULL;
}
//--------------------------------------------------------------------
// ͨ��һ����ѯ���õ�һ��blobֵ
// ע: ����ֵ�Ǿ���ԭ���ݣ����Ե����������ֶ�ɾ��
const void* FKCW_Database_Database::DataNoCopyFromQuery( string p_strSql, size_t* p_pOutLen, ... )
{
	va_list args;
	va_start(args, p_strSql);
	char buf[512];
	vsprintf(buf, p_strSql.c_str(), args);
	va_end(args);

	FKCW_Database_ResultSet* rs = __ExecuteQuery(buf);
	if(rs->Next())
		return rs->DataNoCopyFromColumnIndex(0, p_pOutLen);
	else
		return NULL;
}
//--------------------------------------------------------------------