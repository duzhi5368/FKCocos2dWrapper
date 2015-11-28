//*************************************************************************
//	��������:	2014-10-24
//	�ļ�����:	FKCW_IO_AssetInputStream.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_IO_Macros.h"
//-------------------------------------------------------------------------
class FKCW_IO_AssetInputStream : public CCObject
{
protected:
	FKCW_IO_AssetInputStream();
	FKCW_IO_AssetInputStream( const string& p_strPath );
public:
	static FKCW_IO_AssetInputStream* Create( const string& p_strPath );
	virtual ~FKCW_IO_AssetInputStream();
public:
	// ��ȡ���ݻ�����ָ��
	virtual char*		GetBuffer() = 0;
	// ��ȡ��ǰ�����ļ�ͷ��ƫ����
	virtual size_t		GetPosition() = 0;
	// ��ȡȫ���ݳ���
	virtual size_t		GetLength() = 0;
	// ��ȡ��Ч���ݳ���
	virtual size_t		GetAvailableLength() = 0;
	// ����һ����Դ
	virtual bool		Open();
	// �ر�һ����Դ
	virtual void		Close() = 0;
	// ��ȡһ�����ݵ�������
	// ����ֵ��-1 ����0 �����ݣ���ֵ ʵ�ʶ����������
	virtual ssize_t		Read( char* p_szBuffer, size_t p_unLength ) = 0;
	// ��ȡһ���ֽ�
	virtual ssize_t		ReadByte( char* p_cRet );
	// ��ȡһ��������
	virtual ssize_t		ReadShort( short* p_pRet );
	// ��ȡһ������
	virtual ssize_t		ReadInt( int* p_pRet );
	// ��ȡһ��int64
	virtual ssize_t		ReadInt64( int64_t* p_pRet );
	// ���¶�ȡָ��λ��
	// ������p_nOffset ƫ����
	// ������p_nMode SEEK_CUR SEEK_END SEEK_SET ֮һ
	// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
	virtual size_t		Seek( int p_nOffset, int p_nMode ) = 0;
	// �����Ƿ�ʹ�ô�βģʽ��
	// ע��Ĭ��ΪСβģʽ
	virtual void		SetBigEndian( bool p_bIsUseBigEndian );
	// �ж��Ƿ��βģʽ
	virtual bool		IsBigEndian();
protected:
	int					m_nEndianState;		// ��β��Сβ
};
//-------------------------------------------------------------------------