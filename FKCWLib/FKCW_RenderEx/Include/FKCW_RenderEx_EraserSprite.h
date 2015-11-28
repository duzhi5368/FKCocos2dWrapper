//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_RenderEx_EraserSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	��Ƥ��Ч������
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
class FKCW_RenderEx_EraserSprite : public CCSprite, public CCTargetedTouchDelegate
{
public:
	FKCW_RenderEx_EraserSprite();
	~FKCW_RenderEx_EraserSprite();

	// ������������
	// ������ pszFileName--�����ļ���, eraserImmediately---�Ƿ������������ true---���ԣ� false---����
	//  drawType---������״�� 0---�����Σ�1---Բ�Σ� 2---�Զ�����״(����һ��ͼƬ����)
	static FKCW_RenderEx_EraserSprite* create(const char *pszFileName, const bool& eraserImmediately = true, 
		const unsigned int& drawType = 0, const float& p_fSize = 10.0f);

	virtual bool init(const char *pszFileName, const bool& eraserImmediately = true, 
		const unsigned int& drawType = 0, const float& p_fSize = 10.0f);

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

public:
	CC_PROPERTY(bool, m_bEraser, Eraser);			// �����Ƿ���Բ���
	CC_PROPERTY(float, m_fDrawWidth, DrawWidth);	// ������С��Ĭ��Ϊ10.f;
	CC_PROPERTY(bool, m_bEraserOk, EraserOk);		// �Ƿ�������

	// �Զ��������״
	// ע��ͼƬҪ���м���״���οյġ�
	void setDrawStencil(const char *pszFileName);	
private:
	// ���û��ģʽ��ʵ�ֲ���Ч��
	void eraseByBlend(CCPoint& point);
	void eraseByColorMask();

private:
	void initData(const char *pszFileName, const bool& eraserImmediately = true, 
		const unsigned int& drawType = 0, const float fSize = 10.0f );

	CCSize				m_tagSpriteSize;		// �����С
	unsigned int		m_uiDrawType;			// ������״ 0---�����Σ� 1---Բ�� 2--�Զ�����״
	CCPoint				m_touchPoint;			// ������
	CCTexture2D*		m_drawTextture;			// �Զ���ͼƬʱ�����õĲ���ͼƬ
	CCRenderTexture*	m_pRTex;				// ��Ⱦ����
	CCDrawNode*			m_pEraser;				// ��Ⱦ�ڵ�
};
