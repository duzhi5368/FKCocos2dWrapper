//-------------------------------------------------------------------------
#include "PlayTestScene.h"
#include "AudioBridge.h"
//-------------------------------------------------------------------------

CPlayTestScene::CPlayTestScene()
{
}
//-------------------------------------------------------------------------
// ��ʼ�첽������Դ
void CPlayTestScene::onLoadResources()
{
	
}
//-------------------------------------------------------------------------
// �����߼���ʼ��
void CPlayTestScene::onLoadScene()
{
	setAutoRemoveUnusedTexture( true );

	__CreatePlayUI();
	
	// �˳�������ť
	{
		CCMenu* pMenu = CCMenu::create();
		pMenu->setPosition(CCPointZero);
		addChild(pMenu);

		CCMenuItemImage* pBtn = CCMenuItemImage::create();
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("back_button_normal_e.png"); 
		pBtn->setNormalSpriteFrame(pFrame);
		pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("back_button_touch_e.png"); 
		pBtn->setSelectedSpriteFrame(pFrame);
		pBtn->setTarget(this, menu_selector(CPlayTestScene::onClick));
		pBtn->setPosition(SCREEN_CENTER_POS + ccp(0,400));
		pMenu->addChild(pBtn);
	}
	

}
//-------------------------------------------------------------------------
// ��������ʾʱ����
void CPlayTestScene::onEnterScene()
{
	CAudioBridge::GetInstance().PlayBackGroudMusic(eSubSceneType_Play);
	__AddListenNetMessage();

	if (m_pStarWindow == NULL)
	{
		return;
	}
	CCSize size = CCSize(SCERRN_WIDTH - 20, SCERRN_WIDTH - 20);
	m_StarMgr.init(m_pStarWindow,size);
	m_StarMgr.Start();

}
//-------------------------------------------------------------------------
// ����������ʱ����
void CPlayTestScene::onExitScene()
{
	CAudioBridge::GetInstance().StopBackGroundMusic();
	__RemovListenNetMessage();

	m_StarMgr.ClearAll(true);
}
//-------------------------------------------------------------------------

