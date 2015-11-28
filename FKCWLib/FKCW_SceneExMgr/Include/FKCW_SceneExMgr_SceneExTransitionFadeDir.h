//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionFadeDir.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ������/����/��/�� ��ԳƷ����Է�������ʽ���滻
class  FKCW_SceneExMgr_SceneExTransitionFadeTR : public FKCW_SceneExMgr_SceneExTransition ,public FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    FKCW_SceneExMgr_SceneExTransitionFadeTR();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFadeTR();
    virtual CCActionInterval* actionWithSize(const CCSize& size);
    virtual void onEnter();
    virtual CCActionInterval* easeActionWithAction(CCActionInterval * action);

public:

    static FKCW_SceneExMgr_SceneExTransitionFadeTR* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
    virtual void sceneOrder();
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionFadeBL : public FKCW_SceneExMgr_SceneExTransitionFadeTR
{
public:
    FKCW_SceneExMgr_SceneExTransitionFadeBL();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFadeBL();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static FKCW_SceneExMgr_SceneExTransitionFadeBL* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionFadeUp : public FKCW_SceneExMgr_SceneExTransitionFadeTR
{
public:
    FKCW_SceneExMgr_SceneExTransitionFadeUp();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFadeUp();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static FKCW_SceneExMgr_SceneExTransitionFadeUp* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionFadeDown : public FKCW_SceneExMgr_SceneExTransitionFadeTR
{
public:
    FKCW_SceneExMgr_SceneExTransitionFadeDown();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFadeDown();
    virtual CCActionInterval* actionWithSize(const CCSize& size);

public:

    static FKCW_SceneExMgr_SceneExTransitionFadeDown* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------