//--------------------------------------------------------------------
#include "../Include/FKCW_Database_ResultSet.h"
#include "../Include/FKCW_Database_Statement.h"
#include "../Include/FKCW_Database_Database.h"
#include "sqlite3/include/sqlite3.h"
//--------------------------------------------------------------------
FKCW_Database_ResultSet::FKCW_Database_ResultSet( FKCW_Database_Database* p_pDB, FKCW_Database_Statement* p_pSM )
	: m_pDatabase( p_pDB )
	, m_pStatement( p_pSM )
	, m_strSQL( p_pSM->getQuery() )
{
	// ��������
	int nColumnCount = sqlite3_column_count(p_pSM->getStatement());
	for(int i = 0; i < nColumnCount; i++) 
	{
		string szName = sqlite3_column_name(p_pSM->getStatement(), i);
		FKCW_Base_Utils::ToLowerCase( szName );
		m_ColumnNames.push_back( szName );
	}
}
//--------------------------------------------------------------------
FKCW_Database_ResultSet* FKCW_Database_ResultSet::Create( FKCW_Database_Database* p_pDB, FKCW_Database_Statement* p_pSM )
{
	FKCW_Database_ResultSet* rs = new FKCW_Database_ResultSet(p_pDB, p_pSM);
	return (FKCW_Database_ResultSet*)rs->autorelease();
}
//--------------------------------------------------------------------
// �ر�һ�������
// ע���رպ󣬸ý����������ʹ�á�
// ע��������������øú���
void FKCW_Database_ResultSet::Close()
{
	if( m_pStatement ) 
	{
		m_pStatement->Reset();
		m_pStatement = NULL;

		// ֪ͨ�ر�
		if( m_pDatabase )
			m_pDatabase->__PostResultSetClosed(this);
	}
}
//--------------------------------------------------------------------
FKCW_Database_ResultSet::~FKCW_Database_ResultSet()
{
	Close();
	m_pDatabase = NULL;
}
//--------------------------------------------------------------------
// �ƶ���ǰָ�뵽��һ��
// ����ֵ����Ϊfalse���ʾ��û�����ݡ�true��ʾ�ɹ���
bool FKCW_Database_ResultSet::Next()
{
	int rc = 0;
	if( m_pStatement ) 
	{
		bool retry;
		int numberOfRetries = 0;
		do 
		{
			retry = false;

			rc = sqlite3_step( m_pStatement->getStatement());

			if(SQLITE_BUSY == rc || SQLITE_LOCKED == rc) 
			{
				// ���DB��������ȴ�10����(��ֵ���޸�)���ң���������
				retry = true;
				if(SQLITE_LOCKED == rc) 
				{
					rc = sqlite3_reset( m_pStatement->getStatement());
					if(rc != SQLITE_LOCKED) 
					{
						CCLOGERROR("CCResultSet::next: Unexpected result from sqlite3_reset (%d) rs", rc);
					}
				}
				SLEEP(20);

				if( m_pDatabase->getBusyRetryTimeout() && (numberOfRetries++ > m_pDatabase->getBusyRetryTimeout())) 
				{
					CCLOGWARN("CCResultSet::next: Database busy");
					break;
				}
			} 
			else if(SQLITE_DONE == rc || SQLITE_ROW == rc) 
			{
				// һ������
			} 
			else if(SQLITE_ERROR == rc) 
			{
				CCLOGERROR("Error calling sqlite3_step (%d: %s) rs", rc, m_pDatabase->LastErrorMessage().c_str());
				break;
			} 
			else if(SQLITE_MISUSE == rc) 
			{
				CCLOGERROR("Error calling sqlite3_step (%d: %s) rs", rc, m_pDatabase->LastErrorMessage().c_str());
				break;
			} 
			else 
			{
				CCLOGERROR("Unknown error calling sqlite3_step (%d: %s) rs", rc, m_pDatabase->LastErrorMessage().c_str());
				break;
			}
		} while(retry);
	}

	return rc == SQLITE_ROW;
}
//--------------------------------------------------------------------
// �Ƿ���һ������
bool FKCW_Database_ResultSet::IsHasAnotherRow()
{
	return sqlite3_errcode(m_pDatabase->SqliteHandler()) == SQLITE_ROW;
}
//--------------------------------------------------------------------
// ��ȡ�����������
int FKCW_Database_ResultSet::ColumnCount()
{
	return sqlite3_column_count( m_pStatement->getStatement() );
}
//--------------------------------------------------------------------
// �ж�ָ�����Ƿ�Ϊ��
bool FKCW_Database_ResultSet::IsColumnIndexIsNull( int p_nColumnIndex )
{
	return sqlite3_column_type( m_pStatement->getStatement(), p_nColumnIndex ) == SQLITE_NULL;
}
//--------------------------------------------------------------------
bool FKCW_Database_ResultSet::IsColumnIsNull( string p_strColumnName )
{
	return IsColumnIndexIsNull( ColumnIndexByName(p_strColumnName) );
}
//--------------------------------------------------------------------
// ����������ȡָ���е�������
int FKCW_Database_ResultSet::ColumnIndexByName( string p_strColumnName )
{
	int index = 0;
	for(StringList::iterator iter = m_ColumnNames.begin(); iter != m_ColumnNames.end(); iter++, index++) 
	{
		string& name = *iter;
		if(name == p_strColumnName) 
		{
			return index;
		}
	}

	CCLOGWARN("Can't find column index for name: %s", p_strColumnName.c_str());
	return -1;
}
//--------------------------------------------------------------------
// ��ȡָ�������ŵ�����
string FKCW_Database_ResultSet::ColumnNameByIndex( int p_nColumnIndex )
{
	if( p_nColumnIndex < 0 || (size_t)p_nColumnIndex >= m_ColumnNames.size())
		return NULL;

	return m_ColumnNames.at(p_nColumnIndex);
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������int����
int FKCW_Database_ResultSet::IntFromColumnName( string p_strColumnName )
{
	return IntFromColumnIndex( ColumnIndexByName(p_strColumnName));
}
//--------------------------------------------------------------------
int FKCW_Database_ResultSet::IntFromColumnIndex( int p_nColumnIndex )
{
	return sqlite3_column_int( m_pStatement->getStatement(), p_nColumnIndex );
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������long����
long FKCW_Database_ResultSet::LongFromColumnName( string p_strColumnName )
{
	return LongFromColumnIndex( ColumnIndexByName(p_strColumnName));
}
//--------------------------------------------------------------------
long FKCW_Database_ResultSet::LongFromColumnIndex( int p_nColumnIndex )
{
	return (long)sqlite3_column_int64( m_pStatement->getStatement(), p_nColumnIndex );
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������int64_t����
int64_t FKCW_Database_ResultSet::Int64FromColumnName( string p_strColumnName )
{
	return Int64FromColumnIndex( ColumnIndexByName(p_strColumnName));
}
//--------------------------------------------------------------------
int64_t FKCW_Database_ResultSet::Int64FromColumnIndex( int p_nColumnIndex )
{
	return (int64_t)sqlite3_column_int64( m_pStatement->getStatement(), p_nColumnIndex );
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������bool����
bool FKCW_Database_ResultSet::BoolFromColumnName( string p_strColumnName )
{
	return BoolFromColumnIndex( ColumnIndexByName(p_strColumnName) );
}
//--------------------------------------------------------------------
bool FKCW_Database_ResultSet::BoolFromColumnIndex( int p_nColumnIndex )
{
	return IntFromColumnIndex( p_nColumnIndex ) != 0;
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������double����
double FKCW_Database_ResultSet::DoubleFromColumnName( string p_strColumnName )
{
	return DoubleFromColumnIndex( ColumnIndexByName(p_strColumnName) );
}
//--------------------------------------------------------------------
double FKCW_Database_ResultSet::DoubleFromColumnIndex( int p_nColumnIndex )
{
	return sqlite3_column_double( m_pStatement->getStatement(), p_nColumnIndex );
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������string����
string FKCW_Database_ResultSet::StringFromColumnName( string p_strColumnName )
{
	return StringFromColumnIndex( ColumnIndexByName(p_strColumnName) );
}
//--------------------------------------------------------------------
string FKCW_Database_ResultSet::StringFromColumnIndex( int p_nColumnIndex )
{
	if (sqlite3_column_type( m_pStatement->getStatement(), p_nColumnIndex) == SQLITE_NULL || 
		(p_nColumnIndex < 0)) 
	{
		return NULL;
	}

	return (const char*)sqlite3_column_text( m_pStatement->getStatement(), p_nColumnIndex);
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������Blob����
// ע: ����ֵ�Ǵ�Դ�����п����ģ����Ե�������Ҫ�ֶ�ɾ��
const void* FKCW_Database_ResultSet::DataFromColumnName( string p_strColumnName, size_t* p_pOutLen )
{
	return DataFromColumnIndex( ColumnIndexByName(p_strColumnName), p_pOutLen );
}
//--------------------------------------------------------------------
const void* FKCW_Database_ResultSet::DataFromColumnIndex( int p_nColumnIndex, size_t* p_pOutLen )
{
	// �������
	if (sqlite3_column_type(m_pStatement->getStatement(), p_nColumnIndex) == SQLITE_NULL || 
		(p_nColumnIndex < 0)) 
	{
		*p_pOutLen = 0;
		return NULL;
	}

	// ���ݿ���
	int dataSize = sqlite3_column_bytes(m_pStatement->getStatement(), p_nColumnIndex);
	char* buf = (char*)malloc(dataSize * sizeof(char));
	memcpy(buf, sqlite3_column_blob(m_pStatement->getStatement(), p_nColumnIndex), dataSize);

	// ���ػ�����
	*p_pOutLen = dataSize;
	return (const char*)buf;
}
//--------------------------------------------------------------------
// ��ȡ��ǰָ�������� �� ָ������Blob����
// ע: ����ֵ�Ǿ���ԭ���ݣ����Ե����������ֶ�ɾ��
const void* FKCW_Database_ResultSet::DataNoCopyFromColumnName( string p_strColumnName, size_t* p_pOutLen )
{
	return DataNoCopyFromColumnIndex( ColumnIndexByName(p_strColumnName), p_pOutLen );
}
//--------------------------------------------------------------------
const void* FKCW_Database_ResultSet::DataNoCopyFromColumnIndex( int p_nColumnIndex, size_t* p_pOutLen )
{
	if (sqlite3_column_type(m_pStatement->getStatement(), p_nColumnIndex) == SQLITE_NULL ||
		(p_nColumnIndex < 0)) 
	{
		*p_pOutLen = 0;
		return NULL;
	}

	*p_pOutLen = sqlite3_column_bytes(m_pStatement->getStatement(), p_nColumnIndex);
	return (const char*)sqlite3_column_blob(m_pStatement->getStatement(), p_nColumnIndex);
}
//--------------------------------------------------------------------