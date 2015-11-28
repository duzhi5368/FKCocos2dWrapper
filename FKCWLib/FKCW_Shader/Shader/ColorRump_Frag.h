//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	ColorRump_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
static const GLchar* ShaderColorRampFrag = 
	"																						\n\
	#ifdef GL_ES																			\n\
	precision mediump float;																\n\
	#endif																					\n\
	varying vec2 v_texCoord;																\n\
	uniform sampler2D u_texture;															\n\
	uniform sampler2D u_colorRampTexture;													\n\
	void main()																				\n\
	{																						\n\
	vec3 normalColor = texture2D( u_texture, v_texCoord ).rgb;								\n\
	float rampedR = texture2D( u_colorRampTexture, vec2( normalColor.r, 0 )).g;				\n\
	float rampedG = texture2D( u_colorRampTexture, vec2( normalColor.r, 0 )).g;				\n\
	float rampedB = texture2D( u_colorRampTexture, vec2( normalColor.r, 0 )).b;				\n\
	gl_FragColor = vec4( rampedR, rampedG, rampedB, 1 );									\n\
	}";

//--------------------------------------------------------