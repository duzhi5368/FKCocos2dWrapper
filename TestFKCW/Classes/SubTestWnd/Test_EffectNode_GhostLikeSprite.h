//*************************************************************************
//	��������:	2014-12-24
//	�ļ�����:	Test_EffectNode_GhostLikeSprite.h
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_EffectNode_GhostLikeSpriteLayer : public CCLayer
{
public:
	bool init()
	{
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		CCSprite*backGround=CCSprite::create();
		backGround->initWithFile( s_szBackground1Path );
		backGround->setScale(2.0f);
		backGround->setPosition(ccp(winSize.width/2, winSize.height/2));
		addChild(backGround);

		// ֡����
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( s_szFishFramesFile );
		CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile( s_szFishAniFile );
		CCAnimation*animation=CCAnimationCache::sharedAnimationCache()->animationByName("fish_ani");

		// ��꾫��
		m_ghostSprite=new FKCW_EffectNode_GhostLikeSprite();
		m_ghostSprite->autorelease();
		m_ghostSprite->init(((CCAnimationFrame*)animation->getFrames()->objectAtIndex(0))->getSpriteFrame());
		m_ghostSprite->setPosition(ccp(winSize.width/2, winSize.height/3*2));
		this->addChild(m_ghostSprite,1);
		m_ghostSprite->getRefSprite()->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		// ��ͨ�������Ա�
		CCSprite*sp=CCSprite::create();
		sp->initWithSpriteFrame(((CCAnimationFrame*)animation->getFrames()->objectAtIndex(0))->getSpriteFrame());
		this->addChild(sp);
		sp->setPosition(ccp(winSize.width/2, winSize.height/3));
		sp->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

		return true;
	}
protected:
	FKCW_EffectNode_GhostLikeSprite* m_ghostSprite;
public:
	CREATE_FUNC( CTest_EffectNode_GhostLikeSpriteLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(EffectNode, GhostLikeSprite, ���龫��)
//-------------------------------------------------------------------------