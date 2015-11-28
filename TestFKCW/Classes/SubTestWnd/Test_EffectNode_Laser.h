//*************************************************************************
//	��������:	2014-12-24
//	�ļ�����:	Test_EffectNode_Laser.h
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
class CTest_EffectNode_LaserLayer : public CCLayer
{
public:
	bool init()
	{
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();

		setTouchEnabled( true );
		scheduleUpdate();

		m_laser=new FKCW_EffecrNode_Laser();
		m_laser->autorelease();
		m_laser->init();
		this->addChild(m_laser);
		m_laser->setStart(ccp(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y));
		m_laser->setEnd(ccp(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height));

		return true;
	}
public:
	FKCW_EffecrNode_Laser*	m_laser;
public:
	CREATE_FUNC( CTest_EffectNode_LaserLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(EffectNode, Laser, ��������)
//-------------------------------------------------------------------------