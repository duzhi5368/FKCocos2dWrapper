//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionFlip.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
#include "FKCW_SceneExMgr_SceneExTransitionOriented.h"
//-------------------------------------------------------------------------
// ��X����ת�л�����
class  FKCW_SceneExMgr_SceneExTransitionFlipX : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionFlipX();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFlipX();
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionFlipX* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionFlipX* create(float t, FKCW_SceneExMgr_SceneEx* s);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionFlipY : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionFlipY();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFlipY();
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionFlipY* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionFlipY* create(float t, FKCW_SceneExMgr_SceneEx* s);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionFlipAngular : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionFlipAngular();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFlipAngular();
    virtual void onEnter();
    
    static FKCW_SceneExMgr_SceneExTransitionFlipAngular* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionFlipAngular* create(float t, FKCW_SceneExMgr_SceneEx* s);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionZoomFlipX : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionZoomFlipX();
    virtual ~FKCW_SceneExMgr_SceneExTransitionZoomFlipX();
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionZoomFlipX* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionZoomFlipX* create(float t, FKCW_SceneExMgr_SceneEx* s);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionZoomFlipY : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionZoomFlipY();
    virtual ~FKCW_SceneExMgr_SceneExTransitionZoomFlipY();
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionZoomFlipY* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionZoomFlipY* create(float t, FKCW_SceneExMgr_SceneEx* s);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular : public FKCW_SceneExMgr_SceneExTransitionOriented
{
public:
    FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular();
    virtual ~FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular();
    virtual void onEnter();

    static FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular* create(float t, FKCW_SceneExMgr_SceneEx* s, tOrientation o);
    static FKCW_SceneExMgr_SceneExTransitionZoomFlipAngular* create(float t, FKCW_SceneExMgr_SceneEx* s);
};