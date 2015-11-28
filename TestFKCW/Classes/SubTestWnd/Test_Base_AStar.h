//*************************************************************************
//	��������:	2014-12-14
//	�ļ�����:	Test_Base_AStar.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	A*Ѱ·
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_Base_AStarLayer : public CCLayer
{
public:
	bool init()
	{
		m_pAStar = NULL;
		m_pClickType = 1;
		m_pStartView = NULL;
		m_pEndView = NULL;

		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		this->addChild(m_pWindow);

		//�ǵ��ͷ�Ŷ
		m_pAStar = new FKCW_Base_AStar();
		m_pAStar->SetMapSize(10, 10);
		m_pAStar->SetStart(SCoord(0, 0));	//���
		m_pAStar->SetTarget(SCoord(5, 9));	//�յ�
		m_pAStar->SetDiagonalEnable(true);
		
		for (int i=0; i<10; i++)
		{
			for (int j=0; j<10; j++)
			{
				FKCW_UIWidget_ColorView* item = FKCW_UIWidget_ColorView::create(cc4GREEN);
				item->setContentSize(CCSize(44, 44));
				item->setTag(10*i + j);	//��ʶ
				item->setPosition(CCPoint( static_cast<float>((44+1)*j + 100), static_cast<float>((44+1)*i + 100)));
				item->setTouchEnabled(true);
				item->setOnClickListener(this, fkcw_uiwidget_click_selector(CTest_Base_AStarLayer::onClick));
				m_pWindow->addChild(item);

				if (item->getTag() == 0)
				{
					item->setColor(ccBLUE);
					m_pStartView = item;
				}
				if (item->getTag() == 59)
				{
					item->setColor(ccRED);
					m_pEndView = item;
				}
			}
		}
		
		float uX = SCREEN_CENTER_POS.x + 300;
		float uY = 220;
		//��㿪��
		FKCW_UIWidget_ToggleView* toggleStart = FKCW_UIWidget_ToggleView::create(s_szToggle1Path, s_szToggle2Path, s_szToggle3Path);
		CCLabelTTF* labelStart = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("���").c_str(), "", 26);
		labelStart->setPosition(toggleStart->getContentSize()/2);
		toggleStart->addChild(labelStart);
		toggleStart->setPosition(uX, uY);
		toggleStart->setTag(1);
		toggleStart->setExclusion(1);
		toggleStart->setChecked( true );
		toggleStart->setOnCheckListener(this, fkcw_uiwidget_check_selector(CTest_Base_AStarLayer::onCheckChange));
		m_pWindow->addChild(toggleStart);

		//�յ㿪��
		FKCW_UIWidget_ToggleView* toggleEnd = FKCW_UIWidget_ToggleView::create(s_szToggle1Path, s_szToggle2Path, s_szToggle3Path);
		CCLabelTTF* labelEnd = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�յ�").c_str(), "", 26);
		labelEnd->setPosition(toggleEnd->getContentSize()/2);
		toggleEnd->addChild(labelEnd);
		toggleEnd->setPosition(uX, uY+100);
		toggleEnd->setTag(2);
		toggleEnd->setExclusion(1);
		toggleEnd->setOnCheckListener(this, fkcw_uiwidget_check_selector(CTest_Base_AStarLayer::onCheckChange));
		m_pWindow->addChild(toggleEnd);

		//�ϰ�����
		FKCW_UIWidget_ToggleView* toggleWall = FKCW_UIWidget_ToggleView::create(s_szToggle1Path, s_szToggle2Path, s_szToggle3Path);
		CCLabelTTF* labelWall = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("�ϰ�").c_str(), "", 26);
		labelWall->setPosition(toggleWall->getContentSize()/2);
		toggleWall->addChild(labelWall);
		toggleWall->setPosition(uX, uY+200);
		toggleWall->setTag(3);
		toggleWall->setExclusion(1);
		toggleWall->setOnCheckListener(this, fkcw_uiwidget_check_selector(CTest_Base_AStarLayer::onCheckChange));
		m_pWindow->addChild(toggleWall);

		// �Ƿ�ֻ����4��
		FKCW_UIWidget_ToggleView* toggleDir = FKCW_UIWidget_ToggleView::create(s_szToggle1Path, s_szToggle2Path, s_szToggle3Path);
		CCLabelTTF* labelDir = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("8��").c_str(), "", 26);
		labelDir->setPosition(toggleDir->getContentSize()/2);
		toggleDir->addChild(labelDir, 1, 1 );
		toggleDir->setPosition(uX, uY+300);
		toggleDir->setTag(4);
		toggleDir->setExclusion(2);
		toggleDir->setOnCheckListener(this, fkcw_uiwidget_check_selector(CTest_Base_AStarLayer::onCheckChange));
		m_pWindow->addChild(toggleDir);
		
		//Ѱ·��ť
		FKCW_UIWidget_Button* button = FKCW_UIWidget_Button::create(s_szButtonNormalPath, s_szButtonPressPath, s_szButtonDisablePath);
		button->initText(FKCW_Base_StringConvert::a2u("��ʼѰ·").c_str(), "", 28);
		button->setPosition(SCREEN_CENTER_POS + CCPoint(300, -215));
		button->setOnClickListener(this, fkcw_uiwidget_click_selector(CTest_Base_AStarLayer::findRoute));
		m_pWindow->addChild(button);

		return true;
	}
