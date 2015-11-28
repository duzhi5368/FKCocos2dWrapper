//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionTurnOffTiles.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ����������滻��ʽ�л���������ԭ�������³����л�Ϊ���С�������������ͼ���л�Ϊ�³�����
class  FKCW_SceneExMgr_SceneExTransitionTurnOffTiles : public FKCW_SceneExMgr_SceneExTransition ,public FKCW_SceneExMgr_SceneExTransitionEase
{
public :
    FKCW_SceneExMgr_SceneExTransitionTurnOffTiles();
    virtual ~FKCW_SceneExMgr_SceneExTransitionTurnOffTiles();

    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    static FKCW_SceneExMgr_SceneExTransitionTurnOffTiles* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
    virtual void sceneOrder();
};
