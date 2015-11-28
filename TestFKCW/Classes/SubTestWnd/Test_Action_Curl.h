//*************************************************************************
//	��������:	2014-12-23
//	�ļ�����:	Test_Action_Curl.h
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
class CTest_Action_CurlLayer : public CCLayer
{
public:
	virtual bool init()
	{
		CCSprite* s = CCSprite::create( s_szCocosLogoPath );
		s->setPosition(SCREEN_CENTER_POS);
		addChild(s);

		s->runAction(CCRepeatForever::create(CCSequence::create(
			FKCW_Action_Curl::Create(5, SCREEN_CENTER_POS, SCREEN_CENTER_POS_Y, static_cast<float>(M_PI / 2)),
			FKCW_Action_Curl::Create(5, SCREEN_CENTER_POS, 0, static_cast<float>(M_PI / 2)),
			NULL)));
		return true;
	}
public:
	CREATE_FUNC( CTest_Action_CurlLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, Curl, ������ת����)
//-------------------------------------------------------------------------