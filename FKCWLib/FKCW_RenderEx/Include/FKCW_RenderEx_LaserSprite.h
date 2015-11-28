//*************************************************************************
//	��������:	2014-11-7
//	�ļ�����:	FKCW_RenderEx_LaserSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// ���⣬���侫��
class FKCW_RenderEx_LaserSprite : public CCSprite
{
protected:
	FKCW_RenderEx_LaserSprite();
public:
	virtual ~FKCW_RenderEx_LaserSprite();
	static FKCW_RenderEx_LaserSprite* Create( float w, float h );

	virtual bool initWithTexture(CCTexture2D *pTexture);
	virtual void setTexture(CCTexture2D *texture);

	void setWidth(float w);
	void setHeight(float h);
};