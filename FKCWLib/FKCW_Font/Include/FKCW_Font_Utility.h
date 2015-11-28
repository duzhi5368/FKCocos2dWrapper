//*************************************************************************
//	��������:	2014-12-30
//	�ļ�����:	FKCW_Font_Utility.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Font_Config.h"
//-------------------------------------------------------------------------
// ��ȡϵͳ����Ŀ¼
extern const char* get_systemfont_path();
// ��ȡϵͳĬ��PPI
extern int get_system_default_ppi();
// ��ȡϵͳĬ�������С
extern int get_prefered_default_fontsize();
// ��ȡϵͳĬ������
extern const char* get_system_default_fontfile();
// ��ȡϵͳĬ����������
extern const char* get_system_default_hacklatin_fontfile();
// ��ʼ��
extern void FKCW_font_default_initialize();
// ��͡�ַ���
extern std::set<unsigned long>* latin_charset();

// dump��tga�ļ���
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

bool dump2tga(const std::string &filename, const unsigned int *pxl, uint16 width, uint16 height);