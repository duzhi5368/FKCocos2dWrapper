	//*************************************************************************
//	��������:	2014-12-18
//	�ļ�����:	Test_RenderEx_LaserSprite.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	
//  ��    ע:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_RenderEx_LaserSpriteLayer : public CCLayer
{
public:
	bool init()
	{
		m_pLasel = FKCW_RenderEx_LaserSprite::Create(10, SCERRN_HEIGHT);
		m_pLasel->setAnchorPoint(ccp(0.5f, 0));
		m_pLasel->setPosition(ccp(SCREEN_CENTER_POS_X,0));
		addChild(m_pLasel);

		return true;
	}
public:
	CREATE_FUNC( CTest_RenderEx_LaserSpriteLayer );
public:
	FKCW_RenderEx_LaserSprite* m_pLasel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, LaserSprite, ����/���⾫��)
//-------------------------------------------------------------------------