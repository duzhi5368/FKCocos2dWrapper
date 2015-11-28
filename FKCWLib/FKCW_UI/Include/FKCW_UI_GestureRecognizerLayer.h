//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_UI_GestureRecognizerLayer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "cocos2d.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
// ����ʶ���
class FKCW_UI_GestureRecognizerLayer : public CCLayer
{
protected:
	CCRect				m_tagFrame;				// һ����Ч�ķ�Χ��
	bool				m_bIsRecognizing;		// �Ƿ����ڽ�������ʶ��
	SEL_CallFuncO		m_pSelector;			// ��Ϣ���մ�����
	CCObject*			m_pTarget;				// ��Ϣ���ն���
	CCTouchDispatcher*	m_pDispatcher;
	CC_SYNTHESIZE(bool, m_bIsCancelsTouchesInView, CancelsTouchesInView);	// ���������ȷ��ʶ���Ƿ�ȡ����������������ͼ��ȱʡֵfalse��
public:
	FKCW_UI_GestureRecognizerLayer();
	~FKCW_UI_GestureRecognizerLayer();

	void			SetTarget( CCObject* tar, SEL_CallFuncO sel );

	virtual void	setParent(CCNode* parent);
	virtual void	registerWithTouchDispatcher(void);
protected:
	void			_GestureRecognized(CCObject * gesture);
	void			_StopTouchesPropagation(CCSet * pTouches, CCEvent * pEvent);
	bool			_IsPositionBetweenBounds(CCPoint pos);
	float			_DistanceBetweenPoints(CCPoint p1, CCPoint p2);
	CCSet*			_CreateSetWithTouch(CCTouch * pTouch);

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)=0;
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)=0;
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)=0;
};