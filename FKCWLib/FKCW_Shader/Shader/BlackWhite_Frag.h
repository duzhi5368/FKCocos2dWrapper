//*************************************************************************
//	��������:	2015-1-8
//	�ļ�����:	BlackWhite_Frag.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
// �ڰ�
// תΪ�Ҷ�ͼ��Ȼ����ݷ�ֵ��תΪ�ڰ�
static const char* ShaderBlackWhiteFrag = 
	"													\n\
	precision mediump float;							\n\
	uniform sampler2D u_Texture;						\n\
	varying vec2 v_texCoord; 							\n\
	varying vec4 v_fragmentColor;						\n\
	const vec4 W = vec4(0.2125, 0.7154, 0.0721, 0);		\n\
	\n\
	void main()											\n\
	{													\n\
	vec4 col = texture2D(u_Texture, v_texCoord.st);	\n\
	float lum = dot(col, W);						\n\
	if (0.5 < lum) {								\n\
	gl_FragColor = v_fragmentColor;					\n\
	} else {										\n\
	gl_FragColor = vec4(0, 0, 0, 1);}				\n\
	}";