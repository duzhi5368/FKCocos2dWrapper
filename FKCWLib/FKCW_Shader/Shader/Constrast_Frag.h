//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	Constrast_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
// �Ա�Ч��
// ʹ��һ����ɫͼ��Ϊ����ͼ�񣬺Ͳ�ɫͼ��ϡ�
// �����صĽ�ͼƬ��ɫ����Ҷ��������󣬵õ��Ա�Ч��ShaderContrastFrag
static const char* ShaderContrastFrag = 
	"													\n\
	precision mediump float;							\n\
	uniform sampler2D u_Texture;						\n\
	varying vec2 v_texCoord; 							\n\
	varying vec4 v_fragmentColor;						\n\
	\n\
	void main()											\n\
	{													\n\
	float T = 2.0;									\n\
	vec2 st = v_texCoord.st;						\n\
	vec3 irgb = texture2D(u_Texture, st).rgb;		\n\
	vec3 target = vec3(0.5, 0.5, 0.5);				\n\
	gl_FragColor = vec4(mix(target, irgb, T), 1.);	\n\
	}";