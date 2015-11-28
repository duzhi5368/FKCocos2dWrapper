//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionOriented.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �����򻬶��л�����
class  FKCW_SceneExMgr_SceneExTransitionOriented : public FKCW_SceneExMgr_SceneExTransition
{
protected:
    tOrientation m_eOrientation;				// �л������ķ���

public:
    FKCW_SceneExMgr_SceneExTransitionOriented();
    virtual ~FKCW_SceneExMgr_SceneExTransitionOriented();

    // ����һ�������л��Ķ�������
	// ������t �����г��� scene ����Ҫ�л�����Ŀ�곡���� orientation �л��ķ���
    static FKCW_SceneExMgr_SceneExTransitionOriented * create(float t,FKCW_SceneExMgr_SceneEx* scene,
		tOrientation orientation);

    virtual bool initWithDuration(float t,FKCW_SceneExMgr_SceneEx* scene,tOrientation orientation);
};