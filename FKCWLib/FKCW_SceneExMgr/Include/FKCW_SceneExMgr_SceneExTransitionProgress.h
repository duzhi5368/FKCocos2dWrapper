//*************************************************************************
//	��������:	2014-11-12
//	�ļ�����:	FKCW_SceneExMgr_SceneExTransitionProgress.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "FKCW_SceneExMgr_SceneExTransition.h"
//-------------------------------------------------------------------------
// �Խ�������ʽ���г����л���˳/��ʱ���ӱ���ʽ����������ֱ/�����������������������ɢ��������������ɢ��
class FKCW_SceneExMgr_SceneExTransitionProgress : public FKCW_SceneExMgr_SceneExTransition
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgress* create(float t, FKCW_SceneExMgr_SceneEx* scene);

    FKCW_SceneExMgr_SceneExTransitionProgress();
    virtual void onEnter();
    virtual void onExit();
protected:
    virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
    virtual void setupTransition();
    virtual void sceneOrder();
    float m_fTo;
    float m_fFrom;
    FKCW_SceneExMgr_SceneEx* m_pSceneToBeModified;
};
//-------------------------------------------------------------------------
// ��ʱ��
class FKCW_SceneExMgr_SceneExTransitionProgressRadialCCW : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressRadialCCW* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
};
//-------------------------------------------------------------------------
// ˳ʱ��
class FKCW_SceneExMgr_SceneExTransitionProgressRadialCW : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressRadialCW* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
};
//-------------------------------------------------------------------------
// ����
class FKCW_SceneExMgr_SceneExTransitionProgressHorizontal : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressHorizontal* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);

};
//-------------------------------------------------------------------------
// ����
class FKCW_SceneExMgr_SceneExTransitionProgressVertical : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressVertical* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
};
//-------------------------------------------------------------------------
// ������������չ
class FKCW_SceneExMgr_SceneExTransitionProgressInOut : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressInOut* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
	virtual void sceneOrder();
	virtual void setupTransition();
};
//-------------------------------------------------------------------------
// ��������������
class FKCW_SceneExMgr_SceneExTransitionProgressOutIn : public FKCW_SceneExMgr_SceneExTransitionProgress
{
public:
	static FKCW_SceneExMgr_SceneExTransitionProgressOutIn* create(float t, FKCW_SceneExMgr_SceneEx* scene);
protected:
	virtual CCProgressTimer* progressTimerNodeWithRenderTexture(CCRenderTexture* texture);
};
//-------------------------------------------------------------------------