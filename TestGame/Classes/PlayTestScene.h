//*************************************************************************
//	��������:	2015-3-19
//	�ļ�����:	AudioTestScene.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:  ����ģ�� - Play
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
#include "StarManger.h"
//-------------------------------------------------------------------------
class CPlayTestScene :
	public FKCW_SceneExMgr_SceneEx,public IMessageHandler
{
public:
	CREATE_SCENE_FUNC(CPlayTestScene);
public:
	CPlayTestScene();
	// ��ʼ�첽������Դ
	virtual void onLoadResources();
	// �����߼���ʼ��
	virtual void onLoadScene();
	// ��������ʾʱ����
	virtual void onEnterScene();
	// ����������ʱ����
	virtual void onExitScene();
	// ���յ���Ϣ[ע�⣬�յ�����Ϣ�ڣ���������Ϣ�룬������������Ϣ��]
	// ������szMsgData �յ�������ָ��
	// ������nLen �յ������ݳ���
	virtual void OnNetMessage( const char* szMsgData, int nLen );

public:

	void	onClick(CCObject* pSender);
	void	OnSelectBtn(CCObject* pSender);
	bool	OnLabelTouchEnded(CCObject* pSender, CCTouch* pTouch, float fDuration);
private:

	void	__AddListenNetMessage();
	void	__RemovListenNetMessage();
	void	__CreatePlayUI();
	void	__CreateBGUI();
	void	__CreateStar();
	FKCW_UIWidget_Button* __CreateButton(
		int nType,CCPoint& pos,const char* pszImageName,const char* pszImageSecectName,const char* pszName);

private:
	FKCW_UIWidget_WidgetWindow*	m_pRootWindow;
	FKCW_UIWidget_WidgetWindow* m_pStarWindow;
	CStarManger					m_StarMgr;
	FKCW_UIWidget_WidgetWindow* m_pEffectsWindow;
	FKCW_UIWidget_Label*		m_pMoneyLabel;
	FKCW_UIWidget_ImageView*	m_pItemBgImage;
	FKCW_UIWidget_ImageView*	m_pSoundBtnHideImage;
	FKCW_UIWidget_LabelAtlas*	m_pChapterLabel;
	FKCW_UIWidget_LabelAtlas*	m_pTargetLabel;
	FKCW_UIWidget_LabelAtlas*	m_pCurrentLabel;

public:
};

