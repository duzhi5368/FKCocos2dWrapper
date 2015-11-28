//*************************************************************************
//	��������:	2014-12-31
//	�ļ�����:	FKCW_Base_FileZip.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Base_Macro.h"
//-------------------------------------------------------------------------
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif
//-------------------------------------------------------------------------
namespace FKCW_Base_FileZip
{
	// ѹ��Դ�ļ���Ŀ���ļ�
	extern "C" int	Compress(FILE *source, FILE *dest, int level);
	// ��ѹ���ļ�
	extern "C" int	Decompress(FILE *source, FILE *dest, double* progress = NULL);
	// ��ѹ���ͽ�ѹ���Ľ������Ϊ����������Ϣ
	extern "C" void OutputError(int ret);
}