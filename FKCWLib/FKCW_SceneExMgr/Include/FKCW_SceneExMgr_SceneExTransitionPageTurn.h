//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionPageTurn.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ǰ/�� ��ҳ��ʽ�л�����
class FKCW_SceneExMgr_SceneExTransitionPageTurn : public FKCW_SceneExMgr_SceneExTransition
{
protected:
    bool    m_bBack;
    
public:
    FKCW_SceneExMgr_SceneExTransitionPageTurn();
    virtual ~FKCW_SceneExMgr_SceneExTransitionPageTurn();
	static FKCW_SceneExMgr_SceneExTransitionPageTurn* create(float t,FKCW_SceneExMgr_SceneEx* scene,bool backwards);
	virtual bool initWithDuration(float t,FKCW_SceneExMgr_SceneEx* scene,bool backwards);

    CCActionInterval* actionWithSize(const CCSize& vector);
    virtual void onEnter();

protected:
    virtual void sceneOrder();
}; 