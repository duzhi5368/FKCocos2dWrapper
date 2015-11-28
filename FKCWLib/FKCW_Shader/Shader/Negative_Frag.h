//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	Negative_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
// ��ɫ
// �����أ�ʹ�ð�ɫ��ȥ��ǰ������ɫ�õ�
static const GLchar* ShaderNegativeFrag =					
	"													\n\
	precision mediump float;							\n\
	uniform sampler2D u_Texture;						\n\
	varying vec2 v_texCoord; 							\n\
	varying vec4 v_fragmentColor;						\n\
	void main()											\n\
	{													\n\
	float T = 1.0; 										\n\
	vec2 st = v_texCoord.st;							\n\
	vec3 irgb = texture2D(u_Texture, st).rgb;			\n\
	vec3 neg = vec3(1., 1., 1.)-irgb;					\n\
	gl_FragColor = vec4(mix(irgb,neg, T), 1.);			\n\
	}";