//*************************************************************************
//	��������:	2014-11-28
//	�ļ�����:	FKCW_RenderEx_JoystickNode.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_RenderEx_Macros.h"
//-------------------------------------------------------------------------
enum ENUM_JoystickEventType
{
	JET_TOUCH_BEGIN,
	JET_TOUCH_MOVE,
	JET_TOUCH_END
};

// interval��ʱ����,�����x��y�ķ�Χ����0-1.0F,JoystickEventType�����ͣ���ʼ,�ƶ�,������
typedef void (CCObject::*SEL_JoystickEvent)(float interval,float x, float y,ENUM_JoystickEventType type);
#define joystickEvent_selector(_SELECTOR) (SEL_JoystickEvent)(&_SELECTOR)
//-------------------------------------------------------------------------
/**
 * @brief һ������ҡ����
 *
 * ���ݸ�,�����Ͱ�ť�����Ǿ�����,���ǵ�ê��һֱ����ccp(0.5,0.5)
 * ������setHandleEventListener��������ҡ��ҡ���¼��Ĵ���
 */
class FKCW_RenderEx_JoystickNode : public CCNode,public CCTargetedTouchDelegate
{
public:
	FKCW_RenderEx_JoystickNode():m_bMove(false){}
	virtual ~FKCW_RenderEx_JoystickNode(){}

	/**
	 * ����һ��ҡ��ʵ���ľ�̬����
	 *@param fnBg ����ͼƬ���ļ���,��������ҡ�˵ĵ��̾���
	 *@param bgRadius ҡ�˵ĵ��̵İ뾶
	 *@param fnHandle ҡ��ͼƬ���ļ���,��������ҡ�˾���
	 *@param handleRadius ҡ�˵İ뾶
	 */
	static FKCW_RenderEx_JoystickNode* create(const char *fnBg,     float bgRadius,
					        const char *fnHandle, float handleRadius);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void onEnter();
	void onExit();

	// ����ҡ���ƶ�ʱҪ���õķ������������������Ϊvoid f��float interval, float x, float y��,interval��ʱ�����������x��y�ķ�Χ����0-1.0F
	void setHandleEventListener(CCObject *target, SEL_JoystickEvent selector);

	// �������ÿһ֡��������,���������ҡ���¼��Ĵ���Ļ���������ĸ�������
	void callHandleEvent(float interval);
protected:
	CCSprite*			m_bg;				// ���̵ľ���
	CCSprite*			m_handle;			// ҡ�˵ľ���
	float				m_bgRadius;         // ���̵İ뾶
	float				m_handleRadius;     // ҡ�˵İ뾶
	bool				m_bMove;		    // ҡ���Ƿ������ƶ�
	CCPoint				m_handlePos;		// ҡ���ڵ�������ϵ������
	CCObject*			m_touchEventListener;
    SEL_JoystickEvent   m_touchEventSelector;

	bool init(const char *fnBg,     float bgRadius,
			  const char *fnHandle, float handleRadius);
};
