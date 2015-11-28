//*************************************************************************
//	��������:	2014-12-11
//	�ļ�����:	Test_UI_DynamicNumLabel.h
//  �� �� ��:   Wilhan Tian	
//	��Ȩ����:	MIT
//	˵    ��:	��̬���ֱ�ǩ����	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UI_DynamicNumLabelLayer : public CCLayer
{
public:
	virtual bool init()
	{
		//��ʾ��ť
		CCLabelTTF* pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҽ���̬�ı����ֱ�ǩ").c_str(), "Arial", 36 );
		pLabel->setColor( ccc3(230,155,3) );

		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(pLabel, this, menu_selector(CTest_UI_DynamicNumLabelLayer::menuCallBack));
		CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
		pMenu->setPosition( SCREEN_CENTER_POS + ccp( 0, -200 ));
		addChild(pMenu, 1);

		m_pLabel1 = FKCW_UI_DynamicNumLabel::create("test1", "Atlas", 35.0f);
		m_pLabel1->setPosition(CCPoint(SCREEN_CENTER_POS_X, 450));
		this->addChild(m_pLabel1);
		
		CCLabelTTF* lable1 = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("Ĭ�ϲ������").c_str(), "Arial", 26 );
		lable1->setColor( ccBLACK );
		lable1->setPosition(CCPoint(SCREEN_CENTER_POS_X + 150, 450));
		this->addChild(lable1);

		m_pLabel2 = FKCW_UI_DynamicNumLabel::create("-2.0", "Atlas", 35.0f, CCSize(500.0f, 100.0f), CCTextAlignment::kCCTextAlignmentLeft);
		m_pLabel2->setPosition(CCPoint(SCREEN_CENTER_POS_X, 350));
		this->addChild(m_pLabel2);

		CCLabelTTF* lable2 = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�������").c_str(), "Arial", 26 );
		lable2->setColor( ccBLACK );
		lable2->setPosition(CCPoint(SCREEN_CENTER_POS_X + 150, 350));
		this->addChild(lable2);

		m_pLabel3 = FKCW_UI_DynamicNumLabel::create("1000", "Atlas", 35.0f, CCSize(30.0f, 100), CCTextAlignment::kCCTextAlignmentRight, CCVerticalTextAlignment::kCCVerticalTextAlignmentBottom);
		m_pLabel3->setPosition(CCPoint(SCREEN_CENTER_POS_X, 250));
		this->addChild(m_pLabel3);

		CCLabelTTF* lable3 = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���� �Ҷ��� �϶���").c_str(), "Arial", 26 );
		lable3->setColor( ccBLACK );
		lable3->setPosition(CCPoint(SCREEN_CENTER_POS_X + 150, 250));
		this->addChild(lable3);

		return true;
	}
public:
	void menuCallBack(CCObject* pSender) 
	{
		//�޸Ķ�̬��ֵ
		m_pLabel1->SetDynamicValue((m_pLabel1->GetDynamicValue()+1) * (m_pLabel1->GetDynamicValue()+1));
		m_pLabel2->SetDynamicValue( (int)FKCW_Base_Utils::RandomInRange( 0, 100000 ));
		m_pLabel3->SetDynamicValue((m_pLabel3->GetDynamicValue()+1) * (m_pLabel3->GetDynamicValue()+1));
	}
public:
	CREATE_FUNC( CTest_UI_DynamicNumLabelLayer );
private:
	FKCW_UI_DynamicNumLabel* m_pLabel1;
	FKCW_UI_DynamicNumLabel* m_pLabel2;
	FKCW_UI_DynamicNumLabel* m_pLabel3;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, DynamicNumLabel, ��̬���ֱ�ǩʵ����ע�⣬��ʱֻ֧����������֧����ʾ���и��ʾ���뷽ʽ��)
//-------------------------------------------------------------------------