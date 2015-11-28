//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_RenderEx_GradientSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	���侫��
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// һ���ὥ��Ч���ľ���
class FKCW_RenderEx_GradientSprite : public CCSprite
{
private:
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tagStartColor, StartColor)
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tagEndColor, EndColor)
	CC_PROPERTY(GLubyte, m_cStartOpacity, StartOpacity)
	CC_PROPERTY(GLubyte, m_cEndOpacity, EndOpacity)
	CC_PROPERTY_PASS_BY_REF(CCPoint, m_tagAlongVector, Vector)					// ��ɫ��������
	CC_PROPERTY(bool, m_bIsCompressedInterpolation, CompressedInterpolation);	// �Ƿ�ʹ��ѹ������
private:
	// ������ɫ
	void			_UpdateColor();
public:
	FKCW_RenderEx_GradientSprite();
	virtual ~FKCW_RenderEx_GradientSprite();

	static	FKCW_RenderEx_GradientSprite*	create();
	static	FKCW_RenderEx_GradientSprite*	create(const char *pszFileName);
	static	FKCW_RenderEx_GradientSprite*	create(const char *pszFileName, const CCRect& rect);
	static	FKCW_RenderEx_GradientSprite*	createWithTexture(CCTexture2D *pTexture);
	static	FKCW_RenderEx_GradientSprite*	createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
	static	FKCW_RenderEx_GradientSprite*	createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static	FKCW_RenderEx_GradientSprite*	createWithSpriteFrameName(const char *pszSpriteFrameName);

	// �̳���CCNodeRGBA
	virtual void setColor(const ccColor3B& color3);
	virtual void updateDisplayedColor(const ccColor3B& parentColor);
	virtual void setOpacity(GLubyte opacity);
	virtual void setOpacityModifyRGB(bool modify);
	virtual void updateDisplayedOpacity(GLubyte parentOpacity);

	// ���ý���ɫ
	virtual void setColor( const ccColor4B& start, const ccColor4B& end, const CCPoint& v );
	// ���
	bool	IsCompressedInterpolation(){ return getCompressedInterpolation(); }
};