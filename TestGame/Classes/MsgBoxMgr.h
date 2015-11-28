//*************************************************************************
//	��������:	2015-3-24
//	�ļ�����:	MsgBoxMgr.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
//-------------------------------------------------------------------------

class IMsgBoxHandle
{
public:
	virtual void	OnMessageBoxCallBack(int nMessageKey) = 0;
};
class CMsgBoxMgr : public CCObject,public ITimerHander
{
	CMsgBoxMgr(void);
	~CMsgBoxMgr(void);
public:
	static CMsgBoxMgr& instance()
	{
		static CMsgBoxMgr _inst;
		return _inst;
	}

public:
	// ��ʾ�콱��ʾ��
	//		pHandle �ص� һ�㴫�Լ�
	//		pRootWindow ������,��ʾ���addChild���˴�����
	//		nAwardType �������� ��ϸ��鿴GameCommon��ö��
	//		nDuration ��һ���û�����ȡ��ť,�������ʱ�����ʾ���Զ���ʧ Ĭ�� 30s(30s = 30*1000 ms)
	bool	ShowAwardBox(IMsgBoxHandle* pHandle,FKCW_UIWidget_WidgetWindow* pRootWindow,int nAwardType,float nDuration = 30000.0f);
	// ��ʾ��ͨ��ʾ��
	bool	Show(IMsgBoxHandle* pHandle,FKCW_UIWidget_WidgetWindow* pRootWindow,int nType,float nDuration = 30000.0f);
	// ��������
	void	Hide();
	// �жϵ�ǰ�Ƿ�����ʾ����ʾ�ڽ�����
	bool	IsShow(){ return m_bIsShowing; };
	// ��ť�ص�
	void	OnBtnHandle(CCObject* pSender);
	// ��ʱ��ʱ�䴥���ص�
	virtual void		OnTimer( unsigned int unTimerID );

private:
	void	__ShowAwardBox(int nAwardType,float nDuration = 30000.0f);
	void	__ShowNormalBox(int nType,float nDuration);
	void	__Clear();

private:

	bool						m_bIsShowing;
	IMsgBoxHandle*				m_pHandle;
	FKCW_UIWidget_WidgetWindow* m_pRootWindow;
	FKCW_UIWidget_Button*		m_pAwardBtn;
	CCNode*						m_pMsgNode;
	int							m_nMsgKey;
	
};

