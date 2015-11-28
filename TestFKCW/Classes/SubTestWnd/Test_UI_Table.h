//*************************************************************************
//	��������:	2014-11-27
//	�ļ�����:	Test_UI_Table.h
//  �� �� ��:   WilhanTian
//	��Ȩ����:	MIT
//	˵    ��:	UITable �ɽ�һ��node��һ�������ڽ�����������
//	���� ���:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_UI_TableLayer : public CCLayer
{
public:
	virtual bool init()
	{
		for( unsigned int i = 0; i < 11; ++i )
		{
			m_pSpriteList[i] = CCSprite::create( s_szButtonNormalPath );
			m_pSpriteList[i]->setPosition(CCPoint(FKCW_Base_Utils::RandomInRange(0.0f, SCERRN_WIDTH), FKCW_Base_Utils::RandomInRange(0.0f, SCERRN_HEIGHT)));
			this->addChild( m_pSpriteList[i] );
		}
		m_nSpriteWidth = (int)m_pSpriteList[0]->getContentSize().width;
		m_nSpriteHeight = (int)m_pSpriteList[0]->getContentSize().height;

		CCLabelTTF* lable = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("����������Щ����").c_str(), "Arial", 26 );
		lable->setColor(ccc3(230,155,3));

		CCMenuItemLabel* itemLable = CCMenuItemLabel::create(lable, this, menu_selector(CTest_UI_TableLayer::menuCallFunc));
		CCMenu* menu = CCMenu::create(itemLable, NULL);
		menu->setPosition(SCREEN_CENTER_POS + CCPoint(0, -200));
		this->addChild(menu);

		return true;
	}
public:
	void menuCallFunc(CCObject* pSender)
	{
		int nCol = 4;
		int nRow = 3;
		int nTableWidth = (nRow * m_nSpriteWidth);
		int nTableHeight = (nCol * m_nSpriteHeight);
		FKCW_UI_Table* table = FKCW_UI_Table::create(CCRect( SCREEN_CENTER_POS_X - nTableWidth / 2, 
			320.0f - nTableHeight / 2 , static_cast<float>(nTableWidth), 
			static_cast<float>(nTableHeight) ),
			nRow, nCol, true, true);
		for( int i = 0; i < 11; ++i )
		{
			table->registerNode( m_pSpriteList[i] );
		}
		// ����
		table->arrangeItems();
	}
public:
	CREATE_FUNC( CTest_UI_TableLayer );
private:
	int			m_nSpriteWidth;
	int			m_nSpriteHeight;
	CCSprite*	m_pSpriteList[11];
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(UI, Table, UI Table ��������Node)
//-------------------------------------------------------------------------