//*************************************************************************
//	��������:	2015-1-5
//	�ļ�����:	FKCW_Pixel_BaseFunc.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_Pixel_Macros.h"
//-------------------------------------------------------------------------
// ��ת����
CCTexture2D*				ScaleTexUsingRTT(CCTexture2D*texture,float scaleX,float scaleY);
// ��ȡһ������ͼƬ����ɫ����
vector<vector<ccColor4B> >	GetColorMatFromImage(CCImage *image);