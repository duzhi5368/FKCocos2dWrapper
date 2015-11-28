//--------------------------------------------------------------------
#include "../Include/FKCW_Database_Statement.h"
#include "sqlite3/include/sqlite3.h"
//--------------------------------------------------------------------
FKCW_Database_Statement::FKCW_Database_Statement()
	: m_nUseCount( 0 )
	, m_pStatement( NULL )
{

}
//--------------------------------------------------------------------
FKCW_Database_Statement::~FKCW_Database_Statement()
{
	Close();
}
//--------------------------------------------------------------------
// �ر�statement
void FKCW_Database_Statement::Close()
{
	SetStatement( NULL );
}
//--------------------------------------------------------------------
// ����statement
void FKCW_Database_Statement::Reset()
{
	if( m_pStatement )
	{
		sqlite3_reset( m_pStatement );
	}
}
//--------------------------------------------------------------------
// ����statement
void FKCW_Database_Statement::SetStatement( sqlite3_stmt* s )
{
	if( m_pStatement )
	{
		sqlite3_finalize( m_pStatement );
		m_pStatement = NULL;
	}
	m_pStatement = s;
}
//--------------------------------------------------------------------