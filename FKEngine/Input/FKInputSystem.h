//*************************************************************************
//	��������:	2015-1-14
//	�ļ�����:	FKInputSystem.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../FKEngineCommonHead.h"
//-------------------------------------------------------------------------
class FKInputSystem : public IInputSystem, public CCTargetedTouchDelegate,
	public CCKeypadDelegate, public CCObject
{
public:
	FKInputSystem();
	~FKInputSystem();
public:
	// ��ʼ������
	virtual bool	Init();
	// �����ͷ�
	virtual void	Release();
	// ������Ϣ�ص�������
	virtual void	SetInputMsgCallback( IInputMsgHandler* pInputMsgCallback );
	// �����Ƿ��������봦��
	virtual void	SetInputEnabled( bool bEnable );
	// ��ȡ��Ϣ�ص�������
	virtual IInputMsgHandler* GetInputMsgCallback() const;
protected:
	// ������ʼ�ص�
	virtual bool	ccTouchBegan(CCTouch* touch, CCEvent* event);
	// �����ƶ��ص�
	virtual void	ccTouchMoved(CCTouch* touch, CCEvent* event);
	// ���������ص�
	virtual void	ccTouchEnded(CCTouch* touch, CCEvent* event);
	// Android��iOS�ϵĺ��˼����»ص�
	virtual void	keyBackClicked();
	// Android��iOS�ϵ�Menu�����»ص�
	virtual void	keyMenuClicked();
protected:
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	// WINDOWS ��Ϣ
	static void WinKeyboardHook( UINT message,WPARAM wParam, LPARAM lParam );
#endif
	// ��������֧��
	void onLongPress(CCObject* object);
	void onPan(CCObject* object);
	void onPinch(CCObject* object);
	void onSwipe(CCObject* object);
	void onTap(CCObject* object);
private:
	IInputMsgHandler*		m_pMsgCallback;		// ��Ϣ�ص��ӿ�
};
//-------------------------------------------------------------------------
extern FKInputSystem gs_FKInputSystem;
//-------------------------------------------------------------------------