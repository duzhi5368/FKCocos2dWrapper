//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionFadeColor.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// ����ɫЧ�����뵭����ԭ�����𽥼�����ɫ��ָ��ɫ������ָ��ɫ����Ϊ�³���, Ĭ�Ϻ�ɫ��
class  FKCW_SceneExMgr_SceneExTransitionFadeColor : public FKCW_SceneExMgr_SceneExTransition
{
protected:
    ccColor4B    m_tColor;

public:
    FKCW_SceneExMgr_SceneExTransitionFadeColor();
    virtual ~FKCW_SceneExMgr_SceneExTransitionFadeColor();
    
    static FKCW_SceneExMgr_SceneExTransitionFadeColor* create(float duration,FKCW_SceneExMgr_SceneEx* scene, const ccColor3B& color);
    static FKCW_SceneExMgr_SceneExTransitionFadeColor* create(float duration,FKCW_SceneExMgr_SceneEx* scene);

    virtual bool initWithDuration(float t, FKCW_SceneExMgr_SceneEx* scene ,const ccColor3B& color);
    virtual bool initWithDuration(float t, FKCW_SceneExMgr_SceneEx* scene);
    virtual void onEnter();
    virtual void onExit();
};
//-------------------------------------------------------------------------