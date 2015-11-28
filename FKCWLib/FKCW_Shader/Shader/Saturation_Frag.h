//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	Saturation_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// ����
// ��ϲ�ɫͼƬ��������ͼ�Ļҽף��õ�����ͼ
static const char* ShaderSaturationFrag =
	"													\n\
	precision mediump float;							\n\
	uniform sampler2D u_Texture;						\n\
	varying vec2 v_texCoord; 							\n\
	varying vec4 v_fragmentColor;						\n\
	const vec3 W = vec3(0.2125, 0.7154, 0.0721);		\n\
	\n\
	void main()											\n\
	{													\n\
	float T = 3.0;											\n\
	vec2 st = v_texCoord.st;								\n\
	vec3 irgb = texture2D(u_Texture, st).rgb; 				\n\
	float luminance = dot(irgb, W);							\n\
	vec3 target = vec3(luminance, luminance, luminance); 	\n\
	gl_FragColor = vec4(mix(target, irgb, T), 1.);			\n\
	}";