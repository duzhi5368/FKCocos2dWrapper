//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionJumpZoom.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ��Ծ���ų����л�����
class  FKCW_SceneExMgr_SceneExTransitionJumpZoom : public FKCW_SceneExMgr_SceneExTransition
{
public:
    FKCW_SceneExMgr_SceneExTransitionJumpZoom();
    virtual ~FKCW_SceneExMgr_SceneExTransitionJumpZoom();

    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionJumpZoom* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};