//*************************************************************************
//	��������:	2014-10-29
//	�ļ�����:	Shine_Vert.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
const char* ShaderShineVert = "\n\
							  attribute vec4 a_position;\n\
							  attribute vec2 a_texCoord;\n\
							  attribute vec4 a_color;\n\
							  \n\
							  #ifdef GL_ES\n\
							  varying lowp vec4 v_fragmentColor;\n\
							  varying mediump vec2 v_texCoord;\n\
							  varying lowp vec4 v_position;\n\
							  #else\n\
							  varying vec4 v_fragmentColor;\n\
							  varying vec2 v_texCoord;\n\
							  varying vec4 v_position;\n\
							  #endif\n\
							  \n\
							  void main()	{\n\
							  gl_Position = CC_MVPMatrix * a_position;\n\
							  v_position = a_position;\n\
							  v_fragmentColor = a_color;\n\
							  v_texCoord = a_texCoord;\n\
							  }";