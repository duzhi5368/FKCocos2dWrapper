//*************************************************************************
//	��������:	2014-12-24
//	�ļ�����:	MenuScene.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../../FKCWLib/FKCocos2dxWrapper.h"
#include "ListControllerLayer.h"
//-------------------------------------------------------------------------
class CMenuScene : public FKCW_SceneExMgr_SceneEx
{
public:
	CREATE_SCENE_FUNC(CMenuScene);
public:
	CMenuScene();
	virtual ~CMenuScene();

	virtual void onLoadScene();
private:
	CListControllerLayer*		m_pLayer;
};