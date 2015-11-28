//*************************************************************************
//	��������:	2014-11-11
//	�ļ�����:	FKCW_SceneExMgr_MsgDelegate.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr.h"
//-------------------------------------------------------------------------
// ��Ϣ����
struct SSenceExMsg
{
	CCObject*    pMsgObj;
	void*        wParam;
	void*        lParam;
	unsigned int uMsg;
};
//-------------------------------------------------------------------------
// ��Ϣ���������̳д������ɻ����Ϣ����
class FKCW_SceneExMgr_MsgDelegate
{
public:
	FKCW_SceneExMgr_MsgDelegate(){};

public:
	virtual void onMessage(unsigned int uMsg, CCObject* pMsgObj, void* wParam, void* lParam){};
};
//-------------------------------------------------------------------------
// ��ָ��Ŀ�����Ϣ����
struct SSceneExMsgForTarget
{
	SSenceExMsg tMessage;
	FKCW_SceneExMgr_MsgDelegate* pDelegate;
};
//-------------------------------------------------------------------------