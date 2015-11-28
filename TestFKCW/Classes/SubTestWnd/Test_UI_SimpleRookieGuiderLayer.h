//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_SimpleRookieGuiderLayer.h
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
class CTest_UI_SimpleRookieGuiderLayer : public CCLayer
{
public:
	virtual bool init()
	{
		// ���������ֳ�ʼ������
		CCLabelTTF* pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���ҽ���ʼ��������").c_str(), "Arial", 36 );
		pLabel->setColor( ccc3(230,155,3) );

		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(pLabel, this, menu_selector(CTest_UI_SimpleRookieGuiderLayer::ShowGuiderCallback));
		CCMenu* pMenu = CCMenu::create(pMenuItem, NULL);
		pMenu->setPosition( SCREEN_CENTER_POS + ccp( 0, -50 ));
		addChild(pMenu, 1);

		m_pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("").c_str(), "Arial", 36 );
		m_pLabel->setPosition( SCREEN_CENTER_POS + ccp( 0, -200 ));
		addChild(m_pLabel);

		return true;
	}
public:
	void ShowGuiderCallback(CCObject* pSender)
	{
		m_pGuideLayer = FKCW_UI_SimpleRookieGuiderLayer::Create();
		m_pGuideLayer->setArrow( CCSprite::create( s_szArrowPath ));
		m_pGuideLayer->AddRegion( CCRectMake( 300, 300, 50, 50),
			CCCallFunc::create( this,callfunc_selector( CTest_UI_SimpleRookieGuiderLayer::OnClickFirstRegion )), false );
		m_pGuideLayer->PointToRegionCenter( 0, 60, 120.0f, 250.0f );
		addChild( m_pGuideLayer );
	}
public:
	void OnClickFirstRegion()
	{
		m_pLabel->setString( FKCW_Base_StringConvert::a2u("��ɵ�һ�����").c_str() );

		m_pStatic = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("������������").c_str(), "Arial", 26 );
		m_pStatic->setColor( ccBLUE );
		m_pStatic->setPosition( SCREEN_CENTER_POS + ccp( 50, 200 ));
		addChild( m_pStatic, 1 );

		removeChild( m_pGuideLayer );
		m_pGuideLayer = FKCW_UI_SimpleRookieGuiderLayer::Create();
		m_pGuideLayer->setArrow( CCSprite::create( s_szArrowPath ));
		m_pGuideLayer->AddRegion( m_pStatic,
			CCCallFunc::create( this,callfunc_selector( CTest_UI_SimpleRookieGuiderLayer::OnClickSecondRegion )), false );
		m_pGuideLayer->PointToRegionCenter( 0, 60, 120.0f, 250.0f );
		addChild( m_pGuideLayer );
	}

	void OnClickSecondRegion()
	{
		m_pLabel->setString( FKCW_Base_StringConvert::a2u("��ɵڶ������,��һ�ν���Ҫǿ�Ƶȴ�3��").c_str() );

		removeChild( m_pStatic );
		removeChild( m_pGuideLayer );
		m_pGuideLayer = FKCW_UI_SimpleRookieGuiderLayer::Create();
		m_pGuideLayer->setArrow( CCSprite::create( s_szArrowPath ));
		m_pGuideLayer->AddRegion( CCRectMake( 500, 400, 20, 30), NULL, true );
		m_pGuideLayer->AddRegion( CCRectMake( 150, 200, 100, 60), NULL, true );
		m_pGuideLayer->PointToRegionCenter( 0, 60, 120.0f, 250.0f );
		m_pGuideLayer->EnableRegionCheckAfter( 3.0f );
		addChild( m_pGuideLayer );
	}
public:
	CREATE_FUNC( CTest_UI_SimpleRookieGuiderLayer );
private:
	CCLabelTTF*							m_pStatic;
	FKCW_UI_SimpleRookieGuiderLayer*	m_pGuideLayer;
	CCLabelTTF*							m_pLabel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, SimpleRookieGuider, ���������㣬��ͬʱ���ж������(��ڵ�)���֣������󣨴������ʱ������ƣ��ɻص������ڻص��д�����������)
//-------------------------------------------------------------------------