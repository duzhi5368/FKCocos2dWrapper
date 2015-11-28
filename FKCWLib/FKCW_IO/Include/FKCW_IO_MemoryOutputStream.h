/********************************************************************
	created:	2014/10/28
	file base:	FKCW_IO_MemoryOutputStream
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_IO_AssetOutputStream.h"
//--------------------------------------------------------------------
class FKCW_IO_MemoryOutputStream : public FKCW_IO_AssetOutputStream
{
private:
	char*			m_szBuffer;			// ������
	size_t			m_unLength;			// ����������
	size_t			m_unPosition;		// ��ǰ��ָ��λ��
	size_t			m_unCapacity;		// ����������
	bool			m_bIsSelfRelease;	// �������Ƿ��Լ�����
protected:
	FKCW_IO_MemoryOutputStream( char* p_szBuffer, size_t p_unCapacity, bool p_bIsSelfRelease );
	// ȷ�������������㹻дlen���ֽ�
	void		_EnsureCapacity( size_t p_unLen );
public:
	FKCW_IO_MemoryOutputStream();
	virtual ~FKCW_IO_MemoryOutputStream();
	// ����һ��Ĭ���ڴ���������û��汻���ڴ����������
	static FKCW_IO_MemoryOutputStream* Create();
	// ����һ��ָ����С���ڴ������
	// ע�����ڴ汻���������������δ���ɱ������ɾ����ɾ�����μ����� p_bIsSelfRelease��
	static FKCW_IO_MemoryOutputStream* Create( size_t p_unCapacity, bool p_bIsSelfRelease = false );
public:
	// �رյ�ǰ�����
	virtual void		Close();
	// дһ������
	// ����ֵ��-1 ����������ʵ��д��Ĵ�С
	virtual ssize_t		Write( const char* p_pData, size_t p_nLen );
	virtual ssize_t		Write( const int* p_pData, size_t p_nLen );
	// ��ȡ��ǰ�����ļ�ͷ��ƫ����
	virtual size_t		GetPosition();
	// ���¶�ȡָ��λ��
	// ������p_nOffset ƫ����
	// ������p_nMode SEEK_CUR SEEK_END SEEK_SET ֮һ
	// ����ֵ��ƫ��֮�󣬺��ļ�ͷ�����ƫ����
	virtual size_t		Seek( int p_nOffset, int p_nMode );
	// ��ȡ��ǰ���������д����ڴ泤��
	size_t				GetLength();
	// ��ȡ��ǰ�����дָ��
	const char*			GetBuffer();
	// ���������ָ�룬׼����д������
	void				Reset();
};