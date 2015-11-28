//*************************************************************************
//	��������:	2014-12-4
//	�ļ�����:	FKCW_UIWidget_WidgetWindow.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	�������
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_UIWidget_Macros.h"
#include "FKCW_UIWidget_Widget.h"
#include "FKCW_UIWidget_Protocol.h"
//-------------------------------------------------------------------------
class FKCW_UIWidget_WidgetWindow : public CCNodeRGBA, public CCTouchDelegate
{
public:
	FKCW_UIWidget_WidgetWindow();
	virtual ~FKCW_UIWidget_WidgetWindow();
public:
	// Ĭ�ϳ�ʼ��
	virtual bool init();
	// Ĭ�ϴ���
	static FKCW_UIWidget_WidgetWindow* create();

	// ��ȡ������Ϣ�㼶
	virtual int getTouchPriority();
	// ������Ϣ�����㼶���������������ڵ㣩
	virtual void setTouchPriority(int nTouchPriority);

	// �Ƿ�ǰ�����˴�����Ϣ����
	virtual bool isTouchEnabled();
	// ���ô�����Ϣ�Ŀ����ر�
	virtual void setTouchEnabled(bool bTouchEnabled);

	// �Ƿ����㴥����Ϣ
	bool isMultiTouchEnabled() const;
	// �����Ƿ����㴥����Ϣ
	void setMultiTouchEnabled(bool bEnabled);

	// �����Ƿ�Ϊģ̬
	void setModalable(bool bModalable);
	// �Ƿ�Ϊģ̬
	bool isModalable() const;

	// ����������е�һ��ID��������
	CCObject* findWidgetById(const char* id);

	// ��������ƶ� ��Ϣ������
	virtual void setOnTouchMovedAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler);
	// �������̧�� ��Ϣ������
	virtual void setOnTouchEndedAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler);
	// �������ȡ�� ��Ϣ������
	virtual void setOnTouchCancelledAfterLongClickListener(CCObject* pListener, SEL_AfterLongClickHandler pHandler);

public:
	virtual void	visit();
	virtual void	onEnter();
	virtual void	onExit();

	virtual bool	ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	virtual void	ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
	virtual void	ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
	virtual void	ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent);

	virtual void	ccTouchesBegan(CCSet* pTouches, CCEvent* pEvent);
	virtual void	ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent);
	virtual void	ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent);
	virtual void	ccTouchesCancelled(CCSet* pTouches, CCEvent* pEvent);

	virtual void	setLongClickTouchHandlerWidget(CCObject* pWidgetObject, int nTouchId);

	CCObject*		find(CCArray* pChidren, const char* id);

	virtual void	executeTouchMovedAfterLongClickHandler(CCObject* pSender, CCTouch* pTouch, float fDuration);
	virtual void	executeTouchEndedAfterLongClickHandler(CCObject* pSender, CCTouch* pTouch, float fDuration);
	virtual void	executeTouchCancelledAfterLongClickHandler(CCObject* pSender, CCTouch* pTouch, float fDuration);

protected:
	struct SMultiTouchTarget
	{
		FKCW_UIWidget_Widget*	pWidget;
		CCObject*				pLongClickedWidgetObject;
		float					fTouchedDuration;
	};
	std::map<int, SMultiTouchTarget> m_mMultiTouchKeeper;

protected:
	int							m_nTouchPriority;
	bool						m_bTouchEnabled;
	float						m_fTouchedDuration;
	bool						m_bIsTouched;
	bool						m_bMultiTouchEnabled;
	bool						m_bModalable;

	CCObject*					m_pLongClickedWidgetObject;
	FKCW_UIWidget_Widget*		m_pSelectedWidget;

	CCObject*					m_pTouchMovedAfterLongClickListener;
	CCObject*					m_pTouchEndedAfterLongClickListener;
	CCObject*					m_pTouchCancelledAfterLongClickListener;

	SEL_AfterLongClickHandler	m_pTouchMovedAfterLongClickHandler;
	SEL_AfterLongClickHandler	m_pTouchEndedAfterLongClickHandler;
	SEL_AfterLongClickHandler	m_pTouchCancelledAfterLongClickHandler;

#if FKCW_WIDGET_USING_LUA
protected:
	int							m_nTouchMovedAfterLongClickScriptHandler;
	int							m_nTouchEndedAfterLongClickScriptHandler;
	int							m_pTouchCancelledAfterLongClickScriptHandler;
public:
	void						setOnTouchMovedAfterLongClickScriptHandler(int nHandler);
	void						setOnTouchEndedAfterLongClickScriptHandler(int nHandler);
	void						setOnTouchCancelledAfterLongClickScriptHandler(int nHandler);
	void						removeOnTouchMovedAfterLongClickScriptHandler();
	void						removeOnTouchEndedAfterLongClickScriptHandler();
	void						removeOnTouchCancelledAfterLongClickScriptHandler();
#endif
};