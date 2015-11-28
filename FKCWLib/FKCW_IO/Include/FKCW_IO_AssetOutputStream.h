//*************************************************************************
//	��������:	2014-10-24
//	�ļ�����:	FKCW_IO_AssetOutputStream.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_IO_Macros.h"
//-------------------------------------------------------------------------
class FKCW_IO_AssetOutputStream : public CCObject
{
protected:
	FKCW_IO_AssetOutputStream();
	FKCW_IO_AssetOutputStream( const string& p_strPath, bool p_bIsAppend = false );
public:
	static FKCW_IO_AssetOutputStream* Create( const string& p_strPath, bool p_bIsAppend = false );
	virtual ~FKCW_IO_AssetOutputStream();
public:
	// ��һ����Դ
	virtual bool		Open();
	// �ر�һ����Դ
	virtual void		Close() = 0;
	// дһ������
	// ����ֵ��-1 ����������ʵ��д��Ĵ�С
	virtual ssize_t		Write( const char* p_pData, size_t p_nLen ) = 0;
	virtual ssize_t		Write( const int* p_pData, size_t p_nLen ) = 0;
	// ��ȡ��ǰ�����ļ�ͷ��ƫ����
	virtual size_t		GetPosition() = 0;
	// ���¶�ȡָ��λ��
	// ������p_nOffset ƫ����
	// ������p_nMode SEEK_CUR SEEK_END SEEK_SET ֮һ
	// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
	virtual size_t		Seek( int p_nOffset, int p_nMode ) = 0;
	// ��ȡ���·��
	const string&		GetPath(){ return m_strPath; }
protected:
	bool				m_bIsAppend;	// �Ƿ񸽼��ļ�
	string				m_strPath;		// �ļ�·��
};