// �����л���ť
void CPlayTestScene::OnSelectBtn(CCObject* pSender)
{
	if (pSender == NULL)
	{
		return;
	}

	CAudioBridge::GetInstance().PlayEffect(eSound_Button);

	FKCW_UIWidget_Widget* pWidget = dynamic_cast<FKCW_UIWidget_Widget*>(pSender);
	if (pWidget == NULL)
	{
		return;
	}

	int nTag = pWidget->getUserTag();
	if (nTag <= eSubSceneType_Min)
	{
		return;
	}

	IEventSystem* pEvent = GetEventSystem();
	if (pEvent == NULL)
	{
		return;
	}

	if (nTag < eSubSceneType_Max)
	{
		pEvent->FireExec(eEvent_UIEvent,eEvent_Scene_Switch,nTag,NULL,0);
		return;
	}

	if (nTag < eTestPlayButton_Max)
	{
		if (nTag == eTestPlayButton_Music)
		{
			bool bIsVisible = m_pSoundBtnHideImage->isVisible();
			m_pSoundBtnHideImage->setVisible(!bIsVisible);
		}

		if (nTag > eTestPlayButton_AddMoney)
		{
			FKCW_UIWidget_Button* pBtn = dynamic_cast<FKCW_UIWidget_Button*>(pSender);
			m_pItemBgImage->setVisible(true);
			m_pItemBgImage->setPosition(pBtn->getPosition());
		}
		pEvent->FireExec(eEvent_UIEvent,eEvent_Play_ButtonClick,nTag,NULL,0);
		return;
	}
	


}
//-------------------------------------------------------------------------
void CPlayTestScene::onClick(CCObject* sender)
{
	FKCW_SceneExMgr_SceneExMgr::sharedManager()->popScene(this);
}
//-------------------------------------------------------------------------
// ����UI
void CPlayTestScene::__CreatePlayUI()
{
	// background
	FKCW_UIWidget_ImageView* pBackGroundImage = FKCW_UIWidget_ImageView::create(s_szPlayBgPath);
	pBackGroundImage->setScaleX(SCERRN_WIDTH / pBackGroundImage->getContentSize().width);
	pBackGroundImage->setScaleY(SCERRN_HEIGHT / pBackGroundImage->getContentSize().height);
	pBackGroundImage->setPosition( SCREEN_CENTER_POS);
	addChild( pBackGroundImage );

	
	__CreateBGUI();

	__CreateStar();
}
//-------------------------------------------------------------------------
void CPlayTestScene::__CreateBGUI()
{
	m_pRootWindow = FKCW_UIWidget_WidgetWindow::create();
	m_pRootWindow->setMultiTouchEnabled(true);
	this->addChild(m_pRootWindow);

	FKCW_UIWidget_Button* pButton = NULL;
	FKCW_UIWidget_ImageView* pImage = NULL;
	CCPoint btnPos;

	// ��ʾ��Ҫ�ļ���Label
	{
		// chap Label
		btnPos = SCREEN_LEFT_UP_POS + ccp(75,-30);
		pImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szChapterBg);
		pImage->setPosition(btnPos);
		m_pRootWindow->addChild(pImage);

		m_pChapterLabel = FKCW_UIWidget_LabelAtlas::create("99", s_szYellowLabels, 30, 36, '0');
		m_pChapterLabel->setPosition(btnPos);
		m_pRootWindow->addChild(m_pChapterLabel);

		// target Label
		btnPos = SCREEN_LEFT_UP_POS + ccp(SCERRN_WIDTH / 2 + 100,-30);
		pImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szTargetBg);
		pImage->setPosition(btnPos);
		m_pRootWindow->addChild(pImage);

		m_pTargetLabel = FKCW_UIWidget_LabelAtlas::create("999", s_szRedLabels, 25, 36, '0');
		m_pTargetLabel->setPosition(btnPos + ccp(pImage->getContentSize().width/2 + 50,0));
		m_pRootWindow->addChild(m_pTargetLabel);

		// current Label
		btnPos = SCREEN_LEFT_UP_POS + ccp(SCERRN_WIDTH / 2 + 100,-80);
		pImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szCurrentBg);
		pImage->setPosition(btnPos);
		m_pRootWindow->addChild(pImage);

		m_pCurrentLabel = FKCW_UIWidget_LabelAtlas::create("999", s_szYellowLabels, 30, 36, '0');
		m_pCurrentLabel->setPosition(btnPos + ccp(pImage->getContentSize().width/2 + 50,0));
		m_pRootWindow->addChild(m_pCurrentLabel);

		// monery Label
		btnPos = SCREEN_LEFT_DOWN_POS + ccp(70,60);
		pImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szTextBg);
		pImage->setPosition(btnPos);
		m_pRootWindow->addChild(pImage);

		btnPos = SCREEN_LEFT_DOWN_POS + ccp(25,60);
		pImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szMasonry);
		pImage->setPosition(btnPos);
		m_pRootWindow->addChild(pImage);

		btnPos = SCREEN_LEFT_DOWN_POS + ccp(90,60);
		m_pMoneyLabel = FKCW_UIWidget_Label::create(FKCW_Base_StringConvert::a2u("50000").c_str(), "", 32.0f);
		m_pMoneyLabel->setPosition(btnPos);
		m_pMoneyLabel->setColor(ccc3(0, 255, 0));
		m_pMoneyLabel->setTouchEnabled(true);
		m_pMoneyLabel->setOnTouchEndedListener(
			this, fkcw_uiwidget_touchevent_selector(CPlayTestScene::OnLabelTouchEnded));
		m_pRootWindow->addChild(m_pMoneyLabel);
	}
	

	// ��ť��
	{
		btnPos = SCREEN_LEFT_DOWN_POS + ccp(180,60);
		pButton = __CreateButton(eTestPlayButton_AddMoney,btnPos,s_szAddNon,s_szAddTou,"add");
		m_pRootWindow->addChild(pButton);

		// music Button
		btnPos = SCREEN_LEFT_UP_POS + ccp(70,-100);
		pButton = __CreateButton(eTestPlayButton_Music,btnPos,s_szSoundOn,s_szSoundOff,"music");
		m_pRootWindow->addChild(pButton);

		m_pSoundBtnHideImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szSoundHide);
		m_pSoundBtnHideImage->setPosition(btnPos);
		m_pSoundBtnHideImage->setVisible(false);
		m_pRootWindow->addChild(m_pSoundBtnHideImage);

		// item bg
		m_pItemBgImage = FKCW_UIWidget_ImageView::createWithSpriteFrameName(s_szItemBg);
		m_pItemBgImage->setVisible(false);
		m_pRootWindow->addChild(m_pItemBgImage);

		// clear all Button
		btnPos = SCREEN_RIGHT_DOWN_POS + ccp(-250,70);
		pButton = __CreateButton(eTestPlayButton_All,btnPos,s_szAllButton,s_szAllButton,"all");
		m_pRootWindow->addChild(pButton);

		// sort Button
		btnPos = SCREEN_RIGHT_DOWN_POS + ccp(-150,70);
		pButton = __CreateButton(eTestPlayButton_SortStar,btnPos,s_szSortButton,s_szSortButton,"sort");
		m_pRootWindow->addChild(pButton);

		// magic hand Button
		btnPos = SCREEN_RIGHT_DOWN_POS + ccp(-50,70);
		pButton = __CreateButton(eTestPlayButton_HandMagic,btnPos,s_szHandButton,s_szHandButton,"hand");
		m_pRootWindow->addChild(pButton);
	}
}
//-------------------------------------------------------------------------
void CPlayTestScene::__CreateStar()
{
	m_pStarWindow = FKCW_UIWidget_WidgetWindow::create();
	m_pStarWindow->setTouchEnabled(true);
	this->addChild(m_pStarWindow); 
	
}
//-------------------------------------------------------------------------
// ����button
FKCW_UIWidget_Button* CPlayTestScene::__CreateButton(
	int nType,CCPoint& pos,const char* pszImageName,const char* pszImageSecectName,const char* pszName)
{
	FKCW_UIWidget_Button* pBtn = FKCW_UIWidget_Button::create();
	pBtn->setNormalSpriteFrameName(pszImageName);
	pBtn->setSelectedSpriteFrameName(pszImageSecectName);
	pBtn->setDescription(pszName);
	pBtn->setUserTag(nType);
	pBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(CPlayTestScene::OnSelectBtn));
	pBtn->setPosition(pos);
	pBtn->setTouchEnabled(true);
	return pBtn;
}
//-------------------------------------------------------------------------
bool CPlayTestScene::OnLabelTouchEnded(CCObject* pSender, CCTouch* pTouch, float fDuration)
{
	FKCW_UIWidget_Label* pText = (FKCW_UIWidget_Label*) pSender;
	if (pText)
	{
		string str = pText->getString();
		int nValue = FKCW_Base_Utils::AtoI(str);
		nValue -= 100;
		if (nValue < 100)
		{
			nValue = 1000;
		}
		str = FKCW_Base_Utils::ItoA(nValue);
		pText->setString(str.c_str());
	}

	CAudioBridge::GetInstance().PlayEffect(eSound_Button);

	return true;
}
//-------------------------------------------------------------------------
void CPlayTestScene::__AddListenNetMessage()
{
	IMsgDispatchSystem* pMsgDispath = GetMsgDispatchSystem();
	if (pMsgDispath)
	{
		pMsgDispath->RegisteMsgHandler(this,eNetMsg_Main_Game,eNetMsg_Sub_PlayStar);
	}
}
//-------------------------------------------------------------------------
void CPlayTestScene::__RemovListenNetMessage()
{
	IMsgDispatchSystem* pMsgDispath = GetMsgDispatchSystem();
	if (pMsgDispath)
	{
		pMsgDispath->UnregisterMsgHandler(this,eNetMsg_Main_Game,eNetMsg_Sub_PlayStar);
	}
}
//-------------------------------------------------------------------------
// ���յ���Ϣ[ע�⣬�յ�����Ϣ�ڣ���������Ϣ�룬������������Ϣ��]
// ������szMsgData �յ�������ָ��
// ������nLen �յ������ݳ���
void CPlayTestScene::OnNetMessage( const char* szMsgData, int nLen )
{
	if (nLen != (sizeof(MSG_SUB_TYPE) + sizeof(S_GAME_INTVALUE_SUB_S2C)))
	{
		FKLOG("CPlayTestScene::OnNetMessage nLen = %d",nLen);
		FKLOG("CPlayTestScene::OnNetMessage S2CLen = %d",sizeof(S_GAME_INTVALUE_SUB_S2C));
		return;
	}
	MSG_SUB_TYPE SubType = *(MSG_SUB_TYPE*)( szMsgData);
	S_GAME_INTVALUE_SUB_S2C sIntValue = *(S_GAME_INTVALUE_SUB_S2C*)( szMsgData + sizeof(MSG_SUB_TYPE) );
	
	if (SubType != eNetMsg_Sub_PlayStar)
	{
		return;
	}
	int nValue = sIntValue.nValue;
	FKLOG("CPlayTestScene::OnNetMessage ���水ť�����������ݷ���:nValue = %d",nValue);
}
//-------------------------------------------------------------------------
