//*************************************************************************
//	��������:	2015-1-9
//	�ļ�����:	Test_Action_Suck.h
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
class CTest_Action_SuckLayer : public CCLayer
{
public:
	virtual bool init()
	{
		CCSprite* pPlayer = CCSprite::create( s_szHalfPhotoPath );
		if( pPlayer )
		{
			pPlayer->setPosition( SCREEN_CENTER_POS );
			pPlayer->setScale( 0.8f );
			pPlayer->runAction( CCSequence::create(
				CCDelayTime::create( 0.5f ),
				FKCW_Action_Suck::create( CCSizeMake( 100, 100 ), 5.0f, 
				SCREEN_CENTER_POS + ccp( 0, 50) ),
				CCCallFuncN::create( this, callfuncN_selector(CTest_Action_SuckLayer::RemoveSprite )),
				NULL ));
		}

		this->addChild( pPlayer );

		return true;
	}
public:
	void RemoveSprite( CCNode* p )
	{
		if( p != NULL )
		{
			p->removeAllChildren();
			p->removeFromParentAndCleanup( true );
		}
	}
public:
	CREATE_FUNC( CTest_Action_SuckLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, Suck, �ڶ�����Ч��)
	//-------------------------------------------------------------------------