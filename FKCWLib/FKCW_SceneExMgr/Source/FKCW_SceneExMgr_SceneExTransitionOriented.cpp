//-------------------------------------------------------------------------
#include "../Include/FKCW_SceneExMgr_SceneExTransitionOriented.h"
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionOriented::FKCW_SceneExMgr_SceneExTransitionOriented()
{

}
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionOriented::~FKCW_SceneExMgr_SceneExTransitionOriented()
{

}
//-------------------------------------------------------------------------
// ����һ�������л��Ķ�������
// ������t �����г��� scene ����Ҫ�л�����Ŀ�곡���� orientation �л��ķ���
FKCW_SceneExMgr_SceneExTransitionOriented* FKCW_SceneExMgr_SceneExTransitionOriented::create(float t,FKCW_SceneExMgr_SceneEx* scene,
														  tOrientation orientation)
{
	FKCW_SceneExMgr_SceneExTransitionOriented * pScene = new FKCW_SceneExMgr_SceneExTransitionOriented();
	pScene->initWithDuration(t,scene,orientation);
	pScene->autorelease();
	return pScene;
}
//-------------------------------------------------------------------------
bool FKCW_SceneExMgr_SceneExTransitionOriented::initWithDuration(
	float t,FKCW_SceneExMgr_SceneEx* scene,tOrientation orientation)
{
	if ( FKCW_SceneExMgr_SceneExTransition::initWithDuration(t, scene) )
	{
		m_eOrientation = orientation;
	}
	return true;
}
//-------------------------------------------------------------------------