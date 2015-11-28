//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransition.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneEx.h"
#include "FKCW_SceneExMgr.h"
//-------------------------------------------------------------------------
// ���麯�����̳б�������ζ�ų�����ִ��һ�������ٶ�����
class FKCW_SceneExMgr_SceneExTransitionEase
{
public:
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action) = 0;
};
//-------------------------------------------------------------------------
// ���ɳ�������
class FKCW_SceneExMgr_SceneExTransition : public FKCW_SceneExMgr_SceneEx
{

protected:
	FKCW_SceneExMgr_SceneEx*	m_pInScene;					// ��������ʾ�ĳ������³�����
    FKCW_SceneExMgr_SceneEx*	m_pOutScene;				// ����������ĳ������ϳ�����
	float						m_fDuration;				// �л�����Ч���г�
	bool						m_bIsInSceneOnTop;			// �Ƿ���г�����Ⱦ�����Ա�֤�³�����������
	bool						m_bIsSendCleanupToScene;	// �Ƿ����л����֮����վɳ���

public:
    FKCW_SceneExMgr_SceneExTransition();
    virtual ~FKCW_SceneExMgr_SceneExTransition();
    virtual void draw();
    virtual void onEnter();
    virtual void onExit();
    virtual void cleanup();

	virtual FKCW_SceneExMgr_SceneEx* getInScene();

	// ����һ���������ɳ���
    static FKCW_SceneExMgr_SceneExTransition* create(float t, FKCW_SceneExMgr_SceneEx *scene);
	// ��ʼ��һ���������ɳ���
    virtual bool initWithDuration(float t,FKCW_SceneExMgr_SceneEx* scene);
	// ���ɽ��������
    void finish(void);
	// ���ֹ��ɳ���������Ҫ���������������ϳ���
    void hideOutShowIn(void);

protected:
	// ���öԳ�����������
    virtual void sceneOrder();
private:
	// ˽�к����������ڳ����л�������ɺ������³���Ϊ��ǰ��Ϸ������
    void setNewScene(float dt);
};
//-------------------------------------------------------------------------