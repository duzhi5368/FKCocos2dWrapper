//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	OldPhoto_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
USING_NS_CC;
//-------------------------------------------------------------------------
static const char* ShaderOldPhotoFrag = 
	"																													\n\
	#ifdef GL_ES 								 																		\n\
		precision mediump float; 					 																	\n\
	#endif 																												\n\
																														\n\
	uniform sampler2D u_texture; 				 																		\n\
	varying vec2 v_texCoord; 					 																		\n\
	varying vec4 v_fragmentColor; 																						\n\
																														\n\
	void main(void) 							 																		\n\
	{ 											 																		\n\
		// vec3( 0.299, 0.587, 0.114 ) ��RGBתYUV�Ĳ���ֵ�����ɻ�ɫͼ														\n\
		float MixColor = dot(texture2D(u_texture, v_texCoord).rgb, vec3(0.299, 0.587, 0.114));							\n\
		// ʹ�û�ɫͼ������ɫ���																							\n\
		vec4 blendColor = vec4( 1.2, 1.0, 0.8, 1.0 ); // �������ֵ���޸����ջ��ɫֵ										\n\
		gl_FragColor = vec4(MixColor * blendColor.r, MixColor * blendColor.g, MixColor * blendColor.b, blendColor.a);	\n\
	}";
//-------------------------------------------------------------------------