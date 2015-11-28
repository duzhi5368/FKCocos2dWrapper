//*************************************************************************
//	��������:	2015-3-23
//	�ļ�����:	ShopTestScene.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	�̳�ϵͳ
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "GameCommon.h"
//-------------------------------------------------------------------------
class CShopTestScene :
	public FKCW_SceneExMgr_SceneEx
{
public:
	CREATE_SCENE_FUNC(CShopTestScene);
public:
	CShopTestScene();
	// ��ʼ�첽������Դ
	virtual void onLoadResources();
	// �����߼���ʼ��
	virtual void onLoadScene();
	// ��������ʾʱ����
	virtual void onEnterScene();
	// ����������ʱ����
	virtual void onExitScene();

public:
	void	onClick(CCObject* pSender);

private:

	FKCW_UIWidget_WidgetWindow*	m_pRootWindow;
};

