//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionSlideIn.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �ƶ��л�Ч�����³����������ҽ�ԭ�����Ƴ���Ļ��
class FKCW_SceneExMgr_SceneExTransitionSlideInL : public FKCW_SceneExMgr_SceneExTransition, public FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    FKCW_SceneExMgr_SceneExTransitionSlideInL();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSlideInL();

    virtual void initScenes(void);
    virtual CCActionInterval* action(void);
    virtual void onEnter();
    
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

    static FKCW_SceneExMgr_SceneExTransitionSlideInL* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
    virtual void sceneOrder();
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionSlideInR : public FKCW_SceneExMgr_SceneExTransitionSlideInL 
{
public:
    FKCW_SceneExMgr_SceneExTransitionSlideInR();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSlideInR();

    virtual void initScenes(void);
    virtual CCActionInterval* action(void);

    static FKCW_SceneExMgr_SceneExTransitionSlideInR* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
    virtual void sceneOrder();
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionSlideInB : public FKCW_SceneExMgr_SceneExTransitionSlideInL
{
public:
    FKCW_SceneExMgr_SceneExTransitionSlideInB();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSlideInB();

    virtual void initScenes(void);
    virtual CCActionInterval* action(void);

    static FKCW_SceneExMgr_SceneExTransitionSlideInB* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected: 
    virtual void sceneOrder();
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionSlideInT : public FKCW_SceneExMgr_SceneExTransitionSlideInL
{
public:
    FKCW_SceneExMgr_SceneExTransitionSlideInT();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSlideInT();

    virtual void initScenes(void);
    virtual CCActionInterval* action(void);

    static FKCW_SceneExMgr_SceneExTransitionSlideInT* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
    virtual void sceneOrder();
};
//-------------------------------------------------------------------------