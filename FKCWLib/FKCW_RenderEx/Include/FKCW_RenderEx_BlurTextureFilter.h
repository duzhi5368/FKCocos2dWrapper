//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	FKCW_RenderEx_BlurTextureFilter.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
#include "FKCW_RenderEx_Texture2DMutable.h"
//-------------------------------------------------------------------------
class FKCW_RenderEx_BlurTextureFilter 
{
/**
	@param input: Original texture data
	@param output: Empty (or not) buffer
	@param format: Pixel format of the data
	@param width: Real width (is a power of two)
	@param height: Real height (is a power of two)
	@param position: Top left vertex of the blur effect
	@param size: The size of the blur effect
	@param contentSize:
	@param radios: It's the radius of the blur effect
*/
public:
	FKCW_RenderEx_BlurTextureFilter() {};
	~FKCW_RenderEx_BlurTextureFilter() {};
public:
	void blurInput(void* input, void* output, CCTexture2DPixelFormat format, int width, int height, CCSize contentSize, int radius, CCRect rect);
	FKCW_RenderEx_Texture2DMutable* blur(FKCW_RenderEx_Texture2DMutable* texture, int radius);
	FKCW_RenderEx_Texture2DMutable* blur(FKCW_RenderEx_Texture2DMutable* texture, int radius, CCRect rect);
};
//--------------------------------------------------------