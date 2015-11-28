//*************************************************************************
//	��������:	2014-12-23
//	�ļ�����:	Test_Action_CallFuncT.h
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
class CTest_Action_CallFuncTLayer : public CCLayer
{
public:
	virtual bool init()
	{
		m_pLabel = CCLabelTTF::create("0", "Helvetica", 48);
		m_pLabel->setPosition(SCREEN_CENTER_POS);
		addChild(m_pLabel);

		runAction(CCSequence::create(CCDelayTime::create(1),
			FKCW_Action_CallfuncT<int>::Create(this, 
			(FKCW_Action_CallfuncT<int>::SEL_CallFuncT)&CTest_Action_CallFuncTLayer::randomChangeLabel,
			static_cast<int>(FKCW_Base_Utils::Random01() * 1000) ),
			NULL));

		return true;
	}
public:
	void randomChangeLabel(int n) 
	{
		char buf[32];
		sprintf(buf, "%d", n);
		m_pLabel->setString(buf);

		runAction(CCSequence::create(CCDelayTime::create(1),
			FKCW_Action_CallfuncT<int>::Create(this,
			(FKCW_Action_CallfuncT<int>::SEL_CallFuncT)&CTest_Action_CallFuncTLayer::randomChangeLabel, 
			static_cast<int>(FKCW_Base_Utils::Random01() * 1000) ),
			NULL));
	}
public:
	CREATE_FUNC( CTest_Action_CallFuncTLayer );
private:
	CCLabelTTF*		m_pLabel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Action, CallFuncT, ģ������ص����������������ڳ�����������Ҫ��ϴ������)
//-------------------------------------------------------------------------