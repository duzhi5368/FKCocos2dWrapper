//*************************************************************************
//	��������:	2014-12-19
//	�ļ�����:	Test_GR_Examples.h
//  �� �� ��:   WilhanTian	
//	��Ȩ����:	MIT
//	˵    ��:	
//  ��    ע:	����ʹ�á�����
//  �޸ļ�¼: �����������Ż�������ʾ
//	�� �� ��: �˹۸� Rect
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "../resource.h"
#include "../TestScene.h"
#include "../../../FKCWLib/FKCocos2dxWrapper.h"
//-------------------------------------------------------------------------
class CTest_GR_ExamplesLayer : public CCLayer
{
public:
	bool init()
	{
		m_pWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pWindow->setMultiTouchEnabled(true);
		addChild(m_pWindow);

		//����
		FKCW_GR_LongPressGestureRecognizer* grLongPress = FKCW_GR_LongPressGestureRecognizer::create();
		grLongPress->SetTarget(this, callfuncO_selector(CTest_GR_ExamplesLayer::onLongPress));
		m_pWindow->addChild(grLongPress);

		//��������,��������
		FKCW_GR_PanGestureRecognizer* grPan = FKCW_GR_PanGestureRecognizer::create();
		grPan->SetTarget(this, callfuncO_selector(CTest_GR_ExamplesLayer::onPan));
		m_pWindow->addChild(grPan);

		//���
		FKCW_GR_PinchGestureRecognizer* grPinch = FKCW_GR_PinchGestureRecognizer::create();
		grPinch->SetTarget(this, callfuncO_selector(CTest_GR_ExamplesLayer::onPinch));
		m_pWindow->addChild(grPinch);

		//���ٻ�������pan��ͬ���ٶ�
		FKCW_GR_SwipeGestureRecognizer* grSwipe = FKCW_GR_SwipeGestureRecognizer::create();
		grSwipe->SetTarget(this, callfuncO_selector(CTest_GR_ExamplesLayer::onSwipe));
		m_pWindow->addChild(grSwipe);

		//���
		FKCW_GR_TapGestureRecognizer* grTap = FKCW_GR_TapGestureRecognizer::create();
		grTap->SetTarget(this, callfuncO_selector(CTest_GR_ExamplesLayer::onTap));
		m_pWindow->addChild(grTap);
	
		
		std::string str = "Ŀǰ֧�ֵ����ƣ�\n";
		str += "���㳤��:���峤��ʱ��Ϊ0.5s\n";
		str += "���㻬��:����2dxԭ�е�moved��Ϣ�ж�\n";
		str += "������:ֻ�ж�ǰ�������ص�\n";
		str += "������ٻ���:�ɸ�����Ӧ�ٶ�(60p/300ms)\n";
		str += "������";

		CCLabelTTF* pLabel = CCLabelTTF::create(
			A2U(str.c_str()).c_str(), 
			"", 24);
		pLabel->setPosition(SCREEN_CENTER_POS);
		m_pWindow->addChild(pLabel);
		//��ʾ
		m_pInfoLabel = CCLabelTTF::create(A2U("��ǰ����Ϣ").c_str(), "", 26);
		m_pInfoLabel->setColor(ccc3(255,0,0));
		m_pInfoLabel->setPosition(SCREEN_CENTER_POS+ccp(0, 200));
		m_pWindow->addChild(m_pInfoLabel);

		return true;
	}
public:
	void onLongPress(CCObject* object)
	{
		FKCW_GR_LongPress* p = dynamic_cast<FKCW_GR_LongPress*>(object);
		if( p == NULL )
		{
			m_pInfoLabel->setString(A2U("������Ϣ").c_str());
		}
		else
		{
			char szInfo[64];
			memset( szInfo, 0, 64 );
			sprintf( szInfo, "������Ϣ: pos.x = %.2f, pos.y = %.2f", 
				p->m_tagLocation.x, p->m_tagLocation.y );
			m_pInfoLabel->setString(A2U( szInfo ).c_str());
		}
	}
	void onPan(CCObject* object)
	{
		FKCW_GR_Pan* p = dynamic_cast<FKCW_GR_Pan*>(object);
		if( p == NULL )
		{
			m_pInfoLabel->setString(A2U("��������").c_str());
		}
		else
		{
			char szInfo[128];
			memset( szInfo, 0, 128 );
			sprintf( szInfo, "������Ϣ: pos.x = %.2f, pos.y = %.2f delta.x = %.2f, delta.y = %.2f", 
				p->m_tagLocation.x, p->m_tagLocation.y,
				p->m_tagDelta.x, p->m_tagDelta.y );
			m_pInfoLabel->setString(A2U( szInfo ).c_str());
		}
	}
	void onPinch(CCObject* object)
	{
		FKCW_GR_Pinch* p = dynamic_cast<FKCW_GR_Pinch*>(object);
		if( p == NULL )
		{
			m_pInfoLabel->setString(A2U("���").c_str());
		}
		else
		{
			char szInfo[64];
			memset( szInfo, 0, 64 );
			if( p->m_eType == eGRPinchType_Close )
			{
				sprintf(szInfo, "%s", "�����С");
			}
			else if( p->m_eType == eGRPinchType_Open )
			{
				sprintf(szInfo, "%s", "��ϷŴ�");
			}
			else
			{
				sprintf(szInfo, "%s", "���:WTF");
			}
			m_pInfoLabel->setString(A2U( szInfo ).c_str());
		}
	}
	void onSwipe(CCObject* object)
	{
		FKCW_GR_Swipe* p = dynamic_cast<FKCW_GR_Swipe*>(object);
		if( p == NULL )
		{
			m_pInfoLabel->setString(A2U("���ٻ���").c_str());
		}
		else
		{
			char szInfo[128];
			memset( szInfo, 0, 128 );
			std::string str;
			if( (p->m_eDirection & eSwipeDirection_Right) == eSwipeDirection_Right )
				str += "����";
			if( (p->m_eDirection & eSwipeDirection_Left) == eSwipeDirection_Left )
				str += "����";
			if( (p->m_eDirection & eSwipeDirection_Up) == eSwipeDirection_Up )
				str += "����";
			if( (p->m_eDirection & eSwipeDirection_Down) == eSwipeDirection_Down )
				str += "����";
			sprintf( szInfo, "���ٻ���: pos.x = %.2f, pos.y = %.2f", 
				p->m_tagLocation.x, p->m_tagLocation.y );
			str += string( szInfo );
			m_pInfoLabel->setString(A2U( str.c_str() ).c_str());
		}
	}
	void onTap(CCObject* object)
	{
		FKCW_GR_Tap* p = dynamic_cast<FKCW_GR_Tap*>(object);
		if( p == NULL )
		{
			m_pInfoLabel->setString(A2U("���").c_str());
		}
		else
		{
			char szInfo[64];
			memset( szInfo, 0, 64 );
			sprintf( szInfo, "�����Ϣ: pos.x = %.2f, pos.y = %.2f", 
				p->m_tagLocation.x, p->m_tagLocation.y );
			m_pInfoLabel->setString(A2U( szInfo ).c_str());
		}
	}
public:
	CREATE_FUNC( CTest_GR_ExamplesLayer );
protected:
	CCLabelTTF* m_pInfoLabel;
	FKCW_UIWidget_WidgetWindow* m_pWindow;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(GR, Examples, ����ʶ��ʾ��)