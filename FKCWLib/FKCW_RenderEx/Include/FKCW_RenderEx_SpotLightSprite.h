//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	FKCW_RenderEx_SpotLightSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	�����Ч������
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
class FKCW_RenderEx_SpotLightSprite : public CCSprite
{
private:
	CCRenderTexture*	m_pRenderTex;
	float				m_fSpotLightRadius;
	ccColor4B			m_tagRenderColor;
	GLfloat *			m_pVertices;
	GLfloat *			m_pCoordinates;
	ccColor4B *			m_pColors;
private:
	FKCW_RenderEx_SpotLightSprite*		InitWithRenderTexture( CCRenderTexture* pRenderTex,
		float fRadius, ccColor4B tagRenderColor );
	void								SpreadOutTimer(float dt);
	void								Tick(float dt);
public:
	static FKCW_RenderEx_SpotLightSprite* Create( CCRenderTexture* pRenderTex,
		float fRadius, ccColor4B tagRenderColor );
public:
	void								RemoveSelf();
};
//-------------------------------------------------------------------------