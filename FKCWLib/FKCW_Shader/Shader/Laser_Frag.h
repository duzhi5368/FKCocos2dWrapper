//*************************************************************************
//	��������:	2014-10-29
//	�ļ�����:	Laser_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
// Ĭ������£�cocos2dx��CC_Time��ΪVec4,����yֵ�� ��
const char* ShaderLaserFrag = "\n\
								  #ifdef GL_ES\n\
								  precision lowp float;\n\
								  #endif\n\
								  \n\
								  varying vec2 v_texCoord;\n\
								  varying vec4 v_fragmentColor;\n\
								  \n\
								  void main()	{\n\
								  float fPosX = v_texCoord.x;\n\
								  float fPosY = v_texCoord.y;\n\
								  \n\
								  float fR = 1.0;\n\
								  float fG = 1.0;\n\
								  float fB = 1.0;\n\
								  float fA = 1.0;\n\
								  \n\
								  float fTime = abs(sin(CC_Time.y));\n\
								  if(fTime < 0.3)	{\n\
								  fTime = 0.3;\n\
								  }\n\
								  \n\
								  fR = fTime / abs(fPosX - 0.5) * 0.6;\n\
								  fG = fR * 0.3 * fTime;\n\
								  fB = fR * (1.0 - fPosY) * fTime;\n\
								  vec3 Color = vec3(fR, fG, fB);\n\
								  \n\
								  float fScale = 1.0;\n\
								  float fPercent = 0.2;\n\
								  float fDis = fPercent;\n\
								  if(fPosX < fPercent) {\n\
								  fDis = fPosX;\n\
								  }\n\
								  if(fPosX > 1.0 - fPercent) {\n\
								  fDis = 1.0 - fPosX;\n\
								  }\n\
								  fScale = fDis / fPercent;\n\
								  fA *= fScale;\n\
								  \n\
								  gl_FragColor.rgb = Color;\n\
								  gl_FragColor.a = fA;\n\
								  }";