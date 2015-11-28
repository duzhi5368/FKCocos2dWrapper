//*************************************************************************
//	��������:	2015-3-23
//	�ļ�����:	AchieTestScene.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	�ɾ�ϵͳ
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
#include "../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CAchieTestScene :
	public FKCW_SceneExMgr_SceneEx
{
public:
	CREATE_SCENE_FUNC(CAchieTestScene);
public:
	CAchieTestScene();
	// ��ʼ�첽������Դ
	virtual void onLoadResources();
	// �����߼���ʼ��
	virtual void onLoadScene();
	// ��������ʾʱ����
	virtual void onEnterScene();
	// ����������ʱ����
	virtual void onExitScene();

	//���뱾��csv�ɾ�����
	virtual void onLoadCVS();
	//��csv�ɾ����ݼ��ص�ListViews��
	virtual void _AddToList(const char* pStr);

public:

	void	onClick(CCObject* pSender);

public:
	FKCW_UIWidget_ImageView* m_pBackGroundImage;
	FKCW_Base_CSVLoader*		m_pLoader;
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	CCEditBox*					m_pFileEdit;
	FKCW_UIWidget_ListView*		m_pListView;

};

