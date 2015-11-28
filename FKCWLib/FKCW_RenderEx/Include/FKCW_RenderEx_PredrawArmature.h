//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_RenderEx_PredrawArmature.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
#include "cocos-ext.h"
//-------------------------------------------------------------------------
USING_NS_CC_EXT;
//-------------------------------------------------------------------------
// �� CCArmature �ļ�ǿ
// ���һ��Ԥ��Ⱦ��������ζ�ŵ�������CCSprite��Ⱦ֮ǰ����������һЩ�Զ���shader����
class FKCW_RenderEx_PredrawArmature : public CCArmature
{
public:
	CC_SYNTHESIZE_RETAIN(CCCallFuncO*, m_pPreDrawFunction, PreDrawFunction);		// Ԥ��Ⱦ����
public:
	static FKCW_RenderEx_PredrawArmature* Create();
	static FKCW_RenderEx_PredrawArmature* Create(const char *name);
	static FKCW_RenderEx_PredrawArmature* Create(const char *name, CCBone *parentBone);
public:
	FKCW_RenderEx_PredrawArmature();
	~FKCW_RenderEx_PredrawArmature();
	virtual void draw();
	virtual CCTextureAtlas* getTexureAtlasWithTexture( CCTexture2D* texture );
};