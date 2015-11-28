//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionMoveIn.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �����л�Ч�����³������������ƶ�����ԭ������ԭ����������
class  FKCW_SceneExMgr_SceneExTransitionMoveInL : public FKCW_SceneExMgr_SceneExTransition, public FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    FKCW_SceneExMgr_SceneExTransitionMoveInL();
    virtual ~FKCW_SceneExMgr_SceneExTransitionMoveInL();

    virtual void initScenes(void);
    virtual CCActionInterval* action(void);
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionMoveInL* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionMoveInR : public FKCW_SceneExMgr_SceneExTransitionMoveInL
{
public:
    FKCW_SceneExMgr_SceneExTransitionMoveInR();
    virtual ~FKCW_SceneExMgr_SceneExTransitionMoveInR();
    virtual void initScenes();

    static FKCW_SceneExMgr_SceneExTransitionMoveInR* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionMoveInT : public FKCW_SceneExMgr_SceneExTransitionMoveInL 
{
public:
    FKCW_SceneExMgr_SceneExTransitionMoveInT();
    virtual ~FKCW_SceneExMgr_SceneExTransitionMoveInT();
    virtual void initScenes();

    static FKCW_SceneExMgr_SceneExTransitionMoveInT* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionMoveInB : public FKCW_SceneExMgr_SceneExTransitionMoveInL
{
public:
    FKCW_SceneExMgr_SceneExTransitionMoveInB();
    virtual ~FKCW_SceneExMgr_SceneExTransitionMoveInB();
    virtual void initScenes();

    static FKCW_SceneExMgr_SceneExTransitionMoveInB* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
