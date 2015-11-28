//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionCrossFade.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �ںϣ���Ϸ�ʽ�л�������ԭ�����𽥱䵭���³����𽥱��
class  FKCW_SceneExMgr_SceneExTransitionCrossFade : public FKCW_SceneExMgr_SceneExTransition
{
public :
    FKCW_SceneExMgr_SceneExTransitionCrossFade();
    virtual ~FKCW_SceneExMgr_SceneExTransitionCrossFade();

    virtual void draw();
    virtual void onEnter();
    virtual void onExit();

public:
    static FKCW_SceneExMgr_SceneExTransitionCrossFade* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
