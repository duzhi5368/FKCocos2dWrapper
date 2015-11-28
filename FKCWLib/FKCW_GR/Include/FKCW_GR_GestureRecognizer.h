//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_GR_GestureRecognizer.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_GR_Macros.h"
//-------------------------------------------------------------------------
// ����ʶ���
class FKCW_GR_GestureRecognizer : public CCLayer
{
protected:
	CCRect				m_tagFrame;				// һ����Ч�ķ�Χ��
	bool				m_bIsRecognizing;		// �Ƿ����ڽ�������ʶ��
	SEL_CallFuncO		m_pSelector;			// ��Ϣ���մ�����
	CCObject*			m_pTarget;				// ��Ϣ���ն���
	CCTouchDispatcher*	m_pDispatcher;
	CC_SYNTHESIZE(bool, m_bIsCancelsTouchesInView, CancelsTouchesInView);	// ���������ȷ��ʶ���Ƿ�ȡ����������������ͼ��ȱʡֵfalse��
public:
	FKCW_GR_GestureRecognizer();
	virtual			~FKCW_GR_GestureRecognizer();
	// ��������ʶ�������ʹ�����
	void			SetTarget( CCObject* tar, SEL_CallFuncO sel );

	virtual void	setParent(CCNode* parent);
	virtual void	registerWithTouchDispatcher(void);
protected:
	void			_GestureRecognized(CCObject * gesture);
	void			_StopTouchesPropagation(CCSet * pTouches, CCEvent * pEvent);
	bool			_IsPositionBetweenBounds(CCPoint pos);
	float			_DistanceBetweenPoints(CCPoint p1, CCPoint p2);
	CCSet*			_CreateSetWithTouch(CCTouch * pTouch);

	virtual bool	ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)=0;
	virtual void	ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent)=0;
	virtual void	ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)=0;
};