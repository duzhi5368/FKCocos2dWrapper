//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionShrinkGrow.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �����л�����Ч��
class  FKCW_SceneExMgr_SceneExTransitionShrinkGrow : public FKCW_SceneExMgr_SceneExTransition , public FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    FKCW_SceneExMgr_SceneExTransitionShrinkGrow();
    virtual ~FKCW_SceneExMgr_SceneExTransitionShrinkGrow();

    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static FKCW_SceneExMgr_SceneExTransitionShrinkGrow* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
