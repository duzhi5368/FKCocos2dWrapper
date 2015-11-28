//*************************************************************************
//	��������:	2014-10-29
//	�ļ�����:	Matrix_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
#define kCCUniform_colorMatrix "CC_colorMatrix"

static GLint sUniform_pos_CC_colorMatrix = -1;

const char* ShaderMatrixFrag = "\n\
								   #ifdef GL_ES \n\
								   precision lowp float; \n\
								   #endif \n\
								   \n\
								   varying vec4 v_fragmentColor; \n\
								   varying vec2 v_texCoord; \n\
								   uniform sampler2D CC_Texture0; \n\
								   uniform mat4 CC_colorMatrix; \n\
								   \n\
								   void main()	{ \n\
								   gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_texCoord); \n\
								   gl_FragColor = CC_colorMatrix * gl_FragColor; \n\
								   }";