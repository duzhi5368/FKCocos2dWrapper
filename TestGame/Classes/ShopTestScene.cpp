//-------------------------------------------------------------------------
#include "ShopTestScene.h"
//-------------------------------------------------------------------------


CShopTestScene::CShopTestScene(void)
{
}

//-------------------------------------------------------------------------
// ��ʼ�첽������Դ
void CShopTestScene::onLoadResources()
{

}
//-------------------------------------------------------------------------
// �����߼���ʼ��
void CShopTestScene::onLoadScene()
{
	setAutoRemoveUnusedTexture( true );

	// ������,����������ʾ���
	{
		m_pRootWindow = FKCW_UIWidget_WidgetWindow::create();
		m_pRootWindow->setMultiTouchEnabled(true);
		this->addChild(m_pRootWindow);
	}
	
	// ���ذ�ť
	{
		CCMenu *pMenu = CCMenu::create();
		pMenu->setPosition(CCPointZero);
		addChild(pMenu);
		CCMenuItemImage* pBtn = CCMenuItemImage::create();
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("back_button_normal_e.png"); 
		pBtn->setNormalSpriteFrame(pFrame);
		pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("back_button_touch_e.png"); 
		pBtn->setSelectedSpriteFrame(pFrame);
		pBtn->setTarget(this, menu_selector(CShopTestScene::onClick));
		pBtn->setPosition(SCREEN_CENTER_POS + ccp(0,400));
		pMenu->addChild(pBtn);
	}
}
//-------------------------------------------------------------------------
void CShopTestScene::onClick(CCObject* sender)
{

	FKCW_SceneExMgr_SceneExMgr::sharedManager()->popScene(this);
}
//-------------------------------------------------------------------------
// ��������ʾʱ����
void CShopTestScene::onEnterScene()
{

}
//-------------------------------------------------------------------------
// ����������ʱ����
void CShopTestScene::onExitScene()
{

}
//-------------------------------------------------------------------------
