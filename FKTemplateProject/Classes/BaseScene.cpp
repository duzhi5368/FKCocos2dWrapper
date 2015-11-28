//*************************************************************************
//	��������:	2015-1-6
//	�ļ�����:	BaseScene.cpp
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseScene.h"
#include "Resource.h"
#include "cocos2d.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
CCScene* BaseLayer::scene()
{
    CCScene *scene = CCScene::create();
    BaseLayer *layer = BaseLayer::create();
    scene->addChild(layer);
    
    CCLabelTTF* pInfo = CCLabelTTF::create("hello FKCW", "Arial", 26 );
		pInfo->setColor( ccc3(209,73,78) );
		pInfo->setPosition( ccp(600,300));
		layer->addChild( pInfo);
		
    return scene;
}
//-------------------------------------------------------------------------
BaseLayer::BaseLayer()
{

}
//-------------------------------------------------------------------------
bool BaseLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    	
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	// ��Ӽ��̷���
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook( BaseLayer::KeyboardHook ); 
#endif
	
	// add your code here
    
    return true;
}

//-------------------------------------------------------------------------
// WINDOWS ��Ϣ
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	void BaseLayer::KeyboardHook( UINT message,WPARAM wParam, LPARAM lParam )
{

}
#endif
//-------------------------------------------------------------------------