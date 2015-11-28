//*************************************************************************
//	��������:	2014-12-23
//	�ļ�����:	Test_Base_ResourceLoader.h
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
class CTest_Base_ResourceLoaderLayer : public CCLayer, public FKCW_Base_ResourceLoaderListener
{
public:
	virtual bool init()
	{
		CCMenuItemLabel* pItemLabel = CCMenuItemLabel::create(
			CCLabelTTF::create( A2U("���ҿ�ʼ������Դ").c_str(), "Helvetica", 48),
			this,
			menu_selector(CTest_Base_ResourceLoaderLayer::onStartLoadClicked));
		pItemLabel->setPosition( SCREEN_CENTER_POS );
		pItemLabel->setColor( ccc3(230,155,3) );

		CCMenu* menu = CCMenu::create(pItemLabel, NULL);
		menu->setPosition(CCPointZero);
		addChild(menu);

		m_pPercentLabel = CCLabelTTF::create("0%", "Helvetica", 32);
		m_pPercentLabel->setPosition( SCREEN_CENTER_POS + ccp(0, -100));
		addChild(m_pPercentLabel);

		return true;
	}
public:
	void onStartLoadClicked( CCObject* pSender )
	{
		FKCW_Base_ResourceLoader* pLoader = new FKCW_Base_ResourceLoader( this );
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddPlatformStringTask( "zh",s_szLocaliztionZHFile, false);
		pLoader->AddArmatureTask( s_szArmatureCowboyPlist, s_szArmatureCowboyPic,
			s_szArmatureCowboy, NULL, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);
		pLoader->AddImageTask(s_szExpandNodeBgPath, 0.1f);

		pLoader->Run();
	}

	void OnResourceLoadingProgress( float p_fProgress, float p_fDelta )
	{
		char buf[32];
		sprintf(buf, "%d%%", (int)p_fProgress);
		m_pPercentLabel->setString(buf);
	}
	// ����Դ�������ʱ��֪ͨ
	void		OnResourceLoadingDone()
	{
		m_pPercentLabel->setString( A2U("���").c_str());
	}
public:
	CREATE_FUNC( CTest_Base_ResourceLoaderLayer );
private:
	CCLabelTTF*			m_pPercentLabel;
};
//-------------------------------------------------------------------------
CREATE_TEST_SCENE_CLASS(Base, ResourceLoader, �����߳���Դ����)
//-------------------------------------------------------------------------