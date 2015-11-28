//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_MsgManager.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_MsgDelegate.h"
#include "FKCW_SceneExMgr.h"
//-------------------------------------------------------------------------
// ��Ϣ������
class FKCW_SceneExMgr_MsgManager : public CCObject
{
public:
	virtual ~FKCW_SceneExMgr_MsgManager();
	static FKCW_SceneExMgr_MsgManager* sharedManager();

	// ��һ֡��������Ϣ��ȫ��������
	void PostMessage(unsigned int uMsg, CCObject* pMsgObj = NULL, void* wParam = NULL, void* lParam = NULL);
	// ��һ֡��������Ϣ��ָ��������
	void PostMessage(FKCW_SceneExMgr_MsgDelegate* pDelegate, unsigned int uMsg,
		CCObject* pMsgObj = NULL, void* wParam = NULL, void* lParam = NULL);
	// ע��һ���µ���Ϣ������
	void RegisterMsgDelegate(FKCW_SceneExMgr_MsgDelegate* pDelegate);
	// ж��һ����Ϣ������
	void UnregisterMsgDelegate(FKCW_SceneExMgr_MsgDelegate* pDelegate);

public:
	// ÿ֡����
	void update();

private:
	FKCW_SceneExMgr_MsgManager();

	bool											m_bDispatchMsgLocked;
	std::vector<SSenceExMsg>						m_vMsgTemps;
	std::vector<SSenceExMsg>						m_vMsgQueue;
	std::vector<SSceneExMsgForTarget>				m_vTargetMsgTemps;
	std::vector<SSceneExMsgForTarget>				m_vTargetMsgQueue;
	std::vector<FKCW_SceneExMgr_MsgDelegate*>		m_vMsgDelegates;
	std::vector<FKCW_SceneExMgr_MsgDelegate*>		m_vMsgDelegatesRemoved;
	std::vector<FKCW_SceneExMgr_MsgDelegate*>		m_vMsgDelegatesAdded;

};