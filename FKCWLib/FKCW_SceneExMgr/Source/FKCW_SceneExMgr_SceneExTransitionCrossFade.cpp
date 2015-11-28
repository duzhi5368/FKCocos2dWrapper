//-------------------------------------------------------------------------
#include "../Include/FKCW_SceneExMgr_SceneExTransitionCrossFade.h"
//-------------------------------------------------------------------------
const unsigned int kSceneFade = 0xFADEFADE;
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionCrossFade::FKCW_SceneExMgr_SceneExTransitionCrossFade()
{
}
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionCrossFade::~FKCW_SceneExMgr_SceneExTransitionCrossFade()
{
}
//-------------------------------------------------------------------------
FKCW_SceneExMgr_SceneExTransitionCrossFade* FKCW_SceneExMgr_SceneExTransitionCrossFade::create(float t, FKCW_SceneExMgr_SceneEx* scene)
{
	FKCW_SceneExMgr_SceneExTransitionCrossFade* pScene = new FKCW_SceneExMgr_SceneExTransitionCrossFade();
	if(pScene && pScene->initWithDuration(t, scene))
	{
		pScene->autorelease();
		return pScene;
	}
	CC_SAFE_DELETE(pScene);
	return NULL;
}
//-------------------------------------------------------------------------
void FKCW_SceneExMgr_SceneExTransitionCrossFade:: draw()
{
	// ��Ⱦ�Ѿ���onEnterִ�еĶ���������
}
//-------------------------------------------------------------------------
void FKCW_SceneExMgr_SceneExTransitionCrossFade::onEnter()
{
	FKCW_SceneExMgr_SceneExTransition::onEnter();

	// ����һ������ɫ��Layer��������������Լ���renderTexture
	ccColor4B  color = {0,0,0,0};
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCLayerColor* layer = CCLayerColor::create(color);

	// Ϊ���볡������һ����Ⱦ����
	CCRenderTexture* inTexture = CCRenderTexture::create((int)size.width, (int)size.height);

	if (NULL == inTexture)
	{
		return;
	}

	inTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
	inTexture->setPosition( ccp(size.width/2, size.height/2) );
	inTexture->setAnchorPoint( ccp(0.5f,0.5f) );

	// ��Ⱦ�½��ȳ�����textureBuffer��
	inTexture->begin();
	m_pInScene->visit();
	inTexture->end();

	// Ϊ������ʧ���ϳ�������һ����Ⱦ����
	CCRenderTexture* outTexture = CCRenderTexture::create((int)size.width, (int)size.height);
	outTexture->getSprite()->setAnchorPoint( ccp(0.5f,0.5f) );
	outTexture->setPosition( ccp(size.width/2, size.height/2) );
	outTexture->setAnchorPoint( ccp(0.5f,0.5f) );

	// ��Ⱦ�Ͻ��ȳ�����textureBuffer��
	outTexture->begin();
	m_pOutScene->visit();
	outTexture->end();

	// ������Ϻ���
	ccBlendFunc blend1 = {GL_ONE, GL_ONE};							// �³�����Ϊ�����㣬��ʹ��alpha
	ccBlendFunc blend2 = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};	// �ϳ�����ǰ��alpha

	// ���û�Ϻ���
	inTexture->getSprite()->setBlendFunc(blend1);
	outTexture->getSprite()->setBlendFunc(blend2);    

	// �����Ⱦ����Layer��
	layer->addChild(inTexture);
	layer->addChild(outTexture);

	// ��ʼ����Alphaֵ
	inTexture->getSprite()->setOpacity(255);
	outTexture->getSprite()->setOpacity(255);

	// ������϶���
	CCAction* layerAction = CCSequence::create
		(
		CCFadeTo::create(m_fDuration, 0),
		CCCallFunc::create(this, callfunc_selector(FKCW_SceneExMgr_SceneExTransition::hideOutShowIn)),
		CCCallFunc::create(this, callfunc_selector(FKCW_SceneExMgr_SceneExTransition::finish)),
		NULL
		);


	// ִ�л�϶���
	outTexture->getSprite()->runAction( layerAction );

	// ��Ӵ�����renderTexture��Layer����ǰ������
	addChild(layer, 2, kSceneFade);
}
//-------------------------------------------------------------------------
void FKCW_SceneExMgr_SceneExTransitionCrossFade::onExit()
{
	// �Ƴ��Լ���Layer
	this->removeChildByTag(kSceneFade, false);
	FKCW_SceneExMgr_SceneExTransition::onExit();
}
//-------------------------------------------------------------------------