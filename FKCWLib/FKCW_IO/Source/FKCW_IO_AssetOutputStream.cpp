//-------------------------------------------------------------------------
#include "../Include/FKCW_IO_AssetOutputStream.h"
#include "../../FKCW_Base/Include/FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
FKCW_IO_AssetOutputStream::FKCW_IO_AssetOutputStream()
	: m_bIsAppend( false )
{
	m_strPath.clear();
}
//-------------------------------------------------------------------------
FKCW_IO_AssetOutputStream::FKCW_IO_AssetOutputStream( const string& p_strPath, bool p_bIsAppend )
	: m_bIsAppend( p_bIsAppend )
	, m_strPath( p_strPath )
{

}
//-------------------------------------------------------------------------
FKCW_IO_AssetOutputStream::~FKCW_IO_AssetOutputStream()
{

}
//-------------------------------------------------------------------------
// ��һ����Դ
bool FKCW_IO_AssetOutputStream::Open()
{
	return true;
}
//-------------------------------------------------------------------------