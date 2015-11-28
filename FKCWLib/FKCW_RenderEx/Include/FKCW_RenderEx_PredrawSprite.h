//*************************************************************************
//	��������:	2014-11-4
//	�ļ�����:	FKCW_RenderEx_PredrawSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
// ��CCSprite�ļ�ǿ
// 1�������Ǹ���texture֮�󣬿��Ա���ԭ����blendFuncion��
// 2�����һ��Ԥ��Ⱦ��������ζ�ŵ�������CCSprite��Ⱦ֮ǰ����������һЩ�Զ���shader����
class FKCW_RenderEx_PredrawSprite : public CCSprite
{
private:
	CC_SYNTHESIZE_BOOL(m_bIsShouldUpdateBlendFunc, ShouldUpdateBlendFunc);		// true��ʾ������blendFuction
	CC_SYNTHESIZE_RETAIN(CCCallFuncO*, m_pPreDrawFunction, PreDrawFunction);	// Ԥ��Ⱦ����
protected:
	FKCW_RenderEx_PredrawSprite();
public:
	virtual ~FKCW_RenderEx_PredrawSprite();

	static FKCW_RenderEx_PredrawSprite* create();
	static FKCW_RenderEx_PredrawSprite* create(const char *pszFileName);
	static FKCW_RenderEx_PredrawSprite* create(const char *pszFileName, const CCRect& rect);
	static FKCW_RenderEx_PredrawSprite* createWithTexture(CCTexture2D *pTexture);
	static FKCW_RenderEx_PredrawSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
	static FKCW_RenderEx_PredrawSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static FKCW_RenderEx_PredrawSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);

	// ���������һ��Ԥ��Ⱦ�ص�
	virtual void draw();

	// �ú�����ֱ�ӳ��� updateBlendFunc.
	// �ڶ������һ��TexturePacker�����ԣ��У����һ�������еĲ�ͬ֡ʹ���˲�ͬ������
	// ���Ҿ���ʹ���˷�Ĭ�ϵĻ��ģʽ������ setDisplayFrame() ���Զ��ָ����ģʽ�����ԣ�
	// �����������д setTexture()���ڸ��»�Ϻ���֮ǰ����һ������ʶ
	virtual void setTexture(CCTexture2D *texture);
};