public:
	void onCheckChange(CCObject* pSender, bool checked)
	{
		FKCW_UIWidget_ToggleView* v = (FKCW_UIWidget_ToggleView*)pSender;
		m_pClickType = v->getTag();

		// 4��/8���л�
		if( m_pClickType == 4 )
		{
			m_pAStar->SetDiagonalEnable( !m_pAStar->IsDiagonalEnable() );
			if( m_pAStar->IsDiagonalEnable() )
			{
				CCLabelTTF* p = (CCLabelTTF*)(v->getChildByTag( 1 ));
				p->setString( FKCW_Base_StringConvert::a2u("8��").c_str() );
			}
			else
			{
				CCLabelTTF* p = (CCLabelTTF*)(v->getChildByTag( 1 ));
				p->setString( FKCW_Base_StringConvert::a2u("4��").c_str() );
			}
		}
	}

	void onClick(CCObject* pSender)
	{
		FKCW_UIWidget_ColorView* view = (FKCW_UIWidget_ColorView*)pSender;
		switch (m_pClickType)
		{
		case 1://���
			if(!sameColor(view->getColor(), ccBLUE) 
				&& !sameColor(view->getColor(), ccRED)
				&& !sameColor(view->getColor(), ccBLACK))
			{
				m_pStartView->setColor(ccGREEN);
				view->setColor(ccBLUE);
				m_pStartView = view;

				m_pAStar->SetStart(SCoord(view->getTag()/10, view->getTag()%10));
			}
			break;
		case 2://�յ�
			if(!sameColor(view->getColor(), ccBLUE) 
				&& !sameColor(view->getColor(), ccRED)
				&& !sameColor(view->getColor(), ccBLACK))
			{
				m_pEndView->setColor(ccGREEN);
				view->setColor(ccRED);
				m_pEndView = view;

				m_pAStar->SetTarget(SCoord(view->getTag()/10, view->getTag()%10));
			}
			break;
		case 3://�ϰ�
			if(!sameColor(view->getColor(), ccBLUE) 
				&& !sameColor(view->getColor(), ccRED)
				)
			{
				if( !sameColor(view->getColor(), ccBLACK) )
				{
					view->setColor(ccBLACK);
					m_pAStar->SetObstacle(SCoord(view->getTag()/10, view->getTag()%10));
				}
				else
				{
					view->setColor(ccGREEN);
					m_pAStar->CancleObstacle(SCoord(view->getTag()/10, view->getTag()%10));
				}
			}
			break;
		}
	}

	void findRoute(CCObject* pSender)
	{
		std::vector<SCoord>* list = new std::vector<SCoord>;
		//����
		for (int i=0; i<10; i++)
		{
			for (int j=0; j<10; j++)
			{
				FKCW_UIWidget_ColorView* view = (FKCW_UIWidget_ColorView*)m_pWindow->getChildByTag(i*10 + j);
				if(!sameColor(view->getColor(), ccBLUE) 
					&& !sameColor(view->getColor(), ccRED) 
					&& !sameColor(view->getColor(), ccBLACK))
				{
					view->setColor(ccGREEN);
				}
			}
		}

		//����·��
		if(m_pAStar->ComputeRoute())
		{
			m_pAStar->GetRoute(list);
			for (unsigned int i=0; i<list->size(); i++)
			{
				SCoord sc = list->at(i);
				FKCW_UIWidget_ColorView* view = (FKCW_UIWidget_ColorView*)m_pWindow->getChildByTag(sc._x*10 + sc._y);
				if(view!=m_pStartView && view!=m_pEndView)
				{
					view->setColor(ccORANGE);
				}
			}
		}
		delete list;
	}
	//**��ɫ�Ƿ����*/
	bool sameColor(ccColor3B colorA, ccColor3B colorB)
	{
		if(colorA.b == colorB.b && colorA.g == colorB.g && colorA.r == colorB.r)
		{
			return true;
		}
		return false;
	}
public:
	virtual void onExit() 
	{
		//�ͷ�
		if( m_pAStar!=NULL )
		{
			delete m_pAStar;
			m_pAStar = NULL;
		}
		CCLayer::onExit();
	}
public:
	CREATE_FUNC( CTest_Base_AStarLayer );
public:
	FKCW_UIWidget_WidgetWindow*				m_pWindow;
	FKCW_UIWidget_ColorView*				m_pStartView;
	FKCW_UIWidget_ColorView*				m_pEndView;
	FKCW_Base_AStar*						m_pAStar;
	int										m_pClickType;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Base, AStar, A*Ѱ·��ʾ)
//-------------------------------------------------------------------------