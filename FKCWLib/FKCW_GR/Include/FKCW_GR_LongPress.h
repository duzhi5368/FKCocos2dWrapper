//*************************************************************************
//	��������:	2014-11-5
//	�ļ�����:	FKCW_GR_LongPress.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_GR_GestureRecognizer.h"
//-------------------------------------------------------------------------
// ���峤��ʱ��Ϊ0.5��
static const float		s_LongPressMinDuration	= 0.5f;
//-------------------------------------------------------------------------
// ��������
class FKCW_GR_LongPress : public CCObject
{
public:
	bool		init(){ return true; }
	CREATE_FUNC(FKCW_GR_LongPress);
	CCPoint		m_tagLocation;
};
//-------------------------------------------------------------------------
class FKCW_GR_LongPressGestureRecognizer : public FKCW_GR_GestureRecognizer
{
public:
	bool			init();
	void			TimerDidEnd(float dt);
	FKCW_GR_LongPressGestureRecognizer();
	~FKCW_GR_LongPressGestureRecognizer();
	CREATE_FUNC(FKCW_GR_LongPressGestureRecognizer) ;

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent){};
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
private:
	CCPoint			m_tagCurrLocation;
	CCTouch*		m_pCurrTouch;
	CCEvent*		m_pCurrEvent;
	CC_SYNTHESIZE(float, m_fMinimumPressDuration, MinimumPressDuration);	// ��С������ʱ��

	void		__StopGestureRecognition();
};