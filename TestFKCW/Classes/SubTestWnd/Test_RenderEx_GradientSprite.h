//*************************************************************************
//	��������:	2014-12-18
//	�ļ�����:	Test_RenderEx_GradientSprite.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_RenderEx_GradientSpriteLayer : public CCLayer
{
public:
	bool init()
	{
		FKCW_RenderEx_GradientSprite* s = FKCW_RenderEx_GradientSprite::create(s_szHalfPhotoPath);
		s->setColor(ccc4(255, 0, 0, 255), ccc4(0, 255, 0, 255), ccp(0, 1));
		s->setPosition(SCREEN_CENTER_POS +ccp(-300,0));
		s->setScale(0.6f);
		addChild(s);

		s = FKCW_RenderEx_GradientSprite::create(s_szHalfPhotoPath);
		s->setColor(ccc4(255, 0, 0, 255), ccc4(0, 255, 0, 0), ccp(0, 1));
		s->setPosition(SCREEN_CENTER_POS);
		s->setScale(0.6f);
		addChild(s);

		s = FKCW_RenderEx_GradientSprite::create(s_szHalfPhotoPath);
		s->setColor(ccc4(255, 0, 255, 255), ccc4(0, 255, 0, 255), ccp(1, 1));
		s->setPosition(SCREEN_CENTER_POS+ccp(300,0));
		s->setScale(0.6f);
		addChild(s);

		return true;
	}
public:
	CREATE_FUNC( CTest_RenderEx_GradientSpriteLayer );
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, GradientSprite, һ���ὥ��Ч���ľ���)
//-------------------------------------------------------------------------