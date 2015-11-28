//-------------------------------------------------------------------------
#include "../Include/FKCW_SceneExMgr_SceneExTransitionRotoZoom.h"
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionRotoZoom::FKCW_SceneExMgr_SceneExTransitionRotoZoom()
{

}
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionRotoZoom::~FKCW_SceneExMgr_SceneExTransitionRotoZoom()
{

}
//-------------------------------------------------------------------------
void FKCW_SceneExMgr_SceneExTransitionRotoZoom::onEnter()
{
	FKCW_SceneExMgr_SceneExTransition::onEnter();

	m_pInScene->setScale(0.001f);
	m_pOutScene->setScale(1.0f);

	m_pInScene->setAnchorPoint(ccp(0.5f, 0.5f));
	m_pOutScene->setAnchorPoint(ccp(0.5f, 0.5f));

	CCActionInterval *rotozoom = (CCActionInterval*)(CCSequence::create
	(
		CCSpawn::create(
			CCScaleBy::create(m_fDuration/2, 0.001f),
			CCRotateBy::create(m_fDuration/2, 360 * 2),
			NULL),
		CCDelayTime::create(m_fDuration/2),
		NULL
	));

	m_pOutScene->runAction(rotozoom);
	m_pInScene->runAction
	(
		CCSequence::create
		(
			rotozoom->reverse(),
			CCCallFunc::create(this, callfunc_selector(FKCW_SceneExMgr_SceneExTransition::finish)),
			NULL
		)
	);
}
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionRotoZoom* FKCW_SceneExMgr_SceneExTransitionRotoZoom::create(float t, FKCW_SceneExMgr_SceneEx* scene)
{
	FKCW_SceneExMgr_SceneExTransitionRotoZoom* pScene = new FKCW_SceneExMgr_SceneExTransitionRotoZoom();                                
	if(pScene && pScene->initWithDuration(t, scene))            
	{                                                           
		pScene->autorelease();                                  
		return pScene;                                          
	}                                                           
	CC_SAFE_DELETE(pScene);                                     
	return NULL;  
}
//-------------------------------------------------------------------------