//*************************************************************************
//	��������:	2014-12-18
//	�ļ�����:	Test_RenderEx_ScrollingBackgroundNode.h
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
class CTest_RenderEx_ScrollingBackgroundNodeLayer : public CCLayer
{
public:
	bool init()
	{
		m_nCount = 0;

		CCSprite* pBackgroud1 = CCSprite::create(s_szBrickPath);
		CCSprite* pBackgroud2 = CCSprite::create(s_szBrickPath);
		m_pBackground = ScrollingBackground::create(SD_RIGHT_TO_LEFT);
		m_pBackground->addBackgroundSprite(pBackgroud1);
		m_pBackground->addBackgroundSprite(pBackgroud2);
		m_pBackground->setBgChangeEventListener(this, bgSpriteChangeEvent(CTest_RenderEx_ScrollingBackgroundNodeLayer::onBgSpriteChange));
		m_pBackground->setBgMoveEventListener(this, bgSpriteMoveEvent(CTest_RenderEx_ScrollingBackgroundNodeLayer::onBgMove));
		m_pBackground->beginContinuousScroll(500);
		this->addChild(m_pBackground);


		m_pInfoLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�����Ļ��̬��ӱ���").c_str(), "", 26);
		m_pInfoLabel->setPosition(SCREEN_CENTER_POS + ccp(0, -200));
		this->addChild(m_pInfoLabel);

		this->setTouchEnabled(true);
		this->setTouchMode(ccTouchesMode::kCCTouchesOneByOne);

		return true;
	}
public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
	{
		CCSprite* pAddedBG = CCSprite::create(s_szWoodPath);

		char m[5];
		sprintf(m, "%d", m_nCount);
		CCLabelTTF* label = CCLabelTTF::create(FKCW_Base_StringConvert::a2u(m).c_str(), "", 52);
		label->setPosition(pAddedBG->getContentSize()/2);
		pAddedBG->addChild(label);

		if(!m_pBackground->addBackgroundSprite(pAddedBG))
		{
			m_pInfoLabel->setString(FKCW_Base_StringConvert::a2u("��ӱ���ʧ��,��Ϊ��ǰ��ʾ�ı���Ϊ����β").c_str());
		}
		else
		{
			m_pInfoLabel->setString(FKCW_Base_StringConvert::a2u("��ӱ����ɹ�").c_str());
			m_nCount++;
		}

		return true;
	}

	void onBgSpriteChange (CCSprite* current,CCSprite* follow,CCSprite* leave)
	{
		m_pInfoLabel->setString(FKCW_Base_StringConvert::a2u("�����Ļ��̬��ӱ���").c_str());
	}

	void onBgMove (CCSprite* current,CCSprite* follow)
	{
		//m_label->setString(FKCW_Base_StringConvert::a2u("onBgMove�¼�����").c_str());
	}
public:
	CREATE_FUNC( CTest_RenderEx_ScrollingBackgroundNodeLayer );
protected:
	ScrollingBackground*	m_pBackground;
	CCLabelTTF*				m_pInfoLabel;
	int						m_nCount;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, ScrollingBackgroundNode, ���޾������Ľڵ�)
//-------------------------------------------------------------------------