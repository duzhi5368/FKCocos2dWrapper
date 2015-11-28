//*************************************************************************
//	��������:	2015-1-5
//	�ļ�����:	FKCW_Pixel_StaticPixelSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Pixel_Macros.h"
//-------------------------------------------------------------------------
class FKCW_Pixel_StaticPixelSprite:public CCSprite
{
public:
	FKCW_Pixel_StaticPixelSprite();
	virtual ~FKCW_Pixel_StaticPixelSprite();
	bool	init(const string&texFileName,CCSize perPixelSize=g_defaultPerPixelSize);
protected:
	CCSize m_perPixelSize;
};