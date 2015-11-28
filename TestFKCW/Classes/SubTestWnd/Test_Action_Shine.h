//*************************************************************************
//	��������:	2014-12-12
//	�ļ�����:	Test_Action_Shine.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	��̬����Ч��
//  ���Խ��: 
//*************************************************************************
#pragma once
//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Action_ShineLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_nIndex = 0;

		m_pSprite = CCSprite::create(s_szHalfPhotoPath);
		m_pSprite->setPosition(SCREEN_CENTER_POS);
		this->addChild(m_pSprite);

		CCLabelTTF* lable = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҶԾ���ִ�ж�̬���߶���").c_str(), "Arial", 26 );
		lable->setColor(ccc3(230,155,3));

		CCMenuItemLabel* itemLable = CCMenuItemLabel::create(lable, this, menu_selector(CTest_Action_ShineLayer::menuCallFunc));
		CCMenu* menu = CCMenu::create(itemLable, NULL);
		menu->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		this->addChild(menu);

		return true;
	}
public:
	void menuCallFunc(CCObject* pSender)
	{
		ccColor4B c1 = {0,   0, 255, 255};
		ccColor4B c2 = {0, 255,   0, 255};
		ccColor4B c3 = {255, 0,   0, 255};
		switch ( m_nIndex % 2 )
		{
		case 0:
			m_pSprite->runAction(FKCW_Action_Shine::Create(1.5f, c1, c2, c3, vertex3(0.2f, 0.5f, 0.3f)));
			break;
		case 1:
			m_pSprite->runAction(FKCW_Action_Shine::Create(0.5f, cc4TRANSPARENT,
				ccc4(255, 255, 255, 180), cc4TRANSPARENT, vertex3(0.3f, 0.5f, 0.7f)));
			break;
		default:
			break;
		}
		m_nIndex++;
	}
public:
	CREATE_FUNC( CTest_Action_ShineLayer );
private:
	CCSprite*	m_pSprite;
	int			m_nIndex;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, Shine, ��Ч��Ϊ���������ƶ�һ�Σ�����Ϊ�ݶ�״�����ɱ��������������ɫ)
//-------------------------------------------------------------------------