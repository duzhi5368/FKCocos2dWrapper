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
#include <Shlobj.h>
//-------------------------------------------------------------------------
USING_NS_CC;
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
    scene->addChild(layer);
    return scene;
}
//-------------------------------------------------------------------------
BaseLayer::BaseLayer()
{
	m_pImage = NULL;
	m_nZipRatio = 7;
	m_nJpegRatio = 75;
	m_szSingleFile.clear();
	m_szSrcDir.clear();
	m_szDstDir.clear();
	m_szPreviewFile.clear();
	m_bIsOpeningDir			= false;

	m_pRootWindow			= NULL;

	m_pZipSlider			= NULL;
	m_pZipRatioValue		= NULL;
	m_pJpegSlider			= NULL;
	m_pJpegRatioValue		= NULL;

	m_pSingleFileEdit		= NULL;
	m_pSelSingleFileBtn		= NULL;
	m_pConvertFileBtn		= NULL;

	m_pSrcDirEdit			= NULL;
	m_pDstDirEdit			= NULL;
	m_pConvertDirBtn		= NULL;
	m_pSelSrcDirBtn			= NULL;
	m_pSelDstDirBtn			= NULL;
	m_pPreviewFileEdit		= NULL;
	m_pSelPreviewFileBtn	= NULL;
	m_pPreviewFileBtn		= NULL;

	m_pPreviewSprite		= NULL;
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

	m_pRootWindow = FKCW_UIWidget_WidgetWindow::create();
	m_pRootWindow->setMultiTouchEnabled(true);
	addChild(m_pRootWindow);

	m_pPreviewSprite = CCSprite::create( s_szSmallPanelPath );
	m_pPreviewSprite->setPosition( ccp( SCERRN_WIDTH - 512.0f, SCREEN_CENTER_POS_Y));
	m_pRootWindow->addChild( m_pPreviewSprite );

	if( !InitUI() )
	{
		return false;
	}
	else
	{
		FKLOG("��ʼ��UI���");
	}

	// ����������Ҫ�������LoadConfig()��InitConfig()��ȥÿ����·�����鷳
    
    return true;
}
//-------------------------------------------------------------------------
bool BaseLayer::InitUI()
{
	{
		FKCW_UIWidget_Layout* pLayout = FKCW_UIWidget_Layout::create(CCSize(465,140));
		pLayout->setPosition(SCREEN_LEFT_UP_POS+ccp( 80, -120));
		pLayout->setAnchorPoint( ccp(0.0f, 1.0f) );
		pLayout->setContentSize(CCSize(465,140));
		pLayout->setBackgroundImage(s_szBackground1Path);
		m_pRootWindow->addChild(pLayout);

		FKCW_UIWidget_Label* pRatioTile = FKCW_UIWidget_Label::create(A2U("============�� ѹ�����趨 ��============").c_str(), "Atlas", 26.0f);
		pRatioTile->setAnchorPoint( ccp(0.0f, 0.5f) );
		pRatioTile->setPosition(ccp(-20, 210));
		pLayout->addChild(pRatioTile);

		FKCW_UIWidget_Label* pZipRatioInfo = FKCW_UIWidget_Label::create(A2U("Zipѹ����,��ֵԽ��,�ļ�ԽС,����ѹʱ��Խ��").c_str(), "Atlas", 26.0f);
		pZipRatioInfo->setAnchorPoint( ccp(0.0f, 0.5f) );
		pZipRatioInfo->setPosition(ccp(-40, 170));
		pLayout->addChild(pZipRatioInfo);

		m_pZipSlider = CCControlSlider::create( s_szProgressBGPath,s_szProgressPath ,s_szSliderPath );
		m_pZipSlider->setAnchorPoint(ccp(0.0f, 0.5f));
		m_pZipSlider->setMinimumValue(1);
		m_pZipSlider->setMaximumValue(9);
		m_pZipSlider->setValue( 7 );
		m_pZipSlider->setScaleX(0.8f);
		m_pZipSlider->setPosition(ccp(-40, 130));
		m_pZipSlider->addTargetWithActionForControlEvents(this, 
			cccontrol_selector(BaseLayer::onChangeZipRatio), 
			CCControlEventValueChanged);
		pLayout->addChild( m_pZipSlider );

		m_pZipRatioValue = FKCW_UIWidget_Label::create(A2U("ѹ����:7").c_str(), "Atlas", 26.0f);
		m_pZipRatioValue->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pZipRatioValue->setPosition(ccp(380, 130));
		pLayout->addChild(m_pZipRatioValue);

		FKCW_UIWidget_Label* pJpegRatioInfo = FKCW_UIWidget_Label::create(A2U("Jpegѹ����,��ֵԽС,�ļ�ԽС,��ͼƬƷ��Խ��").c_str(), "Atlas", 26.0f);
		pJpegRatioInfo->setAnchorPoint( ccp(0.0f, 0.5f) );
		pJpegRatioInfo->setPosition(ccp(-40, 85));
		pLayout->addChild(pJpegRatioInfo);

		m_pJpegSlider = CCControlSlider::create( s_szProgressBGPath,s_szProgressPath ,s_szSliderPath );
		m_pJpegSlider->setAnchorPoint(ccp(0.0f, 0.5f));
		m_pJpegSlider->setMinimumValue(50);
		m_pJpegSlider->setMaximumValue(100);
		m_pJpegSlider->setValue( 75 );
		m_pJpegSlider->setScaleX(0.8f);
		m_pJpegSlider->setPosition(ccp(-40, 45));
		m_pJpegSlider->addTargetWithActionForControlEvents(this, 
			cccontrol_selector(BaseLayer::onChangeJpegRatio), 
			CCControlEventValueChanged);
		pLayout->addChild( m_pJpegSlider );

		m_pJpegRatioValue = FKCW_UIWidget_Label::create(A2U("ѹ����:75").c_str(), "Atlas", 26.0f);
		m_pJpegRatioValue->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pJpegRatioValue->setPosition(ccp( 380, 45));
		pLayout->addChild(m_pJpegRatioValue);
	}
	{
		FKCW_UIWidget_Layout* pLayout = FKCW_UIWidget_Layout::create();
		pLayout->setPosition(SCREEN_LEFT_UP_POS+ccp( 63, -360));
		pLayout->setAnchorPoint( ccp(0.0f, 1.0f) );
		pLayout->setContentSize(CCSize(500,320));
		pLayout->setBackgroundImage(s_szBackground1Path);
		m_pRootWindow->addChild(pLayout);

		FKCW_UIWidget_Label* pSingleFileTile = FKCW_UIWidget_Label::create(A2U("=============�� ���ļ�ת�� ��=============").c_str(), "Atlas", 26.0f);
		pSingleFileTile->setAnchorPoint( ccp(0.0f, 0.5f) );
		pSingleFileTile->setPosition(ccp(-20, 300));
		pLayout->addChild(pSingleFileTile);

		CCScale9Sprite* pSingleEditBoxBG = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pSingleFileEdit = CCEditBox::create(CCSizeMake(485, 46), pSingleEditBoxBG );
		m_pSingleFileEdit->setPosition( ccp(40, 260));
		m_pSingleFileEdit->setFontName("Atlas");
		m_pSingleFileEdit->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pSingleFileEdit->setFontSize( 18 );
		m_pSingleFileEdit->setText(A2U("��������Դ�ļ�·��").c_str());
		pLayout->addChild( m_pSingleFileEdit );

		m_pSelSingleFileBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(60, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pSelSingleFileBtn->setPosition(ccp(10, 260));
		m_pSelSingleFileBtn->setUserTag( 1 );
		m_pSelSingleFileBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onOpenFile));
		m_pSelSingleFileBtn->initText("...", "Atlas", 26);
		pLayout->addChild( m_pSelSingleFileBtn);

		m_pConvertFileBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(150, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pConvertFileBtn->setPosition(ccp(240, 210));
		m_pConvertFileBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onConvertFile));
		m_pConvertFileBtn->initText(A2U("���ļ�ת��").c_str(), "Atlas", 26);
		pLayout->addChild( m_pConvertFileBtn);

		FKCW_UIWidget_Label* pFileDirTile = FKCW_UIWidget_Label::create(A2U("===========�� �ļ�������ת�� ��===========").c_str(), "Atlas", 26.0f);
		pFileDirTile->setAnchorPoint( ccp(0.0f, 0.5f) );
		pFileDirTile->setPosition(ccp(-20, 170));
		pLayout->addChild(pFileDirTile);

		CCScale9Sprite* pSrcDirEditBoxBG = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pSrcDirEdit = CCEditBox::create(CCSizeMake(485, 46), pSrcDirEditBoxBG );
		m_pSrcDirEdit->setPosition( ccp(40, 125));
		m_pSrcDirEdit->setFontName("Atlas");
		m_pSrcDirEdit->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pSrcDirEdit->setFontSize( 18 );
		m_pSrcDirEdit->setText(A2U("��������Դ�ļ���·��").c_str());
		pLayout->addChild( m_pSrcDirEdit );

		m_pSelSrcDirBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(60, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pSelSrcDirBtn->setPosition(ccp(10, 125));
		m_pSelSrcDirBtn->setUserTag( 1 );
		m_pSelSrcDirBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onOpenDir));
		m_pSelSrcDirBtn->initText("...", "Atlas", 26);
		pLayout->addChild( m_pSelSrcDirBtn);

		CCScale9Sprite* pDstDirEditBoxBG = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pDstDirEdit = CCEditBox::create(CCSizeMake(485, 46), pDstDirEditBoxBG );
		m_pDstDirEdit->setPosition( ccp(40, 75));
		m_pDstDirEdit->setFontName("Atlas");
		m_pDstDirEdit->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pDstDirEdit->setFontSize( 18 );
		m_pDstDirEdit->setText(A2U("��������Ŀ���ļ���·��").c_str());
		pLayout->addChild( m_pDstDirEdit );

		m_pSelDstDirBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(60, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pSelDstDirBtn->setPosition(ccp(10, 75));
		m_pSelDstDirBtn->setUserTag( 2 );
		m_pSelDstDirBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onOpenDir));
		m_pSelDstDirBtn->initText("...", "Atlas", 26);
		pLayout->addChild( m_pSelDstDirBtn);

		m_pConvertDirBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(180, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pConvertDirBtn->setPosition(ccp(240, 25));
		m_pConvertDirBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onConvertDir));
		m_pConvertDirBtn->initText(A2U("�����ļ�ת��").c_str(), "Atlas", 26);
		pLayout->addChild( m_pConvertDirBtn);
	}
	{
		FKCW_UIWidget_Layout* pLayout = FKCW_UIWidget_Layout::create();
		pLayout->setPosition(SCREEN_LEFT_UP_POS+ccp( 63, -690));
		pLayout->setAnchorPoint( ccp(0.0f, 1.0f) );
		pLayout->setContentSize(CCSize(500,320));
		pLayout->setBackgroundImage(s_szBackground1Path);
		m_pRootWindow->addChild(pLayout);

		FKCW_UIWidget_Label* pPreviewTile = FKCW_UIWidget_Label::create(A2U("============�� �鿴ͼƬ�ļ� ��============").c_str(), "Atlas", 26.0f);
		pPreviewTile->setAnchorPoint( ccp(0.0f, 0.5f) );
		pPreviewTile->setPosition(ccp(-20, 300));
		pLayout->addChild(pPreviewTile);

		CCScale9Sprite* pSingleEditBoxBG = CCScale9Sprite::create(s_szSprite9Btn1Path);
		m_pPreviewFileEdit = CCEditBox::create(CCSizeMake(485, 46), pSingleEditBoxBG );
		m_pPreviewFileEdit->setPosition( ccp(40, 260));
		m_pPreviewFileEdit->setFontName("Atlas");
		m_pPreviewFileEdit->setAnchorPoint( ccp(0.0f, 0.5f) );
		m_pPreviewFileEdit->setFontSize( 18 );
		m_pPreviewFileEdit->setText(A2U("��������Ԥ���ļ�·��").c_str());
		pLayout->addChild( m_pPreviewFileEdit );

		m_pSelPreviewFileBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(60, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pSelPreviewFileBtn->setPosition(ccp(10, 260));
		m_pSelPreviewFileBtn->setUserTag( 2 );
		m_pSelPreviewFileBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onOpenFile));
		m_pSelPreviewFileBtn->initText("...", "Atlas", 26);
		pLayout->addChild( m_pSelPreviewFileBtn);

		m_pPreviewFileBtn = FKCW_UIWidget_Button::createWith9Sprite(CCSize(180, 46),
			s_szSprite9Btn1Path, s_szSprite9Btn2Path );
		m_pPreviewFileBtn->setPosition(ccp(240, 210));
		m_pPreviewFileBtn->setOnClickListener(this, fkcw_uiwidget_click_selector(BaseLayer::onPreviewFile));
		m_pPreviewFileBtn->initText(A2U("ͼƬ�ļ�Ԥ��").c_str(), "Atlas", 26);
		pLayout->addChild( m_pPreviewFileBtn);
	}


	return true;
}
//-------------------------------------------------------------------------
// �����ĳ��һ�ļ�
void BaseLayer::onOpenFile(CCObject* pSender)
{
	int nType = ((FKCW_UIWidget_Button*)pSender)->getUserTag();
	if( nType != 1 && nType != 2 )
		return;
	OPENFILENAME ofn;			// �����Ի���ṹ��     
	wchar_t szFile[MAX_PATH];	// �����ȡ�ļ����ƵĻ�������               
	// ��ʼ��ѡ���ļ��Ի���     
	ZeroMemory(&ofn, sizeof(OPENFILENAME));    
	ofn.lStructSize = sizeof(OPENFILENAME);    
	ofn.hwndOwner = NULL;    
	ofn.lpstrFile = szFile;    
	ofn.lpstrFile[0] = '\0';   
	ofn.nMaxFile = sizeof(szFile); 
	if( nType == 1 )
	{
		ofn.lpstrFilter = L"PNG�ļ�(*.png)\0*.PNG\0JPG�ļ�(*.jpg)\0*.JPG\0BMP�ļ�(*.bmp)\0*.BMP\0FKP�ļ�(*.fkp)\0*.FKP\0\0";
	}
	else
	{
		ofn.lpstrFilter = L"FKP�ļ�(*.fkp)\0*.FKP\0PNG�ļ�(*.png)\0*.PNG\0JPG�ļ�(*.jpg)\0*.JPG\0BMP�ļ�(*.bmp)\0*.BMP\0\0";
	}
	ofn.nFilterIndex = 1;    
	ofn.lpstrFileTitle = NULL;    
	ofn.nMaxFileTitle = 0;    
	ofn.lpstrInitialDir = NULL;    
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	// ��ʾ��ѡ���ļ��Ի���     
	if ( GetOpenFileName(&ofn) )    
	{    
		if( nType == 1 )
		{    
			m_szSingleFile = Tchar2String(szFile);
			m_pSingleFileEdit->setText( A2U(m_szSingleFile.c_str()).c_str() );
		}
		else
		{
			m_szPreviewFile = Tchar2String(szFile);
			m_pPreviewFileEdit->setText( A2U(m_szPreviewFile.c_str()).c_str() );
		}
	}
}
//-------------------------------------------------------------------------
// ��ĳ�ļ���
void BaseLayer::onOpenDir(CCObject* pSender)
{
	int nType = ((FKCW_UIWidget_Button*)pSender)->getUserTag();
	if( nType != 1 && nType != 2 )
		return;
	if( m_bIsOpeningDir )
		return;

	wchar_t szBuffer[MAX_PATH] = {0}; 
	BROWSEINFO bi;     
	bi.hwndOwner = NULL;     
	bi.pidlRoot = NULL;     
	bi.pszDisplayName = szBuffer;          
	bi.ulFlags = 0;     
	bi.lpfn = NULL;     
	bi.lParam = 0;     
	bi.iImage = 0;

	if( nType == 1 )
	{
		m_szSrcDir.clear();
		bi.lpszTitle = L"��ѡ����Ҫת����ԴĿ¼��";
	}
	else
	{
		m_szDstDir.clear();
		bi.lpszTitle = L"��ѡ��ת�����Ŀ��Ŀ¼��";
	}

	m_bIsOpeningDir = true;	// ��¼flag����ֹ����ļ���ѡ�񴰿ڵ���
	//����ѡ��Ŀ¼�Ի���  
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);     
	if(lp && SHGetPathFromIDList(lp, szBuffer))
	{
		if( nType == 1 )
		{
			m_szSrcDir = Tchar2String(szBuffer);
			m_pSrcDirEdit->setText( A2U(m_szSrcDir.c_str()).c_str() );
		}
		else
		{
			m_szDstDir = Tchar2String(szBuffer);
			m_pDstDirEdit->setText( A2U(m_szDstDir.c_str()).c_str() );
		}
	}
	m_bIsOpeningDir = false;
}
//-------------------------------------------------------------------------
// ���е��ļ�ת��
void BaseLayer::onConvertFile(CCObject* pSender)
{
	if( m_pImage != NULL )
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	m_szSingleFile = m_pSingleFileEdit->getText();
	if( m_szSingleFile.empty() )
	{
		_MessageInfo("����", "����ѡ��һ���ļ�");
		return;
	}

	// �����ļ�
	m_pImage = new CFKImage;
	if( (m_pImage == NULL) ||
		(!m_pImage->Load( m_szSingleFile.c_str(), eFormats_Unknown )))
	{
		char szTmp[MAX_PATH];
		memset( szTmp, 0, MAX_PATH );
		sprintf( szTmp, "�����ļ�ʧ��: %s", A2U(m_szSingleFile.c_str()).c_str() );
		_MessageInfo("�쳣", szTmp );
		return;
	}
	else
	{
		FKLOG( "�����ļ��ɹ� - %s", A2U(m_szSingleFile.c_str()).c_str() );
	}

	// notice: ������ʱ��֧��ת����ʽΪFKP
	// ��ȡ���ĺ���ļ���
	string szDstFilePathName = _GetConvertedName( m_szSingleFile, ".fkp" );
	// ����ѹ�����ʺ�Jpeg������
	m_pImage->SetJpegQuality( m_nJpegRatio );
	m_pImage->SetZipQuality( m_nZipRatio );
	if( m_pImage->Save( szDstFilePathName.c_str(), eFormats_FKP ) )
	{
		_MessageInfo("��ʾ", "ת���ļ��ɹ�");
		FKLOG("Ŀ���ļ� : %s��Zipѹ���� : %d, Jpegѹ���� : %d", 
			szDstFilePathName.c_str(), m_nZipRatio, m_nJpegRatio );
	}
	else
	{
		_MessageInfo("����", "ת���ļ�ʧ��");
	}
}
//-------------------------------------------------------------------------
// �����ļ�������ת��
void BaseLayer::onConvertDir(CCObject* pSender)
{
	m_szSrcDir = m_pSrcDirEdit->getText();
	m_szDstDir = m_pDstDirEdit->getText();

	FKCW_Base_Utils::SystemSleep( 200 );

	// step1: �ļ��п���
	char szCopyCmd[MAX_PATH];
	memset( szCopyCmd, 0, MAX_PATH );
	sprintf( szCopyCmd,"xcopy %s %s /e",m_szSrcDir.c_str(), m_szDstDir.c_str());
	system( szCopyCmd );

	// step2: ȫ��ת��
	int nCount = 0;
	int nErrorCount = 0;
	// �ݹ�ת����ǰ֧�ֵ����ࡾ��ʱ��ת��bmp��jpg��
	__RecurrenceConvertDir( m_szDstDir.c_str(), eFormats_PNG, eFormats_FKP, nCount, nErrorCount );
	//RecurrenceConvertDir( m_szDstDir.c_str(), eFormats_JPG, eFormats_FKP, nCount, nErrorCount );
	//RecurrenceConvertDir( m_szDstDir.c_str(), eFormats_BMP, eFormats_FKP, nCount, nErrorCount );

	char szInfo[MAX_PATH];
	memset( szInfo, 0, MAX_PATH );
	sprintf( szInfo, "��ʽת����� �ɹ� %d ���ļ���ʧ�� %d ���ļ�", nCount, nErrorCount );
	_MessageInfo("��ʾ", szInfo ); 
}
//-------------------------------------------------------------------------
// ������Zipѹ������
void BaseLayer::onChangeZipRatio(CCObject* sender, CCControlEvent controlEvent)
{
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	m_nZipRatio = static_cast<int>(pSlider->getValue());
	char szZipRatioValue[16];
	memset( szZipRatioValue, 0, 16 );
	sprintf( szZipRatioValue, "ѹ����:%d", m_nZipRatio );
	m_pZipRatioValue->setString( A2U(szZipRatioValue).c_str() );
}
//-------------------------------------------------------------------------
// ������Jpegѹ������
void BaseLayer::onChangeJpegRatio(CCObject* sender, CCControlEvent controlEvent)
{
	CCControlSlider* pSlider = (CCControlSlider*)sender;
	m_nJpegRatio = static_cast<int>(pSlider->getValue());
	char szJpegRatioValue[16];
	memset( szJpegRatioValue, 0, 16 );
	sprintf( szJpegRatioValue, "ѹ����:%d", m_nJpegRatio );
	m_pJpegRatioValue->setString( A2U(szJpegRatioValue).c_str() );
}
//-------------------------------------------------------------------------
// ģ��windows��ʾ��Ϣ��������ռ����
void BaseLayer::_MessageInfo( string strTile, string strContext )
{
	_MessageInfo( strTile.c_str(), strContext.c_str() );
}
//-------------------------------------------------------------------------
void BaseLayer::_MessageInfo( const char* szTile, const char* context )
{
	CCScale9Sprite* pPanel = CCScale9Sprite::create( s_szSprite9Btn1Path );

	CCLabelTTF* pTitle = CCLabelTTF::create(A2U(szTile).c_str(), "Arial", 30 );
	pTitle->setColor( ccRED );

	CCLabelTTF* pInfo = CCLabelTTF::create(A2U(context).c_str(), "Arial", 26 );
	pInfo->setColor( ccWHITE );

	int nWidth = pInfo->getContentSize().width +30;
	nWidth = 400 > nWidth ? 400 : nWidth;
	pPanel->setContentSize( CCSize( nWidth, 150 ) );
	pPanel->setPosition( SCREEN_CENTER_POS + ccp(0, 50) );

	pTitle->setPosition( ccp( pPanel->getContentSize().width / 2 ,
		pPanel->getContentSize().height / 2 + 30 ) );
	pPanel->addChild( pTitle );

	pInfo->setPosition( ccp( pPanel->getContentSize().width / 2 , 
		pPanel->getContentSize().height / 2 - 30 ) );
	pPanel->addChild( pInfo );

	CCNode* pContextNode = CCNode::create();
	pContextNode->addChild( pPanel );

	// ��ҪaddChild
	FKCW_UI_ToastLayer* p = FKCW_UI_ToastLayer::Create( this, pContextNode, 0, 2.0f );

	// ��¼FKLOG
	FKLOG( "[%s] - %s", szTile, context );
}
//-------------------------------------------------------------------------
// ��ȡһ���ļ���ʽ�����ĺ�׺��
string BaseLayer::_GetConvertedName( string strSrcFilePathName, string strExt )
{
	string srcFilePath = strSrcFilePathName;
	string srcPath;
	string srcFile;
	string srcExt;
	FKCW_Base_Utils::ParseFilePathName( srcFilePath, srcPath, srcFile, srcExt );
	string szDstFilePath = srcPath + "\\" + srcFile + strExt;
	return szDstFilePath;
}
//-------------------------------------------------------------------------
// �ݹ��ļ��н��и�ʽת��
bool BaseLayer::__RecurrenceConvertDir( const char* szPath, int p_nSrcType,
							int p_nDstType, int& p_nFileCount, int& p_nFileError )
{
	if( m_pImage )
	{
		delete m_pImage;
		m_pImage = NULL;
	}
	m_pImage = new CFKImage;
	m_pImage->SetJpegQuality( m_nJpegRatio );
	m_pImage->SetZipQuality( m_nZipRatio );

	string szNewExt = "";
	switch (p_nDstType)
	{
	case eFormats_BMP:
		szNewExt = ".bmp";
		break;
	case eFormats_JPG:
		szNewExt = ".jpg";
		break;
	case eFormats_PNG:
		szNewExt = ".png";
		break;
	case eFormats_FKP:
		szNewExt = ".fkp";
		break;
	default:
		return false;
		break;
	}

	WIN32_FIND_DATAA FindData;
	HANDLE hError;
	char FilePathName[1024];
	// ����·��
	char FullPathName[1024];
	strcpy(FilePathName, szPath);
	strcat(FilePathName, "\\*.*");
	hError = FindFirstFileA(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		_MessageInfo("����", "�����ļ���ʧ��");
		return false;
	}
	while(::FindNextFileA(hError, &FindData))
	{
		// ����.��..
		if (strcmp(FindData.cFileName, ".") == 0 
			|| strcmp(FindData.cFileName, "..") == 0 )
		{
			continue;
		}

		// ��������·��
		sprintf(FullPathName, "%s\\%s", szPath,FindData.cFileName);
		string szFilePath = string(FullPathName);
		string srcPath;
		string srcFile;
		string srcExt;
		FKCW_Base_Utils::ParseFilePathName( szFilePath, srcPath, srcFile, srcExt );

		switch( p_nSrcType )
		{
		case eFormats_PNG:
			if( strcmp( srcExt.c_str(), "png" ) == 0 || 
				strcmp( srcExt.c_str(), "PNG" ) == 0)
			{
				if( !m_pImage->Load( szFilePath.c_str(), eFormats_Unknown ))
				{
					FKLOG( "��ȡ�ļ�ʧ�� %s", szFilePath.c_str() );
					continue;
				}
				if( !m_pImage->Save( string(srcPath + "\\" + srcFile + szNewExt).c_str(), p_nDstType ) )
				{
					FKLOG( "�����ļ�ʧ�� %s", string(srcPath + "\\" + srcFile + szNewExt).c_str() );
					p_nFileError++;
					continue;
				}
				else
				{
					FKLOG( "�� %d �ļ� ת���ļ��ɹ� %s", p_nFileCount+1,
						string(srcPath + "\\" + srcFile + szNewExt).c_str() );

					// ɾ��Դ�ļ�
					DeleteFileA( FullPathName );
					p_nFileCount++;
				}
			}
			break;
		case eFormats_JPG:
			if( strcmp( srcExt.c_str(), "jpg" ) == 0 || 
				strcmp( srcExt.c_str(), "JPG" ) == 0  )
			{
				if( !m_pImage->Load( szFilePath.c_str(), eFormats_Unknown ))
				{
					FKLOG( "��ȡ�ļ�ʧ�� %s", szFilePath.c_str() );
					continue;
				}
				if( !m_pImage->Save( string(srcPath + "\\" + srcFile + szNewExt).c_str(), p_nDstType ) )
				{
					FKLOG( "�����ļ�ʧ�� %s", string(srcPath + "\\" + srcFile + szNewExt).c_str() );
					p_nFileError++;
					continue;
				}
				else
				{
					FKLOG( "�� %d �ļ� ת���ļ��ɹ� %s", p_nFileCount+1,
						string(srcPath + "\\" + srcFile + szNewExt).c_str() );

					// ɾ��Դ�ļ�
					DeleteFileA( FullPathName );
					p_nFileCount++;
				}
			}
			break;
		case eFormats_BMP:
			if( strcmp( srcExt.c_str(), "bmp" ) == 0 || 
				strcmp( srcExt.c_str(), "BMP" ) == 0)
			{
				if( !m_pImage->Load( szFilePath.c_str(), eFormats_Unknown ))
				{
					FKLOG( "��ȡ�ļ�ʧ�� %s", szFilePath.c_str() );
					continue;
				}
				if( !m_pImage->Save( string(srcPath + "\\" + srcFile + szNewExt).c_str(), p_nDstType ) )
				{
					FKLOG( "�����ļ�ʧ�� %s", string(srcPath + "\\" + srcFile + szNewExt).c_str() );
					p_nFileError++;
					continue;
				}
				else
				{
					FKLOG( "�� %d �ļ� ת���ļ��ɹ� %s", p_nFileCount+1,
						string(srcPath + "\\" + srcFile + szNewExt).c_str() );

					// ɾ��Դ�ļ�
					DeleteFileA( FullPathName );
					p_nFileCount++;
				}
			}
			break;
		case eFormats_FKP:
			if( strcmp( srcExt.c_str(), "fkp" ) == 0 || 
				strcmp( srcExt.c_str(), "FKP" ) == 0 )
			{
				if( !m_pImage->Load( szFilePath.c_str(), eFormats_Unknown ))
				{
					FKLOG( "��ȡ�ļ�ʧ�� %s", szFilePath.c_str() );
					continue;
				}
				if( !m_pImage->Save( string(srcPath + "\\" + srcFile + szNewExt).c_str(), p_nDstType ) )
				{
					FKLOG( "�����ļ�ʧ�� %s", string(srcPath + "\\" + srcFile + szNewExt).c_str() );
					p_nFileError++;
					continue;
				}
				else
				{
					FKLOG( "�� %d �ļ� ת���ļ��ɹ� %s", p_nFileCount+1,
						string(srcPath + "\\" + srcFile + szNewExt).c_str() );

					// ɾ��Դ�ļ�
					DeleteFileA( FullPathName );
					p_nFileCount++;
				}
			}
			break;
		default:
			break;
		}

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			__RecurrenceConvertDir(FullPathName, p_nSrcType, p_nDstType, p_nFileCount, p_nFileError );
		}
	}
	return true;
}
//-------------------------------------------------------------------------
// Ԥ��ĳһͼƬ�ļ�
void BaseLayer::onPreviewFile(CCObject* pSender)
{
	if( m_pPreviewSprite == NULL )
		return;

	m_szPreviewFile = m_pPreviewFileEdit->getText();

	CCTexture2D* pTex = CCTextureCache::sharedTextureCache()->addImage(m_szPreviewFile.c_str());
	if( pTex == NULL )
	{
		_MessageInfo("����", "��������ͼƬʧ��");
		return;
	}
	m_pPreviewSprite->setTexture( pTex );

	CCSize oldSize = m_pPreviewSprite->getContentSize();
	CCSize newSize = pTex->getContentSize();

	float fXScale = newSize.width / oldSize.width;
	float fYScale = newSize.height / oldSize.height;
	m_pPreviewSprite->setScaleX( fXScale );
	m_pPreviewSprite->setScaleY( fYScale );
}
//-------------------------------------------------------------------------