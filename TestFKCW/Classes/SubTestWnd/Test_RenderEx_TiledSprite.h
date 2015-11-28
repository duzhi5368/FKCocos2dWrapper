	//*************************************************************************
//	��������:	2014-12-18
//	�ļ�����:	Test_RenderEx_TiledSprite.h
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
class CTest_RenderEx_TiledSpriteLayer : public CCLayer
{
public:
	bool init()
	{
		m_bIsFullScreen = false;

		//�������
		m_pSprite = FKCW_RenderEx_TiledSprite::create(s_szWoodPath);
		m_pSprite->setPosition(SCREEN_CENTER_POS);
		this->addChild(m_pSprite);

		m_pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�����Ļ���Խ�������䵽��Ļ").c_str(), "", 26);
		m_pLabel->setColor( ccc3(230,155,3) );
		m_pLabel->setPosition(SCREEN_CENTER_POS + ccp(0, -200));
		this->addChild(m_pLabel);

		this->setTouchEnabled(true);
		this->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);

		return true;
	}
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
	{
		if (m_bIsFullScreen)
		{
			m_pSprite->setContentSize(CCSizeMake(128,128));
			m_pLabel->setString(FKCW_Base_StringConvert::a2u("�����Ļ���Խ�������䵽��Ļ").c_str());
		}
		else
		{
			m_pSprite->setContentSize(SCREEN_CENTER_POS*2);
			m_pLabel->setString(FKCW_Base_StringConvert::a2u("�����Ļ���Խ����鸴ԭ��ԭʼ��С").c_str());
		}

		m_bIsFullScreen = !m_bIsFullScreen;
		return true;
	}
public:
	CREATE_FUNC( CTest_RenderEx_TiledSpriteLayer );
protected:
	FKCW_RenderEx_TiledSprite*	m_pSprite;
	CCLabelTTF*					m_pLabel;
	bool						m_bIsFullScreen;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, TiledSprite, ��侫��)
//-------------------------------------------------------------------------