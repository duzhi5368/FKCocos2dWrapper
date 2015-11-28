//*************************************************************************
//	��������:	2014-10-24
//	�ļ�����:	FKCW_IO_MemoryInputStream.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_IO_AssetInputStream.h"
//-------------------------------------------------------------------------
class FKCW_IO_MemoryInputStream : public FKCW_IO_AssetInputStream
{
protected:
	char*			m_szBuffer;			// ������
	size_t			m_unLength;			// ����������
	size_t			m_unPosition;		// ��ǰ��ָ��λ��
	bool			m_bIsSelfRelease;	// �������Ƿ��Լ�����
protected:
	FKCW_IO_MemoryInputStream( char* p_szBuffer, size_t p_unLength, bool p_bIsSelfRelease );
public:
	static FKCW_IO_MemoryInputStream* Create( char* p_szBuffer, size_t p_unLength, bool p_bIsSelfRelease = false );
	virtual ~FKCW_IO_MemoryInputStream();
public:
	// ��ȡ���ݻ�����ָ��
	virtual char*		GetBuffer();
	// ��ȡ��ǰ�����ļ�ͷ��ƫ����
	virtual size_t		GetPosition();
	// ��ȡȫ���ݳ���
	virtual size_t		GetLength();
	// ��ȡ��Ч���ݳ���
	virtual size_t		GetAvailableLength();
	// �ر�һ����Դ
	virtual void		Close();
	// ��ȡһ�����ݵ�������
	// ����ֵ��-1 ����0 �����ݣ���ֵ ʵ�ʶ����������
	virtual ssize_t		Read( char* p_szBuffer, size_t p_unLength );
	// ���¶�ȡָ��λ��
	// ������p_nOffset ƫ����
	// ������p_nMode SEEK_CUR SEEK_END SEEK_SET ֮һ
	// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
	virtual size_t		Seek( int p_nOffset, int p_nMode );
};