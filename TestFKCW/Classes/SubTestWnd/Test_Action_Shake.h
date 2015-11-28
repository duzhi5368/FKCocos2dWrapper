//*************************************************************************
//	��������:	2014-12-12
//	�ļ�����:	Test_Action_Shake.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	���˶�
//  ���Խ��: ����ִ���𶯶�������ı�Node������λ��
//*************************************************************************
#pragma once
//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Action_ShakeLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_nTimes = 0;

		m_pSprite = CCSprite::create(s_szCocosLogoPath);
		m_pSprite->setPosition(SCREEN_CENTER_POS);
		this->addChild(m_pSprite);

		CCLabelTTF* lable = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҿ�ʼִ���𶯶���").c_str(), "Arial", 26 );
		lable->setColor(ccc3(230,155,3));

		CCMenuItemLabel* itemLable = CCMenuItemLabel::create(lable, this, menu_selector(CTest_Action_ShakeLayer::menuCallFunc));
		CCMenu* menu = CCMenu::create(itemLable, NULL);
		menu->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		this->addChild(menu);

		CCScale9Sprite* pEditBoxBG1 = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pDurationEdit = CCEditBox::create(CCSizeMake(200, 50), pEditBoxBG1 );
		m_pDurationEdit->setPosition( SCREEN_CENTER_POS + ccp(-150, -100));
		m_pDurationEdit->setFontSize( 18 );
		m_pDurationEdit->setText(FKCW_Base_StringConvert::a2u("����ʱ��(��)").c_str());
		addChild(m_pDurationEdit);

		CCScale9Sprite* pEditBoxBG2 = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pRadiusEdit = CCEditBox::create(CCSizeMake(200, 50), pEditBoxBG2 );
		m_pRadiusEdit->setPosition( SCREEN_CENTER_POS + ccp(150, -100));
		m_pRadiusEdit->setFontSize( 18 );
		m_pRadiusEdit->setText(FKCW_Base_StringConvert::a2u("����뾶(����)").c_str());
		addChild(m_pRadiusEdit);

		return true;
	}
public:
	void menuCallFunc(CCObject* pSender)
	{
		string strDuration = m_pDurationEdit->getText();
		string strRadius = m_pRadiusEdit->getText();
		float fDuration = static_cast<float>(FKCW_Base_Utils::AtoI(strDuration.c_str()));
		float fRadius = static_cast<float>(FKCW_Base_Utils::AtoI(strRadius.c_str()));

		fDuration = fDuration == 0 ? 1.0f : fDuration;
		fRadius = fRadius == 0 ? 5.0f : fRadius;

		FKCW_SceneExMgr_SceneEx* p = FKCW_SceneExMgr_SceneExMgr::sharedManager()->getRunningScene();

		switch ( m_nTimes % 2 )
		{
		case 0:
			p->runAction(FKCW_Action_Shake::Create(fDuration,fRadius));
			break;
		case 1:
			//��һ��ͬ��Բδ�ཻ�Ĳ��������
			m_pSprite->runAction(FKCW_Action_Shake::Create(fDuration,fRadius));
			break;
		default:
			break;
		}
		m_nTimes++;
	}
public:
	CREATE_FUNC( CTest_Action_ShakeLayer );
private:
	CCSprite*	m_pSprite;
	CCEditBox*	m_pDurationEdit;
	CCEditBox*	m_pRadiusEdit;
	int			m_nTimes;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, Shake, �𶯶���|��2D�����г������𶯱�����ʽ)
//-------------------------------------------------------------------------