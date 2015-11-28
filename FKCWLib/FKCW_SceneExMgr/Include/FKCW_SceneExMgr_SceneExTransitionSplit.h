//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionSplit.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ����/����ԭ������Ϊ�����������������˲��滻Ϊ�³���
class  FKCW_SceneExMgr_SceneExTransitionSplitCols : public FKCW_SceneExMgr_SceneExTransition , public FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    FKCW_SceneExMgr_SceneExTransitionSplitCols();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSplitCols();

    virtual CCActionInterval* action(void);
    virtual void onEnter();
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:

    static FKCW_SceneExMgr_SceneExTransitionSplitCols* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------
class  FKCW_SceneExMgr_SceneExTransitionSplitRows : public FKCW_SceneExMgr_SceneExTransitionSplitCols
{
public:
    FKCW_SceneExMgr_SceneExTransitionSplitRows();
    virtual ~FKCW_SceneExMgr_SceneExTransitionSplitRows();

    virtual CCActionInterval* action(void);
public:

    static FKCW_SceneExMgr_SceneExTransitionSplitRows* create(float t, FKCW_SceneExMgr_SceneEx* scene);
};
//-------------------------------------------------------------------------