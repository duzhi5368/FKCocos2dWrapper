//*************************************************************************
//	��������:	2015-1-15
//	�ļ�����:	LoginScene.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
#include "MsgBoxMgr.h"
//-------------------------------------------------------------------------
class CLoginScene : public FKCW_SceneExMgr_SceneEx,public IMsgBoxHandle
{
public:
	CREATE_SCENE_FUNC(CLoginScene);
public:
	CLoginScene();
	// ��ʼ�첽������Դ
	virtual void onLoadResources();
	// �����߼���ʼ��
	virtual void onLoadScene();
	// ��������ʾʱ����
	virtual void onEnterScene();
	// ����������ʱ����
	virtual void onExitScene();
	// MessageBox���º�Ļص���Ϣ
	virtual void OnMessageBoxCallBack(int nMessageKey);

public:
	// �˳���Ϸ��ť
	void OnExitBtn(CCObject* pSender);
	// ���ܰ�ť�ص� - �ڲ�������IEventSystem
	void OnSelectBtn(CCObject* pSender);

private:
	// ������¼ʱȫ��UI
	void __CreateMainUI();
	// ��ݷ�װ����������button
	FKCW_UIWidget_Button* __CreateButton(
		int nType,CCPoint& pos,const char* pszImageName,
		const char* pszImageSecectName,const char* pszName);
};