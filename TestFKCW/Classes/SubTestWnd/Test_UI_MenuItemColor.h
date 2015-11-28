//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_MenuItemColor.h
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
class CTest_UI_MenuItemColorLayer : public CCLayer
{
public:
	virtual bool init()
	{
		FKCW_UI_MenuItemColor* p1 = FKCW_UI_MenuItemColor::Create( ccc4( 50, 50, 230, 180 ));
		p1->setContentSize( CCSizeMake(50, 50) );
		FKCW_UI_MenuItemColor* p2 = FKCW_UI_MenuItemColor::Create( ccc4( 50, 50, 230, 255 ),
			ccc4( 0, 0, 130, 255 ), ccc4( 255, 0, 0, 255 ), this, 
			menu_selector(CTest_UI_MenuItemColorLayer::MenuHandlerFunc) );
		CCMenu* pMenu = CCMenu::create( p1, p2, NULL );
		pMenu->alignItemsVertically();
		pMenu->setPosition(SCREEN_CENTER_POS);
		this->addChild( pMenu );

		m_pLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("").c_str(), "Arial", 26 );
		m_pLabel->setPosition( SCREEN_CENTER_POS + ccp( 0, -200 ));
		addChild(m_pLabel);

		return true;
	}
public:
	void MenuHandlerFunc(CCObject* p)
	{
		char szMsg[32];
		memset( szMsg, 0, 32 );
		sprintf( szMsg, "��ť %d �������¼�", p->m_uID );
		m_pLabel->setString( FKCW_Base_StringConvert::a2u(szMsg).c_str() );
	}
public:
	CREATE_FUNC( CTest_UI_MenuItemColorLayer );
private:
	CCLabelTTF* m_pLabel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, MenuItemColor, һ���Զ�����η��񣬴�С����״̬��ɫ�����û�ָ������������ͼƬ���ɽ�����Ϣ����������ΪMenuItem)
//-------------------------------------------------------------------------