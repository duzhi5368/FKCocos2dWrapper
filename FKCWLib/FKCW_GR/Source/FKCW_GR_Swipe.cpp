//--------------------------------------------------------------------
#include "../Include/FKCW_GR_Swipe.h"
//--------------------------------------------------------------------
bool FKCW_GR_SwipeGestureRecognizer::init()
{
	m_nDirection = 15;
	return true;
}
//--------------------------------------------------------------------
FKCW_GR_SwipeGestureRecognizer::~FKCW_GR_SwipeGestureRecognizer()
{

}
//--------------------------------------------------------------------
bool FKCW_GR_SwipeGestureRecognizer::ccTouchBegan(CCTouch * pTouch, CCEvent * pEvent)
{
	if (m_bIsRecognizing) 
	{
		m_bIsRecognizing = false;
		return false;
	}

	m_tagInitialPosition = pTouch->getLocation();
	if (!_IsPositionBetweenBounds(m_tagInitialPosition)) 
		return false;

	CCTime::gettimeofdayCocos2d(&m_tagStartTime, NULL);

	m_bIsRecognizing = true;
	return true;
}
//--------------------------------------------------------------------
void FKCW_GR_SwipeGestureRecognizer::ccTouchEnded(CCTouch * pTouch, CCEvent * pEvent)
{
	CCPoint finalPosition = pTouch->getLocation();
	if (!_IsPositionBetweenBounds(finalPosition))
	{
		m_bIsRecognizing = false;
		return;
	}

	// ����ʼ��������ͷŵ����
	float distance = _DistanceBetweenPoints(m_tagInitialPosition, finalPosition);

	struct cc_timeval currentTime;
	CCTime::gettimeofdayCocos2d(&currentTime, NULL);

	// ����ʼ��������ͷŵ���ʱ��(ms)
	double duration = CCTime::timersubCocos2d(&m_tagStartTime, &currentTime);

	// ���ʱ�䣬���룬�����Ƿ���ȷ
	int dir = 0;
	if (distance>=s_SwipeMinDistance 
		&& duration<=s_SwipeMaxDuration 
		&& __CheckSwipeDirection(m_tagInitialPosition,finalPosition,dir)) 
	{
		FKCW_GR_Swipe * swipe = FKCW_GR_Swipe::create();
		swipe->m_eDirection = (ENUM_Swipe_Direction)dir;
		swipe->m_tagLocation = m_tagInitialPosition;

		_GestureRecognized(swipe);
		if (m_bIsCancelsTouchesInView)
		{
			_StopTouchesPropagation(_CreateSetWithTouch(pTouch), pEvent);
		}
	}

	m_bIsRecognizing = false;
}
//--------------------------------------------------------------------
// ��黬������
bool FKCW_GR_SwipeGestureRecognizer::__CheckSwipeDirection(CCPoint p1, CCPoint p2, int & dir)
{
	bool right = p2.x-p1.x>=s_SwipeMinDistance;
	bool left = p1.x-p2.x>=s_SwipeMinDistance;
	bool down = p1.y-p2.y>=s_SwipeMinDistance;
	bool up = p2.y-p1.y>=s_SwipeMinDistance;

	if (right) {
		if ((m_nDirection & eSwipeDirection_Right) == eSwipeDirection_Right)
		{
			dir = eSwipeDirection_Right;
			return true;
		}
	}
	else if (left) 
	{
		if ((m_nDirection & eSwipeDirection_Left) == eSwipeDirection_Left)
		{
			dir = eSwipeDirection_Left;
			return true;
		}
	}
	else if (up) 
	{
		if ((m_nDirection & eSwipeDirection_Up) == eSwipeDirection_Up) 
		{
			dir = eSwipeDirection_Up;
			return true;
		}
	}
	else if (down) 
	{
		if ((m_nDirection & eSwipeDirection_Down) == eSwipeDirection_Down) 
		{
			dir = eSwipeDirection_Down;
			return true;
		}
	}

	return false;
}
//--------------------------------------------------------------------