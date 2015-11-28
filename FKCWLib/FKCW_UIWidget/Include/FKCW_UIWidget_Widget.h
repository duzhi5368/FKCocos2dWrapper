//*************************************************************************
//	��������:	2014-12-4
//	�ļ�����:	FKCW_UIWidget_Widget.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	���
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UIWidget_Protocol.h"
#include "FKCW_UIWidget_Macros.h"
//-------------------------------------------------------------------------
class FKCW_UIWidget_Widget : public FKCW_UIWidget_TouchProtocol
{
public:
	FKCW_UIWidget_Widget();
	virtual ~FKCW_UIWidget_Widget();
public:
	// ��ȡ�û��Զ����ǩ�������ǩ��cocos2dx��tagû���κι�����
	int getUserTag() const;
	// �����û��Զ����ǩ
	void setUserTag(int nTag);

	// ��ȡ���ID
	const char* getId();
	// �������ID
	void setId(const char* id);

	// ��ȡ���������Ϣ
	const char* getDescription();
	// �������������Ϣ
	void setDescription(const char* description);

	// �ж�����Ƿ���Ч������Ч���������κδ�����Ϣ��
	virtual bool isEnabled();
	// ���������Ч��
	virtual void setEnabled(bool bEnabled);

	// �ж�����Ƿ�����Ч������Ч���򲻴����κδ�����Ϣ��
	virtual bool isTouchEnabled();
	// ��������Ƿ�������Ϣ
	virtual void setTouchEnabled(bool bTouchEnabled);

	// �жϵ�ǰ�ؼ��Ĵ�����Ϣ
	virtual void interruptTouchCascade(CCTouch* pTouch, float fDuration);
	// �жϵ�ǰ�ؼ��Ĵ�����Ϣ�����̵���touchȡ��
	virtual void interruptTouch(CCTouch* pTouch, float fDuration);
	// �жϴ����Ƿ��ж�
	virtual bool isTouchInterrupted();

	// ���ô��� ��ʼ / �ƶ� / ���� / ȡ�� ��Ϣ������
	virtual void setOnTouchBeganListener(CCObject* pListener, SEL_TouchBeganHandler pHandler);
	virtual void setOnTouchMovedListener(CCObject* pListener, SEL_TouchEventHandler pHandler);
	virtual void setOnTouchEndedListener(CCObject* pListener, SEL_TouchEventHandler pHandler);
	virtual void setOnTouchCancelledListener(CCObject* pListener, SEL_TouchEventHandler pHandler);

public:
	// ���к�������ʵ��
	virtual ENUM_WidgetTouchModel onTouchBegan(CCTouch* pTouch){ return eWidgetTouchNone; }
	virtual void onTouchMoved(CCTouch* pTouch, float fDuration){}
	virtual void onTouchEnded(CCTouch* pTouch, float fDuration){}
	virtual void onTouchCancelled(CCTouch* pTouch, float fDuration){}
public:
	// ִ�д��� ��ʼ / �ƶ� / ���� / ȡ�� ��Ϣ����
	virtual ENUM_WidgetTouchModel executeTouchBeganHandler(CCTouch* pTouch);
	virtual void executeTouchMovedHandler(CCTouch* pTouch, float fDuration);
	virtual void executeTouchEndedHandler(CCTouch* pTouch, float fDuration);
	virtual void executeTouchCancelledHandler(CCTouch* pTouch, float fDuration);

public:
	virtual void setLongClickTouchHandlerWidget(CCNode* pWidget, int id);

protected:
	// �������
	void					setThisObject(CCObject* pThis);

protected:
	std::string				m_strId;				// ���ID
	std::string				m_strDescription;		// �������������
	int						m_nUserTag;				// �û��Զ����ǩ����cocos2dx��tagû���κι�����
	bool					m_bEnabled;				// ����Ƿ���Ч������Ч���������κ���Ϣ
	bool					m_bTouchEnabled;		// ����Ƿ�������Ϣ
	bool					m_bTouchInterrupt;

	CCObject*				m_pThisObject;
	CCObject*				m_pTouchBeganListener;
	CCObject*				m_pTouchMovedListener;
	CCObject*				m_pTouchEndedListener;
	CCObject*				m_pTouchCancelledListener;

	SEL_TouchBeganHandler	m_pTouchBeganHandler;
	SEL_TouchEventHandler	m_pTouchMovedHandler;
	SEL_TouchEventHandler	m_pTouchEndedHandler;
	SEL_TouchEventHandler	m_pTouchCancelledHandler;

#if FKCW_WIDGET_USING_LUA
protected:
	int						m_nTouchBeganScriptHandler;
	int						m_nTouchMovedScriptHandler;
	int						m_nTouchEndedScriptHandler;
	int						m_nTouchCancelledScriptHandler;
public:
	virtual void			setOnTouchBeganScriptHandler(int nHandler);
	virtual void			setOnTouchMovedScriptHandler(int nHandler);
	virtual void			setOnTouchEndedScriptHandler(int nHandler);
	virtual void			setOnTouchCancelledScriptHandler(int nHandler);
	virtual void			removeOnTouchBeganScriptHandler();
	virtual void			removeOnTouchMovedScriptHandler();
	virtual void			removeOnTouchEndedScriptHandler();
	virtual void			removeOnTouchCancelledScriptHandler();
#endif
};