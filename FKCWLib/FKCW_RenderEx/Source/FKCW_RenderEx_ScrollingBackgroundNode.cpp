//-------------------------------------------------------------------------
#include "../Include/FKCW_RenderEx_ScrollingBackgroundNode.h"
//-------------------------------------------------------------------------
void ScrollingBackground::setBgChangeEventListener(CCObject *target, SEL_BgSpriteChangeEvent selector)
{
	m_changeEventListener = target;
	m_changeEventSelector = selector;
}
//-------------------------------------------------------------------------
void ScrollingBackground::setBgMoveEventListener(CCObject *target, SEL_BgSpriteMovbEvent selector)
{
	m_moveEventListener = target;
	m_moveEventSelector = selector;
}
//-------------------------------------------------------------------------
void ScrollingBackground::resumeScroll(float velocity) 
{
	m_velocity = velocity;
	m_isScrolling = true;
}
//-------------------------------------------------------------------------
// ��ʼ��������
bool ScrollingBackground::beginContinuousScroll(float velocity)   
{
	return _BeginScroll(velocity);
}
//-------------------------------------------------------------------------
// ��ͣ����
void ScrollingBackground::pauseScroll()  
{
	m_isScrolling = false;
}
//-------------------------------------------------------------------------
///���ص�ͼ�������ж����ŵ�ͼ����
int ScrollingBackground::getNumBgSprite()
{
	return m_bgSpriteList.size();
}
//-------------------------------------------------------------------------
float ScrollingBackground::getVelocity()					          
{
	return m_velocity;
}
//-------------------------------------------------------------------------
bool  ScrollingBackground::isListBack(CCSprite* bgBlock)  
{
	return bgBlock == m_bgSpriteList.back();
}
//-------------------------------------------------------------------------
bool  ScrollingBackground::isListFront(CCSprite* bgBlock) 
{
	return bgBlock == m_bgSpriteList.front();
}
//-------------------------------------------------------------------------
void  ScrollingBackground::setVelocity(float velocity)             
{
	m_velocity = velocity;
}
//-------------------------------------------------------------------------
CCSprite* ScrollingBackground::getBackBgSprite()		  
{
	return m_bgSpriteList.back();
}
//-------------------------------------------------------------------------
CCSprite* ScrollingBackground::getFrontBgSprite()	      
{
	return m_bgSpriteList.front();
}
//-------------------------------------------------------------------------
CCSprite* ScrollingBackground::getCurBgSprite()		      
{
	return m_curIter!=m_bgSpriteList.end() ? (*m_curIter):0;
}
//-------------------------------------------------------------------------
CCSprite* ScrollingBackground::getFollowBgSprite()	      
{
	return m_followIter!=m_bgSpriteList.end() ? (*m_followIter):0;
}
//-------------------------------------------------------------------------
ScrollingBackground* ScrollingBackground::create(ENUM_ScrollDirection direction)
{ 
	ScrollingBackground *pRet = new ScrollingBackground; 
	if (pRet && pRet->init(direction)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}
//-------------------------------------------------------------------------
ScrollingBackground::ScrollingBackground():
	m_changeEventListener(0),
	m_changeEventSelector(0),
	m_moveEventListener(0),
	m_moveEventSelector(0),
	m_sensitivity(10.0f),
	m_isScrolling(false),
	m_bScrollToNext(false),
	m_bScrollBy(false)
{
	m_bgSpriteList.clear();
}
//-------------------------------------------------------------------------
ScrollingBackground::~ScrollingBackground()
{
	m_bgSpriteList.clear();
}
//-------------------------------------------------------------------------
bool ScrollingBackground::init(ENUM_ScrollDirection direction)
{
	if(!CCNode::init())
		return false;

	m_direction   = direction;
	m_visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	this->schedule(schedule_selector(ScrollingBackground::_MoveAction));

	return true;
}
//-------------------------------------------------------------------------
bool ScrollingBackground::_BeginScroll(float velocity)
{
	if(m_bgSpriteList.size()<2)
		return false;

	m_followIter = m_curIter;
	m_followIter++;

	if(m_followIter == m_bgSpriteList.end())
		m_followIter = m_bgSpriteList.begin();

	m_isScrolling = true;
	m_velocity    = velocity;

	return true;
}
//-------------------------------------------------------------------------
bool ScrollingBackground::scrollToNextBgSprite(float velocity)
{
	if(!_BeginScroll(velocity))
		return false;

	m_bScrollToNext = true;
	m_distance      = 0.0f;
	return true;
}
//-------------------------------------------------------------------------
bool ScrollingBackground::setBgSpriteScrollBy(float velocity,float distance)
{
	if(!_BeginScroll(velocity))
		return false;

	m_distance  = fabs(distance);
	m_bScrollBy = true;

	return true;
}
//-------------------------------------------------------------------------
void ScrollingBackground::_PreSetCurPos()
{
	if(m_velocity)
	{
		ListIter preIter = m_curIter;

		if(preIter == m_bgSpriteList.begin())
			preIter = m_bgSpriteList.end();

		preIter--;

		CCPoint aPointCur = (*m_curIter)->getAnchorPoint();
		CCPoint posCur  = (*m_curIter)->getPosition();

		CCPoint aPointPre = (*preIter)->getAnchorPoint();
		CCPoint posPre;

		switch(m_direction)
		{
		case SD_RIGHT_TO_LEFT:
			posPre.x = posCur.x - aPointCur.x * m_visibleSize.width - (1.0f - aPointPre.x) * m_visibleSize.width;
			posPre.y = aPointPre.y * m_visibleSize.height;
			break;

		case SD_LEFT_TO_RIGHT:
			posPre.x = posCur.x + (1.0f - aPointCur.x) * m_visibleSize.width + aPointPre.x * m_visibleSize.width;
			posPre.y = aPointPre.y * m_visibleSize.height;
			break;

		case SD_TOP_TO_BOTTOM:
			posPre.x = aPointPre.x * m_visibleSize.width;
			posPre.y = posCur.y - aPointCur.y * m_visibleSize.height - (1.0f - aPointPre.y) * m_visibleSize.height;
			break;

		case SD_BOTTOM_TO_TOP:
			posPre.x = aPointPre.x * m_visibleSize.width;
			posPre.y = posCur.y + (1.0f - aPointCur.y) * m_visibleSize.height + aPointPre.y * m_visibleSize.height;
			break;
		}

		(*preIter)->setVisible(true);
		(*preIter)->setPosition(posPre);
	}
}
//-------------------------------------------------------------------------
bool ScrollingBackground::_IsChangeBg(const CCPoint& posCur,const CCPoint& achorPointCur)
{
	if(m_velocity>0.0f)
	{
		switch(m_direction)
		{
		case SD_RIGHT_TO_LEFT:
			return  (posCur.x < (-1.0f + achorPointCur.x) * m_visibleSize.width);

		case SD_LEFT_TO_RIGHT:
			return  (posCur.x > (1.0f + achorPointCur.x) * m_visibleSize.width);

		case SD_TOP_TO_BOTTOM:
			return  (posCur.y < (-1.0f + achorPointCur.y) * m_visibleSize.height);

		case SD_BOTTOM_TO_TOP:
			return  (posCur.y > (1.0f + achorPointCur.y) * m_visibleSize.height);

		default:
			return true;
		}
	}
	else
	{
		switch(m_direction)
		{
		case SD_RIGHT_TO_LEFT:
			return  (posCur.x > achorPointCur.x * m_visibleSize.width);

		case SD_LEFT_TO_RIGHT:
			return  (posCur.x < achorPointCur.x * m_visibleSize.width);

		case SD_TOP_TO_BOTTOM:
			return  (posCur.y > achorPointCur.y * m_visibleSize.height);

		case SD_BOTTOM_TO_TOP:
			return  (posCur.y < achorPointCur.y * m_visibleSize.height);

		default:
			return true;
		}
	}
}
//-------------------------------------------------------------------------
void ScrollingBackground::_MoveAction(float d)
{
	if(!m_isScrolling)
		return;

	CCPoint posCur  = (*m_curIter)->getPosition();
	CCPoint aPosCur = (*m_curIter)->getAnchorPoint();

	if(_IsChangeBg(posCur,aPosCur))
		_ChangeCurBgSprite();
	else
	{
		switch(m_direction)
		{
		case SD_RIGHT_TO_LEFT:
			posCur.x-=m_velocity*d;
			break;

		case SD_LEFT_TO_RIGHT:
			posCur.x+=m_velocity*d;
			break;

		case SD_TOP_TO_BOTTOM:
			posCur.y-=m_velocity*d;
			break;

		case SD_BOTTOM_TO_TOP:
			posCur.y+=m_velocity*d;
			break;
		}

		if(m_bScrollBy)
		{
			m_distance -= fabs(m_velocity)*d;
			if(m_distance<0.0f)
			{
				m_isScrolling = false;
				m_bScrollBy   = false;
			}
		}
		else if(m_bScrollToNext)
		{
			m_distance += fabs(m_velocity)*d;
		}

		(*m_curIter)->setPosition(posCur);
	}

	if(m_bgSpriteList.size()>1)
		_SetFollowNodePosition();

	if(m_moveEventListener)
	{
		CCSprite* pCur    = m_curIter!=m_bgSpriteList.end() ? (*m_curIter):0;
		CCSprite* pFollow = m_followIter!=m_bgSpriteList.end() ? (*m_followIter):0;
		(m_moveEventListener->*m_moveEventSelector)(pCur,pFollow);
	}
}
//-------------------------------------------------------------------------
bool ScrollingBackground::addBackgroundSprite(CCSprite* bgSprite)
{
	if(m_bgSpriteList.size()>1 && (*m_curIter) == m_bgSpriteList.back())
		return false;

	CCSize size = bgSprite->getContentSize();

	bgSprite->setScaleX(m_visibleSize.width  / size.width);
	bgSprite->setScaleY(m_visibleSize.height / size.height);

	bgSprite->setVisible(false);

	this->addChild(bgSprite);

	_AddListNode(bgSprite);

	return true;
}
//-------------------------------------------------------------------------
void ScrollingBackground::_AddListNode(CCSprite* bgSprite)
{
	if(m_bgSpriteList.empty())
	{
		CCPoint anchorPoint = bgSprite->getAnchorPoint();
		CCPoint pos(anchorPoint.x * m_visibleSize.width,
			anchorPoint.y * m_visibleSize.height);

		bgSprite->setVisible(true);
		bgSprite->setPosition(pos);

		m_bgSpriteList.push_back(bgSprite);
		m_curIter = m_bgSpriteList.begin();
	}
	else
		m_bgSpriteList.push_back(bgSprite);
}
//-------------------------------------------------------------------------
void ScrollingBackground::_ChangeCurBgSprite()
{
	CCSprite* bgLeave;

	if(m_velocity>0.0f)
	{
		bgLeave = (*m_curIter);
		(*m_curIter)->setVisible(false);

		m_curIter++;
		if(m_curIter == m_bgSpriteList.end())
			m_curIter = m_bgSpriteList.begin();

		m_followIter = m_curIter;
		m_followIter++;
		if(m_followIter == m_bgSpriteList.end())
			m_followIter = m_bgSpriteList.begin();
	}
	else
	{
		bgLeave = (*m_followIter);
		(*m_followIter)->setVisible(false);

		_PreSetCurPos();
		m_followIter = m_curIter;

		if(m_curIter == m_bgSpriteList.begin())
			m_curIter = m_bgSpriteList.end();

		m_curIter--;
	}

	if(m_bScrollToNext && m_distance>m_sensitivity)
	{
		m_distance      = 0.0f;
		m_isScrolling   = false;
		m_bScrollToNext = false;
		setFullScreen(m_velocity>0.0f?(*m_curIter):(*m_followIter));
	}

	if(m_changeEventListener)
	{
		CCSprite* pCur    = m_curIter!=m_bgSpriteList.end() ? (*m_curIter):0;
		CCSprite* pFollow = m_followIter!=m_bgSpriteList.end() ? (*m_followIter):0;
		(m_changeEventListener->*m_changeEventSelector)(pCur,pFollow,bgLeave);
	}
}
//-------------------------------------------------------------------------
void ScrollingBackground::_SetFollowNodePosition()
{
	CCPoint aPointCur = (*m_curIter)->getAnchorPoint();
	CCPoint posCur    = (*m_curIter)->getPosition();

	CCPoint aPointFollow = (*m_followIter)->getAnchorPoint();
	CCPoint posFollow;

	switch(m_direction)
	{
	case SD_RIGHT_TO_LEFT:
		posFollow.x = posCur.x + (1.0f - aPointCur.x) * m_visibleSize.width + aPointFollow.x * m_visibleSize.width;
		posFollow.y = aPointFollow.y * m_visibleSize.height;
		break;

	case SD_LEFT_TO_RIGHT:
		posFollow.x = posCur.x - aPointCur.x * m_visibleSize.width - (1.0f - aPointFollow.x) * m_visibleSize.width;
		posFollow.y = aPointFollow.y * m_visibleSize.height;
		break;

	case SD_TOP_TO_BOTTOM:
		posFollow.x = aPointFollow.x * m_visibleSize.width;
		posFollow.y = posCur.y + (1.0f - aPointCur.y) * m_visibleSize.height + aPointFollow.y * m_visibleSize.height;
		break;

	case SD_BOTTOM_TO_TOP:
		posFollow.x = aPointFollow.x * m_visibleSize.width;
		posFollow.y = posCur.y - aPointCur.y * m_visibleSize.height - (1.0f - aPointFollow.y) * m_visibleSize.height;
		break;
	}

	(*m_followIter)->setVisible(true);
	(*m_followIter)->setPosition(posFollow);
}
//-------------------------------------------------------------------------
void ScrollingBackground::setFullScreen(CCSprite* bgBlock)
{
	CCPoint anchorPoint = bgBlock->getAnchorPoint();
	CCPoint pos(anchorPoint.x * m_visibleSize.width,
		anchorPoint.y * m_visibleSize.height);

	bgBlock->setVisible(true);
	bgBlock->setPosition(pos);
}
//-------------------------------------------------------------------------
bool ScrollingBackground::removeBgSprite(CCSprite* bgBlock)
{
	if(m_bgSpriteList.size()>2 && bgBlock!=(*m_curIter) && bgBlock!=(*m_followIter))
	{
		m_bgSpriteList.remove(bgBlock);
		this->removeChild(bgBlock);
		return true;
	}
	return false;
}
//-------------------------------------------------------------------------