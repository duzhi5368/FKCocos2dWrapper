//*************************************************************************
//	��������:	2015-1-3
//	�ļ�����:	FKCW_RichHtml_HelpFunc.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RichHtml_Macros.h"
#include "FKCW_RichHtml_BaseStruct.h"
//-------------------------------------------------------------------------
extern "C"
{
	int		FKCW_RichHtml_TransferOCTValue(unsigned short c);
	int		FKCW_RichHtml_TransferHEXValue(unsigned short c);
	int		FKCW_RichHtml_TransferInteger(unsigned short* start, unsigned short* end, int& integer);
	int		FKCW_RichHtml_TransferAngleBrackets(unsigned short* start, unsigned short* end, std::string& content);
	bool	FKCW_RichHtml_TransferRect(std::string& str, FKCW_RichHtml_Rect& rect);
	bool	FKCW_RichHtml_TransferImage(const std::string& content, std::string& filename, FKCW_RichHtml_Rect& tex_rect, FKCW_RichHtml_Rect& composit_rect);
};
//-------------------------------------------------------------------------