//-------------------------------------------------------------------------
#include "../Include/FKCW_RenderEx_JoystickNode.h"
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::setHandleEventListener(CCObject *target, SEL_JoystickEvent selector)
{
	m_touchEventListener = target;
	m_touchEventSelector = selector;
}
//-------------------------------------------------------------------------
FKCW_RenderEx_JoystickNode* FKCW_RenderEx_JoystickNode::create(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
	FKCW_RenderEx_JoystickNode *joystick = new FKCW_RenderEx_JoystickNode();
	if (joystick && joystick->init(fnBg,bgRadius,fnHandle,handleRadius))
	{
		joystick->autorelease();
		return joystick;
	}

	CC_SAFE_DELETE(joystick);
	return NULL;
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_JoystickNode::init(const char *fnBg,float bgRadius,const char *fnHandle,float handleRadius)
{
	//创建底盘精灵
	m_bg = CCSprite::create(fnBg);
	if(!m_bg)
		return false;
	this->addChild(m_bg);

	//创建摇杆精灵
	m_handle = CCSprite::create(fnHandle);
	if(!m_handle)
		return false;
	this->addChild(m_handle);

	//初始化参数
	m_touchEventListener = 0;
	m_touchEventSelector = 0;
	m_bgRadius     = bgRadius;
	m_handleRadius = handleRadius;
	m_handlePos    = ccp(0.0f,0.0f);

	//设置底盘的大小
	float bgDiameter = bgRadius * 2;
	CCSize oriBgSize = m_bg->getContentSize();
	m_bg->setScaleX(bgDiameter / oriBgSize.width);
	m_bg->setScaleY(bgDiameter / oriBgSize.height);

	//设置摇杆的大小
	float handleDiameter = handleRadius * 2;
	CCSize oriHandleSize = m_handle->getContentSize();
	m_handle->setScaleX(handleDiameter / oriHandleSize.width);
	m_handle->setScaleY(handleDiameter / oriHandleSize.height);

	//设置定时器
	this->schedule(schedule_selector(FKCW_RenderEx_JoystickNode::callHandleEvent));

	return true;
}
//-------------------------------------------------------------------------
bool FKCW_RenderEx_JoystickNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint point = this->convertTouchToNodeSpaceAR(pTouch);

	//判断触点是否在摇杆上
	if(point.x*point.x+point.y*point.y < m_handleRadius*m_handleRadius)
	{
		m_bMove = true;

		CCPoint pos = m_handle->getPosition();
		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_BEGIN);

		return true;
	}
	else
		return false;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//将摇杆限制在底盘的范围内
	CCPoint point = this->convertTouchToNodeSpaceAR(pTouch);

	if(point.x*point.x+point.y*point.y > m_bgRadius*m_bgRadius)
	{
		point = point.normalize();
		point = point * m_bgRadius;
	}

	m_handle->setPosition(point);
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos = m_handle->getPosition();
	if(m_touchEventListener && m_touchEventSelector)
		(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_END);

	m_handle->setPosition(ccp(0.0f,0.0f));

	m_bMove = false;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint pos = m_handle->getPosition();
	if(m_touchEventListener && m_touchEventSelector)
		(m_touchEventListener->*m_touchEventSelector)(0.0f,pos.x/m_bgRadius,pos.y/m_bgRadius,JET_TOUCH_END);

	m_handle->setPosition(ccp(0.0f,0.0f));

	m_bMove = false;
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::onEnter()
{
	CCNode::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::onExit()
{
	CCNode::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
//-------------------------------------------------------------------------
void FKCW_RenderEx_JoystickNode::callHandleEvent(float interval)
{
	if(m_bMove)
	{
		//调用摇杆事件处理方法
		CCPoint point = m_handle->getPosition();

		if(m_touchEventListener && m_touchEventSelector)
			(m_touchEventListener->*m_touchEventSelector)(interval,point.x/m_bgRadius,point.y/m_bgRadius,JET_TOUCH_MOVE);
	}
}
//-------------------------------------------------------------------------