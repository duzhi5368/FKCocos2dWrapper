//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionRotoZoom.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ��ת�����ŵĳ����л�Ч��������Ч����
class  FKCW_SceneExMgr_SceneExTransitionRotoZoom : public FKCW_SceneExMgr_SceneExTransition
{
public:
    FKCW_SceneExMgr_SceneExTransitionRotoZoom();
    virtual ~FKCW_SceneExMgr_SceneExTransitionRotoZoom();

    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionRotoZoom* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};