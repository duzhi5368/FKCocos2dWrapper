//*************************************************************************
//	��������:	2015-1-6
//	�ļ�����:	BaseScene.cpp
//  �� �� ��:   ������ FreeKnight	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "BaseScene.h"
#include "Resource.h"
//-------------------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------------------
#define LAYER_TAG		10000
#define SPIRTE_TAG		10001
//-------------------------------------------------------------------------
static std::string Tchar2String(wchar_t* src)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0,src, -1, NULL, 0, NULL, NULL);
	char* chRtn =new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, src, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	return str;
}
//-------------------------------------------------------------------------
CCScene* BaseLayer::scene()
{
    CCScene *scene = CCScene::create();
    BaseLayer *layer = BaseLayer::create();
	layer->setTag( LAYER_TAG );
    scene->addChild(layer);
    return scene;
}
//-------------------------------------------------------------------------
BaseLayer::BaseLayer()
{

}
//-------------------------------------------------------------------------
bool BaseLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// ��Ӽ��̷���
	CCDirector::sharedDirector()->getOpenGLView()->setAccelerometerKeyHook( BaseLayer::KeyboardHook ); 
	// add your code here

	// ������ɫ
	m_pBackgroundLayer = CCLayerColor::create( ccc4BFromccc4F(ccc4FFromccc3B( ccGRAY )));
	addChild( m_pBackgroundLayer );

	// ����DB����
	m_pDBSprite = new CCocos2dxDBSprite();
	if( m_pDBSprite == NULL )
		return false;
	m_pDBSprite->setTag( SPIRTE_TAG );
	m_pDBSprite->setPosition( SCREEN_CENTER_POS + ccp(0, -200) );
	this->addChild( m_pDBSprite );

	// ���֡�ص��¼�
	CTestAnimCallbackHandler* pTestEvent = new CTestAnimCallbackHandler;
	if( m_pDBSprite->getAnimation() )
		m_pDBSprite->getAnimation()->SetAniCallback( pTestEvent,NULL );

	// ����UI��
	if( !CreateUI() )
	{
		return false;
	}

	// ��ʾ���������
	UpdateBoneNum();

	// ��ʾ���鶯����
	UpdateFileName();

	// ��ʾ���鶯���б�
	UpdateActionList();
    
    return true;
}
//-------------------------------------------------------------------------
// WINDOWS ��Ϣ
void BaseLayer::KeyboardHook( UINT message,WPARAM wParam, LPARAM lParam )
{
	CCLayer* pLayer = (CCLayer*)( CCDirector::sharedDirector()->getRunningScene()->getChildByTag( LAYER_TAG ) );
	if( pLayer == NULL )
		return;
	CCocos2dxDBSprite* pSprite = (CCocos2dxDBSprite*)pLayer->getChildByTag( SPIRTE_TAG );
	if( pSprite == NULL )
		return;
	switch (message)  
	{  
	//case WM_MOUSEWHEEL:
	//	{
	//		if( (INT)wParam > 0 )
	//		{
	//			pSprite->setScale( pSprite->getScale() * 1.25f );
	//		}
	//		else
	//		{
	//			pSprite->setScale( pSprite->getScale() * 0.8f );
	//		}
	//	}
	//	break;
	case WM_KEYDOWN:  
		switch ( wParam )
		{
		case 'W':
			pSprite->setPosition( ccp(pSprite->getPositionX(), pSprite->getPositionY() + 20) );
			break;
		case 'S':
			pSprite->setPosition( ccp(pSprite->getPositionX(), pSprite->getPositionY() - 20) );
			break;
		case 'A':
			pSprite->setPosition( ccp(pSprite->getPositionX() - 30, pSprite->getPositionY() ) );
			break;
		case 'D':
			pSprite->setPosition( ccp(pSprite->getPositionX() + 30, pSprite->getPositionY()) );
			break;
		case VK_UP:
			pSprite->setScale( pSprite->getScale() * 1.25f );
			break;
		case VK_DOWN:
			pSprite->setScale( pSprite->getScale() * 0.8f );
			break;
		default:
			break;
		}
		return;  
	case WM_KEYUP:  
		switch (wParam)
		{
		case VK_SPACE:
			if( pSprite->getAnimation() )
			{
				if( pSprite->getAnimation()->IsPause() )
				{
					std::list< string > listAnimationName;
					pSprite->getAnimation()->GetAnimationList( listAnimationName );
					if( !listAnimationName.empty() )
						pSprite->getAnimation()->Play( listAnimationName.begin()->c_str() );
				}
				else
				{
					pSprite->getAnimation()->Pause();
				}
			}
			break;
		default:
			break;
		}
		return;
	default:
		return;
	}
}
//-------------------------------------------------------------------------
bool BaseLayer::CreateUI()
{
	CCLabelTTF* pControlInfo1 = CCLabelTTF::create( A2U("WSAD����λ��,Space��ͣ����").c_str(), "Arial", 20 );
	pControlInfo1->setAnchorPoint(ccp(0.0f, 0.5f));
	pControlInfo1->setColor( ccRED );
	pControlInfo1->setPosition( ccp( 20, SCERRN_HEIGHT - 40 ) );
	this->addChild( pControlInfo1 );
	CCLabelTTF* pControlInfo2 = CCLabelTTF::create( A2U("���ϼ�ͷ�Ŵ�,���¼�ͷ��С").c_str(), "Arial", 20 );
	pControlInfo2->setAnchorPoint(ccp(0.0f, 0.5f));
	pControlInfo2->setColor( ccRED );
	pControlInfo2->setPosition( ccp( 20, SCERRN_HEIGHT - 65 ) );
	this->addChild( pControlInfo2 );
	CCLabelTTF* pControlInfo3 = CCLabelTTF::create( A2U("�·������б�ɵ�����䶯��").c_str(), "Arial", 20 );
	pControlInfo3->setAnchorPoint(ccp(0.0f, 0.5f));
	pControlInfo3->setColor( ccRED );
	pControlInfo3->setPosition( ccp( 20, SCERRN_HEIGHT - 90 ) );
	this->addChild( pControlInfo3 );

	FKCW_UI_MenuItemColor* pBtn = FKCW_UI_MenuItemColor::Create( ccc4( 255, 255, 0, 0 ),
		ccc4( 255, 128, 0, 0 ), ccc4( 255, 255, 0, 0 ), this, 
		menu_selector(BaseLayer::OnChangeBGColor) );
	pBtn->setContentSize( CCSizeMake(50, 50) );
	CCMenu* pMenu = CCMenu::create( pBtn, NULL );
	pMenu->alignItemsVertically();
	pMenu->setPosition( ccp( SCREEN_CENTER_POS_X + 150, SCERRN_HEIGHT - 100 ));
	this->addChild( pMenu );

	m_pBonesArmasNumLabel = CCLabelTTF::create( A2U("������Ϣ").c_str(), "Arial", 26 );
	m_pBonesArmasNumLabel->setPosition( ccp( SCREEN_CENTER_POS_X, 30 ) );
	this->addChild( m_pBonesArmasNumLabel );

	m_pDBFileLabel = CCLabelTTF::create( A2U("����DragonBones�ļ�").c_str(), "Arial", 20 );
	m_pDBFileLabel->setAnchorPoint( ccp(0.0f, 0.5f) );
	m_pDBFileLabel->setPosition( ccp( SCREEN_CENTER_POS_X-250, SCERRN_HEIGHT - 40 ) );
	this->addChild( m_pDBFileLabel );

	m_pActionListMenu = CCMenu::create();
	m_pActionListMenu->setPosition( ccp(0,0) );
	this->addChild( m_pActionListMenu );

	CCMenu* pSelFileMenu = CCMenu::create();
	pSelFileMenu->setPosition(CCPointZero);
	this->addChild(pSelFileMenu);

	CCMenuItemImage* pSelFileBtn = CCMenuItemImage::create( s_szButtonNormalPath, s_szButtonPressPath);
	pSelFileBtn->setTarget(this, menu_selector(BaseLayer::OnSelDBFile));
	pSelFileBtn->setPosition( ccp( SCREEN_CENTER_POS_X, SCERRN_HEIGHT - 100 ));
	pSelFileMenu->addChild(pSelFileBtn);

	CCLabelTTF* pBtnLabel = CCLabelTTF::create( A2U("���������ļ�").c_str(), "Arial", 26 );
	pBtnLabel->setPosition( ccp( SCREEN_CENTER_POS_X, SCERRN_HEIGHT - 100 ) );
	pBtnLabel->setColor( ccRED );
	this->addChild( pBtnLabel );

	return true;
}
//-------------------------------------------------------------------------
// ��ʾ���������
void BaseLayer::UpdateBoneNum()
{
	if( m_pDBSprite == NULL )
		return;
	if( m_pDBSprite->GetDBNode() == NULL )
		return;
	if( m_pDBSprite->GetDBNode()->GetArmature() == NULL )
		return;
	// ��ʾ������
	int nTotalBoneNum = 0;
	int nArmatureNum = 1;
	unsigned int nMainBoneNum = m_pDBSprite->GetDBNode()->GetArmature()->m_vecBoneList.size();	// ���Ǽ���
	nTotalBoneNum += nMainBoneNum;
	// �����ӹǼ�
	for( unsigned int i = 0; i < nMainBoneNum; ++i )
	{
		CBone* pSubBone = m_pDBSprite->GetDBNode()->GetArmature()->m_vecBoneList[i];
		if( pSubBone != NULL )
		{
			list<CSlot*> slotList = pSubBone->GetSlots();
			list<CSlot*>::iterator slotIte = slotList.begin();
			for( ; slotIte != slotList.end(); ++slotIte )
			{
				vector<IObject*> vecObj = (*slotIte)->GetDisplayList();
				for( unsigned int j = 0; j < vecObj.size(); ++j )
				{
					if( dynamic_cast<CArmature*>(vecObj[j]) )
					{
						nTotalBoneNum += static_cast<CArmature*>(vecObj[j])->m_vecBoneList.size();
						nArmatureNum++;
					}
				}
			}
		}
	}

	char szInfo[128];
	memset( szInfo, 0, 128 );
	sprintf( szInfo, "��������: %d, Armature����: %d", nTotalBoneNum, nArmatureNum );
	m_pBonesArmasNumLabel->setString( A2U(szInfo).c_str() );
}
//-------------------------------------------------------------------------
// ��ʾ���鶯����
void BaseLayer::UpdateFileName()
{
	if( m_pDBSprite == NULL )
		return;
	string strFileName = m_pDBSprite->getFileName();
	if( strFileName.empty() )
		return;

	m_pDBFileLabel->setString( A2U(strFileName.c_str()).c_str() );
}
//-------------------------------------------------------------------------
// ��ʾ���鶯���б�
void BaseLayer::UpdateActionList()
{
	static CCPoint s_UpBtnPos = ccp( 150, SCERRN_HEIGHT - 180 );
	// ����ȫ������
	m_pActionListMenu->removeAllChildrenWithCleanup( true );

	CCPoint tagBeginPos = s_UpBtnPos;
	if( m_pDBSprite->getAnimation() == NULL )
	{
		CCMenuItemFont* p = CCMenuItemFont::create( A2U("�޶���").c_str(), this, 
			NULL );
		p->setPosition( tagBeginPos );
		m_pActionListMenu->addChild( p );
		return;
	}
	std::list< string > listAnimationName;
	m_pDBSprite->getAnimation()->GetAnimationList( listAnimationName );
	if( listAnimationName.empty() )
	{
		CCMenuItemFont* p = CCMenuItemFont::create( A2U("�޶���").c_str(), this, 
			NULL );
		p->setPosition( tagBeginPos );
		m_pActionListMenu->addChild( p );
		return;
	}

	for( std::list<string>::iterator Ite = listAnimationName.begin();
		Ite != listAnimationName.end();
		++Ite )
	{
		CCMenuItemFont* p = CCMenuItemFont::create( Ite->c_str(), this, 
			menu_selector(BaseLayer::OnSelActionBtn) );
		p->setPosition( tagBeginPos );
		tagBeginPos.y -= 34;
		m_pActionListMenu->addChild( p );
	}
}
//-------------------------------------------------------------------------
// ���²��Ŷ�����ǩ
void BaseLayer::OnSelActionBtn(CCObject* pSender )
{
	CCMenuItemFont* p = ( CCMenuItemFont* )pSender;
	string strActionName = dynamic_cast<CCLabelProtocol*>(p->getLabel())->getString();
	if( m_pDBSprite->getAnimation() == NULL )
		return;
	m_pDBSprite->getAnimation()->Play( strActionName );
}
//-------------------------------------------------------------------------
// ѡ����DB�ļ�
void BaseLayer::OnSelDBFile(CCObject* sender)
{
	// ���֮ǰ��
	if( m_pDBSprite != NULL )
	{
		removeChild( m_pDBSprite );
		delete m_pDBSprite;
		m_pDBSprite = NULL;
	}

	string strDBFile;
	strDBFile.clear();

	OPENFILENAME ofn;			// �����Ի���ṹ��     
	wchar_t szFile[MAX_PATH];	// �����ȡ�ļ����ƵĻ�������               
	// ��ʼ��ѡ���ļ��Ի���     
	ZeroMemory(&ofn, sizeof(OPENFILENAME));    
	ofn.lStructSize = sizeof(OPENFILENAME);    
	ofn.hwndOwner = NULL;    
	ofn.lpstrFile = szFile;    
	ofn.lpstrFile[0] = '\0';   
	ofn.nMaxFile = sizeof(szFile); 
	ofn.lpstrFilter = L"skeleton�ļ�(*.xml)\0*.XML\0\0";
	ofn.nFilterIndex = 1;    
	ofn.lpstrFileTitle = NULL;    
	ofn.nMaxFileTitle = 0;    
	ofn.lpstrInitialDir = NULL;    
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	// ��ʾ��ѡ���ļ��Ի���     
	if ( GetOpenFileName(&ofn) )    
	{ 
		strDBFile = Tchar2String(szFile);
		// �����µ�DB�ļ�
		m_pDBSprite = new CCocos2dxDBSprite();
		if( m_pDBSprite == NULL )
			return;
		m_pDBSprite->setTag( SPIRTE_TAG );
		if( !m_pDBSprite->create( strDBFile.c_str() ) )
		{
			delete m_pDBSprite;
			m_pDBSprite = NULL;
			return;
		}
		m_pDBSprite->setPosition( SCREEN_CENTER_POS + ccp(0, -200) );
		this->addChild( m_pDBSprite );
	}

	// ��ʾ���������
	UpdateBoneNum();

	// ��ʾ���鶯����
	UpdateFileName();

	// ��ʾ���鶯���б�
	UpdateActionList();
}
//-----------------------------------------------------------------
// ����������ɫ
void BaseLayer::OnChangeBGColor(CCObject* sender)
{
	if( m_pBackgroundLayer )
		m_pBackgroundLayer->setColor( ccc3( FKCW_Base_Utils::RandomInRange(5, 255),
		FKCW_Base_Utils::RandomInRange(5, 255),
		FKCW_Base_Utils::RandomInRange(5, 255) ) );
}
//-----------------------------------------------------------------
// CTestAnimCallbackHandler
//-----------------------------------------------------------------
void CTestAnimCallbackHandler::OnAnimaitonCallback( const SAnimationCallbackInfo& p_tagInfo, void* p_pContext )
{
	FKLOG("�ص��������� = %s �ص��� = %s", p_tagInfo.m_szActName, p_tagInfo.m_szName );
}
//-------------------------------------------------------------------------