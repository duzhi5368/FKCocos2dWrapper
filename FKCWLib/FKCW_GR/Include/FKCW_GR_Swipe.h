/********************************************************************
	created:	2014/11/05
	file base:	FKCW_GR_Swipe
	author:		FreeKnight
	
	purpose:	
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKCW_GR_GestureRecognizer.h"
//--------------------------------------------------------------------
const static int	s_SwipeMaxDuration	= 300;		// �컬���ʱ��300ms
const static int	s_SwipeMinDistance	= 60;		// �컬���پ���60����
//--------------------------------------------------------------------
enum ENUM_Swipe_Direction
{
	eSwipeDirection_Right		= 1 << 0,
	eSwipeDirection_Left		= 1 << 1,
	eSwipeDirection_Up			= 1 << 2,
	eSwipeDirection_Down		= 1 << 3
};
//--------------------------------------------------------------------
// ���ٻ�������pan��ͬ���ٶ�
class FKCW_GR_Swipe : public CCObject
{
public:
	bool init() {return true;}
	CREATE_FUNC(FKCW_GR_Swipe);
	ENUM_Swipe_Direction	m_eDirection;
	CCPoint					m_tagLocation;
};
//--------------------------------------------------------------------
class FKCW_GR_SwipeGestureRecognizer : public FKCW_GR_GestureRecognizer
{
public:
	bool init();
	~FKCW_GR_SwipeGestureRecognizer();
	CREATE_FUNC(FKCW_GR_SwipeGestureRecognizer);

	virtual bool ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent);
	virtual void ccTouchMoved(CCTouch * pTouch, CCEvent * pEvent){};
	virtual void ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent);
private:
	// ��黬������
	bool		__CheckSwipeDirection(CCPoint p1, CCPoint p2, int & dir);
private:
	CCPoint				m_tagInitialPosition;
	struct cc_timeval	m_tagStartTime;
	CC_SYNTHESIZE(int, m_nDirection, Direction);
};