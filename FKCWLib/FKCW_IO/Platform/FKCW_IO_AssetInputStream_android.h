//*************************************************************************
//	��������:	2015-4-1
//	�ļ�����:	FKCW_IO_AssetInputStream_android.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//-------------------------------------------------------------------------
#include "../Include/FKCW_IO_AssetInputStream.h"
//-------------------------------------------------------------------------
class FKCW_IO_AssetInputStream_android : public FKCW_IO_AssetInputStream {
	friend class FKCW_IO_AssetInputStream;

private:
    char*  m_buffer;
	size_t m_length;
    size_t m_position;

public:

	FKCW_IO_AssetInputStream_android(const string& path);

public:
	virtual ~FKCW_IO_AssetInputStream_android();

	virtual char*	GetBuffer();
	virtual size_t	GetPosition();
	virtual size_t	GetLength();
	virtual size_t	GetAvailableLength();
	virtual void	Close();
	virtual ssize_t Read(char* buffer, size_t length);
	virtual size_t	Seek(int offset, int mode);
};
//-------------------------------------------------------------------------
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//-------------------------------------------------------------------------