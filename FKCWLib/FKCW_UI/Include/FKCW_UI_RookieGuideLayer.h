//*************************************************************************
//	��������:	2014-11-6
//	�ļ�����:	FKCW_UI_RookieGuideLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UI_Macros.h"
//-------------------------------------------------------------------------
// ����������
// �����ṩ��һ������������ָ�ϵĿ�ܡ�����Ӧ���̳�����Ϊ������Ӿ�Ԫ�ء�
// ���ฺ����ʱ���һ���UI��Ⱦ��
// ���⣬���ཫ�ὫԤ��Ŀɵ��������Ϊ͸����
class FKCW_UI_RookieGuideLayer : public CCLayer
{
protected:
	struct SRegion
	{
		CCRect			m_tagRect;				// �ɵ������
		CCCallFunc*		m_pFunc;				// �������ص�������ע�⣬������ΪNULL��������򲻿ɱ����
		bool			m_pRemoveOnTouch;		// �Ƿ�����ɾ�������򣨵��ص�������Ϊ��ʱ����ֵ��Ч ��
	public:
		SRegion()
		{
			m_tagRect = CCRectZero;
			m_pFunc = NULL;
			m_pRemoveOnTouch = false;
		}
	};
	typedef vector<SRegion>		RegionList;
protected:
	SRegion*			m_pClickedRegion;									// �û��յ����������
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(RegionList, m_vecRegions, Regions);	// �ɵ�������б�
	CC_SYNTHESIZE_PASS_BY_REF_SETTER(ccColor4B, m_tagBgColor, BgColor);		// ������ɫ
	CC_SYNTHESIZE_BOOL(m_bIsAnyTouchMode, AnyTouchMode);					// ���ⴥ��ģʽ��true���ʾ��������ط������Խ���������������
	CC_SYNTHESIZE_BOOL(m_bIsShouldCheckRegion, ShouldCheckRegion);			// �޴���ģʽ��true���ʾû���κ�������ܵ����飬�������ȫ�������¼���
	CC_SYNTHESIZE(CCClippingNode*, m_pClipper, Clipper);					// ���ֲ�
	CC_SYNTHESIZE(CCLayerColor*, m_pContent, Content);						// ���ݲ�
	CC_SYNTHESIZE(CCDrawNode*, m_pStencil, Stencil);						// ��Ƚڵ�
	CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_pOnExitFunc, OnExitFunc);			// ���뱾��Ļص�����
	CC_SYNTHESIZE_RETAIN(CCCallFunc*, m_pOnEnterFunc, OnEnterFunc);			// �뿪����Ļص�����
protected:
	FKCW_UI_RookieGuideLayer();

	// ��������ʾ��ᱻ���ã�������Ը�д�ú�����ִ���Զ�����Ϊ
	virtual void	_OnFadeInDone();
public:
	virtual ~FKCW_UI_RookieGuideLayer();
	static FKCW_UI_RookieGuideLayer* Create();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	// ������ʾ��������������
	// ע���ú�����Ҫ�����ñ���ɫ֮�����
	// ������duration �������ʱ��  delay ���붯��֮ǰ���ӳ�ʱ��
	virtual void	FadeIn( float duration, float delay = 0 );
	// ���һ���ɵ������
	// ע: ������Ӧ��������ռ����ꡣ
	//		��������ɵ�������������֮�����������㽫�Զ�ɾ������
	// ������r ����ռ����꣬����Ӧ����
	//		func ���򱻵����Ļص�����������ֵΪNULL��������Ϊ���ɵ��
	//		removeOnTouch ���ص�������ΪNULLʱ����ֵ��Ч�����ص�����ΪNULLʱ����ֵ��Ϊtrue��
	//				��ʾ�������򱻵�������Ƴ�������
	 void			AddRegion(const CCRect& r, CCCallFunc* func, bool removeOnTouch = false);
	 // ͨ��һ���ڵ����һ���ɵ������
	 // ע���������С����ڵ�İ�Χ�о�����ͬ
	 void			AddRegion(CCNode* n, CCCallFunc* func, bool removeOnTouch = false);
	 // ����һ�����������Ƴ��������д����ص�����ɾ���ûص���
	 void			SetRegionRemoveOnTouch(int index);
	 // ��ȡָ���������
	 const CCRect&	GetRegionRect(int index);
	 // ��Ч��һ������ֱ������ָ��ʱ��
	 void			EnableRegionCheckAfter(float seconds);
};