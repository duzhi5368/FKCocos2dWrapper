//*************************************************************************
//	��������:	2014-12-20
//	�ļ�����:	Test_RenderEx_JoystickNode.h
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
class CTest_RenderEx_JoystickNodeLayer : public CCLayer
{
public:
	bool init()
	{
		FKCW_RenderEx_JoystickNode* joystickNode = FKCW_RenderEx_JoystickNode::create(s_szBaseBoardPath, 128/2, s_szJoystickPath, 64/2);
		joystickNode->setPosition(SCREEN_CENTER_POS);
		joystickNode->setHandleEventListener(this, joystickEvent_selector(CTest_RenderEx_JoystickNodeLayer::onJoystickListener));
		this->addChild(joystickNode);

		m_pInfoLabel = CCLabelTTF::create(FKCW_Base_StringConvert::a2u("����קҡ��").c_str(), "", 26);
		m_pInfoLabel->setPosition(SCREEN_CENTER_POS + ccp(0, -200));
		this->addChild(m_pInfoLabel);

		return true;
	}
public:
	void onJoystickListener(float interval,float x, float y, ENUM_JoystickEventType type)
	{
		char c_type[28];
		if (type == JET_TOUCH_BEGIN)
		{
			sprintf(c_type, "������ʼ");
		}
		else if (type == JET_TOUCH_MOVE)
		{
			sprintf(c_type, "�����ƶ�");
		}
		if (type == JET_TOUCH_END)
		{
			sprintf(c_type, "��������");
		}

		char buff[128];
		sprintf(buff, "ʱ����:%f, x:%f, y:%f \n�¼�:%s", interval, x, y, c_type);
		
		m_pInfoLabel->setString(FKCW_Base_StringConvert::a2u(buff).c_str());
	}
public:
	CREATE_FUNC( CTest_RenderEx_JoystickNodeLayer );
protected:
	CCLabelTTF* m_pInfoLabel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(RenderEx, JoystickNode, ����ҡ�˽ڵ�)
//-------------------------------------------------------------------------