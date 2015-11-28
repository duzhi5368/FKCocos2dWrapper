#include "MainScreen.h"

CCScene* MainScreen::createScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = MainScreen::create();
	scene->addChild(layer);
	return scene;
}

MainScreen::MainScreen():
	m_pNetworkServer(NULL),
	m_isLoadConfigFile(false)
{

}

MainScreen::~MainScreen()
{
	serverClose();
	clientClose();
}

bool MainScreen::init()
{
	if (!CCLayerColor::initWithColor(ccc4(45, 45, 48, 255)))
		return false;

	initUI();

	return true;
}

void MainScreen::initUI()
{
	/******************************************************************************************************************/
	m_pWindow = FKCW_UIWidget_WidgetWindow::create();
	this->addChild(m_pWindow);

	CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

	/******************************************************************************************************************/
	
	//�����ļ�View
	FileView* pFileView = FileView::create();
	pFileView->setTag(ID_FILE_VIEW);
	pFileView->setPosition(ccp(2, windowSize.height - 80));
	pFileView->setZOrder(1000);
	m_pWindow->addChild(pFileView);
	pFileView->setDelegate(this);

	/******************************************************************************************************************/
	
	//������Ϣ�б�(���)
	MessageListView* pMessageListView = MessageListView::create();
	pMessageListView->setTag(ID_MESSAGE_LIST_VIEW);
	pMessageListView->setAnchorPoint(ccp(0, 0));
	pMessageListView->setPosition(ccp(0, 7));
	m_pWindow->addChild(pMessageListView);
	pMessageListView->setDelegate(this);

	//���������б�(�Ҳ�)
	AttributeListView* pAttributeListView = AttributeListView::create();
	pAttributeListView->setTag(ID_ATTRIBUTE_LIST_VIEW);
	pAttributeListView->setAnchorPoint(ccp(0, 1));
	pAttributeListView->setPosition(ccp(pMessageListView->getPositionX() + pMessageListView->getContentSize().width + 5, pMessageListView->getPositionY() + pMessageListView->getContentSize().height));
	pAttributeListView->setTitle("");
	pAttributeListView->setSubTitle("");
	m_pWindow->addChild(pAttributeListView);
	pAttributeListView->setDelegate(this);
	
	//��ʾ��ǩ																								    
	FKCW_UIWidget_Label* pAttributeListViewHelpLabel = FKCW_UIWidget_Label::create(A2U("��ʾ: FBM��ʾ������������\n      FMS��ʾ������������").c_str(), "", s_iFontSizeSuperSmall);
	pAttributeListViewHelpLabel->setColor(ccc3(150, 150, 150));
	pAttributeListViewHelpLabel->setAnchorPoint(ccp(0.5, 0));
	pAttributeListViewHelpLabel->setPosition(ccp(pAttributeListView->getPositionX() + pAttributeListView->getContentSize().width/2, pAttributeListView->getPositionY()));
	m_pWindow->addChild(pAttributeListViewHelpLabel);

	//���Ա༭���
	AttributeEditView* pAttributeEditView = AttributeEditView::create();
	pAttributeEditView->setTag(ID_ATTRIBUTE_EDIT_VIEW);
	pAttributeEditView->setEnabled(false);
	pAttributeEditView->setAnchorPoint(ccp(0, 1));
	pAttributeEditView->setPosition(ccp(pAttributeListView->getPositionX(), pAttributeListView->getPositionY() - pAttributeListView->getContentSize().height - 5));
	m_pWindow->addChild(pAttributeEditView);
	pAttributeEditView->setDelegate(this);

	/******************************************************************************************************************/

	//�ͻ���LogView
	LogView* pClientLogView = LogView::create(CCSize(320, 730));
	pClientLogView->setTag(ID_CLIENT_LOG_VIEW);
	pClientLogView->setTitle(A2U("�ͻ�����־").c_str());
	pClientLogView->setAnchorPoint( ccp(0, 0) );
	pClientLogView->setPosition(ccp(pAttributeListView->getPositionX() + pAttributeListView->getContentSize().width + 10, 7));
	m_pWindow->addChild(pClientLogView);

	//�����LogView
	LogView* pServerLogView = LogView::create(CCSize(320, 730));
	pServerLogView->setTag(ID_SERVER_LOG_VIEW);
	pServerLogView->openSafeMode();
	pServerLogView->setTitle(A2U("��������־").c_str());
	pServerLogView->setAnchorPoint(ccp(0, 0));
	pServerLogView->setPosition(ccp(pClientLogView->getContentSize().width + pClientLogView->getPositionX() + 2, pClientLogView->getPositionY()));
	m_pWindow->addChild(pServerLogView);

	/******************************************************************************************************************/

	//�ͻ������ӷ��������
	IpPostView* pConnectView = IpPostView::create();
	pConnectView->setTag(ID_CONNECT_VIEW);
	pConnectView->setButtonText(A2U("����").c_str());
	pConnectView->setAnchorPoint(ccp(0, 0));
	pConnectView->setPosition(ccp(2, 825));
	m_pWindow->addChild(pConnectView);
	pConnectView->setDeleagte(this);

	//�������������
	IpPostView* pListenView = IpPostView::create();
	pListenView->setTag(ID_LISTEN_VIEW);
	pListenView->setButtonText(A2U("����").c_str());
	pListenView->setAnchorPoint(ccp(0, 0));
	pListenView->setPosition(pConnectView->getPosition() + ccp(0, -pConnectView->getContentSize().height));
	m_pWindow->addChild(pListenView);
	pListenView->setDeleagte(this);
	
	/******************************************************************************************************************/
	
	FKCW_UIWidget_Button* pSendButton = FKCW_UIWidget_Button::createWith9Sprite(CCSizeMake(pAttributeEditView->getContentSize().width, 40), 
		s_szSprite9Btn1Path, s_szSprite9Btn2Path );
	pSendButton->setTag(ID_SEND_MESSAGE_BUTTON);
	pSendButton->setAnchorPoint(ccp(0, 1));
	pSendButton->setOnClickListener(this, fkcw_uiwidget_click_selector(MainScreen::onSendButtonClick));
	pSendButton->setPosition(ccp(pAttributeEditView->getPositionX(), pAttributeEditView->getPositionY() - pAttributeEditView->getContentSize().height - 5));
	pSendButton->getLabel()->setFontSize(s_iFontSizeNormal);
	pSendButton->getLabel()->setString(A2U( "����" ).c_str());
	m_pWindow->addChild(pSendButton);
	
	pSendButton->setEnabled(false);

	/******************************************************************************************************************/
	
	//�������Ϣ��ť
	FKCW_UIWidget_Button* pAddMainMessageButton = FKCW_UIWidget_Button::createWith9Sprite(CCSizeMake(pMessageListView->getContentSize().width, 25), 
		s_szSprite9Btn1Path, s_szSprite9Btn2Path );
	pAddMainMessageButton->setTag(ID_ADD_MAIN_MESSAGE_BUTTON);
	pAddMainMessageButton->setAnchorPoint(ccp(0, 0));
	pAddMainMessageButton->setOnClickListener(this, fkcw_uiwidget_click_selector(MainScreen::onAddMainMessageButtonClick));
	pAddMainMessageButton->setPosition(ccp(pMessageListView->getPositionX(), pMessageListView->getContentSize().height + pMessageListView->getPositionY()));
	pAddMainMessageButton->getLabel()->setFontSize(s_iFontSizeSuperSmall);
	pAddMainMessageButton->getLabel()->setString(A2U( "���������" ).c_str());
	pAddMainMessageButton->setEnabled(false);
	m_pWindow->addChild(pAddMainMessageButton);
	/******************************************************************************************************************/
}

CCNode* MainScreen::getViewByID(int id)
{
	return m_pWindow->getChildByTag(id);
}

/***************************************************************************/

void MainScreen::serverListen(const char* ip, short post)
{
	if (!m_isLoadConfigFile)
	{
		MessageBox(NULL, L"������ȷ���������ļ�", L"", 0);
		return;
	}

	//��֤��ǰֻ��һ��Server
	if (m_pNetworkServer != NULL)
	{
		return;
	}

	m_pNetworkServer = new NetworkServer();
	m_pNetworkServer->registerOnMessageReceived	(this, netserver_backcall_received_selector(MainScreen::onServerMessageReceived));	//�յ���Ϣ
	m_pNetworkServer->registerOnConnected		(this, netserver_backcall_selector(MainScreen::onServerConnected));			//���ӳɹ�
	m_pNetworkServer->registerOnDisconnected	(this, netserver_backcall_selector(MainScreen::onServerDisconnected));		//����
	m_pNetworkServer->registerOnConnectedEnded	(this, netserver_backcall_selector(MainScreen::onServerConnectedEnded));		//�Ͽ�
	m_pNetworkServer->registerOnExceptionCaught	(this, netserver_backcall_selector(MainScreen::onServerExceptionCaught));	//�쳣

	m_pNetworkServer->setListenIp(ip);
	m_pNetworkServer->setListenPost(post);
	m_pNetworkServer->listen();

	IpPostView* pListenView = (IpPostView*)getViewByID(ID_LISTEN_VIEW);
	pListenView->setButtonText(A2U("�Ͽ�").c_str());

	LogView* pServerLogView = (LogView*)getViewByID(ID_SERVER_LOG_VIEW);
	pServerLogView->safeModeLog(A2U("��ʼ����..."));
}

void MainScreen::serverClose()
{
	if (m_pNetworkServer != NULL)
	{
		m_pNetworkServer->close();
		m_pNetworkServer = NULL;
	}

	IpPostView* pListenView = (IpPostView*)getViewByID(ID_LISTEN_VIEW);
	pListenView->setButtonText(A2U("����").c_str());
}

/***************************************************************************/

void MainScreen::clientConnect(const char* ip, short post)
{
	if (!m_isLoadConfigFile)
	{
		MessageBox(NULL, L"������ȷ���������ļ�", L"", 0);
		return;
	}

	FKCW_SimpleNet_InetAddress oAddres;
	oAddres.setIp(ip);
	oAddres.setPort(post);

	NetworkClient::sharedDelegate()->setInetAddress(oAddres);
	NetworkClient::sharedDelegate()->setSoTimeout(3.0f);

	NetworkClient::sharedDelegate()->registerOnConnected(this,		 netclient_backcall_selector(MainScreen::onClientConnected));
	NetworkClient::sharedDelegate()->registerOnConnectTimeout(this,  netclient_backcall_selector(MainScreen::onClientConnectTimeout));
	NetworkClient::sharedDelegate()->registerOnMessageReceived(this, netclient_backcall_received_selector(MainScreen::onClientMessageReceived));
	NetworkClient::sharedDelegate()->registerOnExceptionCaught(this, netclient_backcall_selector(MainScreen::onClientExceptionCaught));
	NetworkClient::sharedDelegate()->registerOnDisconnected(this,    netclient_backcall_selector(MainScreen::onClientDisconnected));
	NetworkClient::sharedDelegate()->registerOnConnectedEnded(this,  netclient_backcall_selector(MainScreen::onClientConnectedEnded));

	NetworkClient::sharedDelegate()->connect();

	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("�������ӷ�����..."));
}

void MainScreen::clientClose()
{
	NetworkClient::sharedDelegate()->close();
	NetworkClient::sharedDelegate()->disconnect();
}

/***************************************************************************/

void MainScreen::onFileViewNewFileMessage(string strFilePathName)
{
	NewFileDialog* pNewFileDialog = NewFileDialog::create(strFilePathName);
	pNewFileDialog->setPosition(SCREEN_CENTER_POS);
	m_pWindow->addChild(pNewFileDialog);
	pNewFileDialog->setDelegate(this);
}

void MainScreen::onFileViewOpenFileMessage(string strFilePathName)
{
	//����XML�ļ�
	bool isCorrectLoad = XmlParser::getInstance()->loadFile(U2A(strFilePathName.c_str()).c_str());
	if (!isCorrectLoad)
	{
		MessageBox(NULL, L"����XMLʧ��", L"����", 0);
		m_isLoadConfigFile = false;
		return;
	}

	m_isLoadConfigFile = true;

	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("�����ļ����سɹ�"));

	//����MessageListView����Դ
	MessageListView* pMessageListView = (MessageListView*)getViewByID(ID_MESSAGE_LIST_VIEW);
	pMessageListView->updateDataResouse();

	AttributeListView* pAttributeListView = (AttributeListView*)getViewByID(ID_ATTRIBUTE_LIST_VIEW);
	pAttributeListView->setTitle("");
	pAttributeListView->clear();

	FKCW_UIWidget_Button* pAddMessageButton = (FKCW_UIWidget_Button*)getViewByID(ID_ADD_MAIN_MESSAGE_BUTTON);
	pAddMessageButton->setEnabled(true);
}

/***************************************************************************/
//�Ѹ�
void MainScreen::onMessageListViewDataSourceMessage(MessageListView* pSender)
{
	vector<string> mainItems = XmlParser::getInstance()->getMainElementCStrings();
	for (unsigned int i=0; i<mainItems.size(); i++)
	{
		string mainBuf = mainItems.at(i);
		pSender->addMainItem(A2U(mainBuf.c_str()));

		short mainTypeBuf = XmlParser::GetMainType(mainBuf);
		vector<string> subItems = XmlParser::getInstance()->getSubElementCstrings(mainTypeBuf);

		for (unsigned int j=0; j<subItems.size(); j++)
		{
			string subString = XmlParser::GetSubString(subItems.at(j).c_str());
			pSender->addSubItem(i, A2U(subString.c_str()));
		}
		pSender->addSubItemAddButton(i);
	}

	AttributeListView* pAttributeListView = (AttributeListView*)getViewByID(ID_ATTRIBUTE_LIST_VIEW);
	pAttributeListView->setTitle("");
	pAttributeListView->clear();

	FKCW_UIWidget_Button* pSendMessageButton = (FKCW_UIWidget_Button*)getViewByID(ID_SEND_MESSAGE_BUTTON);
	pSendMessageButton->setEnabled(false);
}

void MainScreen::onMessageListViewSelectedSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle)
{
	//Ϊȫ�ֱ�����ֵ
	m_mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));
	m_subType = XmlParser::GetSubType(U2A(subTitle.c_str()));

	short fbm = XmlParser::getInstance()->getSubElementFBM(m_mainType, m_subType);
	short fbs = XmlParser::getInstance()->getSubElementFBS(m_mainType, m_subType);

	char cFbm[26];
	char cFbs[26];
	_itoa(fbm, cFbm, 10);
	_itoa(fbs, cFbs, 10);

	AttributeListView* pAttributeListView = (AttributeListView*)getViewByID(ID_ATTRIBUTE_LIST_VIEW);
	pAttributeListView->setTitle(subTitle);
	pAttributeListView->setSubTitle(A2U(" ����������:") + cFbm + A2U(" ����������:") + cFbs);
	pAttributeListView->updateDataResouse();

	FKCW_UIWidget_Button* pSendMessageButton = (FKCW_UIWidget_Button*)getViewByID(ID_SEND_MESSAGE_BUTTON);
	pSendMessageButton->setEnabled(true);
}

void MainScreen::onMessageListViewRemoveMainItemMessage(MessageListView* pSender, string mainTitle)
{
	short mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));
	XmlParser::getInstance()->removeMainElement(mainType);
}

void MainScreen::onMessageListViewRemoveSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle)
{
	short mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));
	short subType = XmlParser::GetSubType(U2A(subTitle.c_str()));
	XmlParser::getInstance()->removeSubElement(mainType, subType);
}

void MainScreen::onMessageListViewAddSubItemMessage(MessageListView* pSender, string mainTitle)
{
	short mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));
	NewSubMessageDialog* pNewSubMessageDialog = NewSubMessageDialog::create(mainType);
	pNewSubMessageDialog->setDelgate(this);
	pNewSubMessageDialog->setPosition(SCREEN_CENTER_POS);
	m_pWindow->addChild(pNewSubMessageDialog);
}

void MainScreen::onMessageListViewReviseMainItemMessage(MessageListView* pSender, string mainTitle)
{
	short mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));
	string mainName = XmlParser::GetMainName(U2A(mainTitle.c_str()));

	ReviseMainMessageDialog* pReviseMainMessageDialog = ReviseMainMessageDialog::create(mainType, A2U(mainName.c_str()));
	pReviseMainMessageDialog->setDelegate(this);
	pReviseMainMessageDialog->setPosition(SCREEN_CENTER_POS);
	m_pWindow->addChild(pReviseMainMessageDialog);
}

void MainScreen::onReviseMainMessageDialogSaveMessage(ReviseMainMessageDialog* pSender, short oldMainType, short mainType, string mainName)
{
	XmlParser::getInstance()->setMainElementName(oldMainType, U2A(mainName.c_str()));
	XmlParser::getInstance()->setMainElementType(oldMainType, mainType);

	MessageListView* pMessageListView = (MessageListView*)getViewByID(ID_MESSAGE_LIST_VIEW);
	pMessageListView->updateDataResouse();
}

void MainScreen::onNewSubMessageDialogSaveMessage( NewSubMessageDialog* pSender, short mainType, short subType, string subName, short fbm, short fbs )
{
	XmlParser::getInstance()->addSubElement(mainType, U2A(subName.c_str()).c_str(), subType, fbm, fbs);
	
	MessageListView* pMessageListView = (MessageListView*)getViewByID(ID_MESSAGE_LIST_VIEW);
	pMessageListView->updateDataResouse();
}

/***************************************************************************/

void MainScreen::onAddMainMessageButtonClick( CCObject* pSender )
{
	NewMainMessageDialog* pDialogBase = NewMainMessageDialog::create();
	pDialogBase->setPosition(SCREEN_CENTER_POS);
	m_pWindow->addChild(pDialogBase);
	pDialogBase->setDelegate(this);
}

void MainScreen::onNewMainMessageDialogSaveMessage( NewMainMessageDialog* pSender, short mainType, string mainName )
{
	XmlParser::getInstance()->addMainElement(mainType, U2A(mainName.c_str()));
	MessageListView* pMessageListView = (MessageListView*)getViewByID(ID_MESSAGE_LIST_VIEW);
	pMessageListView->updateDataResouse();
}

void MainScreen::onReviseSubMessageDialogSaveMessage(ReviseSubMessageDialog* pSender, short mainType, short subType)
{
	XmlParser::getInstance()->setSubElementFBM(mainType, subType, pSender->getFbm());
	XmlParser::getInstance()->setSubElementFBS(mainType, subType, pSender->getFbs());
	XmlParser::getInstance()->setSubElementName(mainType, subType, U2A(pSender->getSubName().c_str()));
	XmlParser::getInstance()->setSubElementType(mainType, subType, pSender->getSubType());

	MessageListView* pMessageListView = (MessageListView*)getViewByID(ID_MESSAGE_LIST_VIEW);
	pMessageListView->updateDataResouse();
}

/***************************************************************************/

void MainScreen::onAttributeListViewDataSourceMessage(AttributeListView* pSender)
{
	vector<string> attributeItems = XmlParser::getInstance()->getAttributeCstrings(m_mainType, m_subType);
	for (unsigned int i = 0; i < attributeItems.size(); i++)
	{
		string item = attributeItems.at(i);
		int cutIndex = item.find(")") + 2;
		string head = item.substr(0, cutIndex);
		string tail = item.substr(cutIndex);

		/*
		//�������ַ���
		if (tail.size() > 8)
		{
			tail = tail.substr(0, 8) + "...";
		}
		*/

		pSender->addItem(A2U((head + tail).c_str()));
	}
	pSender->addItemAddButton();

	AttributeEditView* pAttributeEditView = (AttributeEditView*)getViewByID(ID_ATTRIBUTE_EDIT_VIEW);
	pAttributeEditView->setEnabled(false);
}

void MainScreen::onAttributeListViewSelectedItemMessage(AttributeListView* pSender, string attributeName)
{
	string attName = XmlParser::GetAttName(U2A(attributeName.c_str()));
	string attType = XmlParser::GetAttType(U2A(attributeName.c_str()));
	string attData = XmlParser::GetAttData(U2A(attributeName.c_str()));
	//ȫ��
	m_attName = attName;

	AttributeEditView* pAttributeEditView = (AttributeEditView*)getViewByID(ID_ATTRIBUTE_EDIT_VIEW);
	pAttributeEditView->setAttName(A2U(attName.c_str()));
	pAttributeEditView->setTypeName(A2U(attType.c_str()));
	pAttributeEditView->setData(A2U(attData.c_str()));
	pAttributeEditView->setEnabled(true);
}

void MainScreen::onAttributeListViewRemoveItemMessage(AttributeListView* pSender, string attributeName)
{
	string attName = XmlParser::GetAttName(U2A(attributeName.c_str()));
	XmlParser::getInstance()->removeAttributeElement(m_mainType, m_subType, attName);
}

void MainScreen::onAttributeListViewAddItemMessage( AttributeListView* pSender )
{
	NewAttributeDialog* pNewAttributeDialog = NewAttributeDialog::create();
	pNewAttributeDialog->setPosition(SCREEN_CENTER_POS);
	m_pWindow->addChild(pNewAttributeDialog);
	pNewAttributeDialog->setDelegate(this);
}

/***************************************************************************/

void MainScreen::onSaveMessage(AttributeEditView* pAttributeEditView, string attName, string typeName, string data)
{
	XmlParser::getInstance()->setAttributeElementDataType(m_mainType, m_subType, m_attName, typeName);
	XmlParser::getInstance()->setAttributeElementValue(m_mainType, m_subType, m_attName, U2A(data.c_str()));
	XmlParser::getInstance()->setAttributeElementName(m_mainType, m_subType, m_attName, U2A(attName.c_str()));

	AttributeListView* pAttibuteListView = (AttributeListView*)getViewByID(ID_ATTRIBUTE_LIST_VIEW);
	pAttibuteListView->updateDataResouse();

	pAttributeEditView->setAttName("");
	pAttributeEditView->setTypeName("");
	pAttributeEditView->setData("");
}

void MainScreen::onIpPostButtonClickMessage(IpPostView* pSender, string ip, short post)
{
	if (pSender->getTag() == ID_LISTEN_VIEW)
	{
		if (m_pNetworkServer == NULL)
		{
			serverListen(ip.c_str(), post);
		}
		else
		{
			serverClose();
		}
	}
	else if (pSender->getTag() == ID_CONNECT_VIEW)
	{
		if (NetworkClient::sharedDelegate()->isConnected())
		{
			clientClose();
		}
		else
		{
			clientConnect(ip.c_str(), post);
		}
	}
}
/***************************************************************************/

void MainScreen::onClientMessageReceived(NetworkClient* client, FKCW_SimpleNet_Buffer& oBuffer)
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);

	MsgPack msgPack;
	MsgPackUnpack::unPack(msgPack, XmlParser::getInstance(), &oBuffer);

	{
		//����̨���
		char mainTypeBuf[6];
		char subTypeBuf[6];
		sprintf(mainTypeBuf, "%d", msgPack.mainType);
		sprintf(subTypeBuf, "%d", msgPack.subType);

		string logText = " ������:" + string(mainTypeBuf )+ "�����ͣ�" + string(subTypeBuf);

		pClientLogView->log(A2U(("> �յ���Ϣ��"+logText).c_str()));

		for (unsigned int i=0; i<msgPack.atts.size(); i++)
		{
			logText.clear();

			logText.append("      >");
			logText.append(msgPack.atts.at(i).name);
			logText.append(":");
			logText.append(msgPack.atts.at(i).data);

			pClientLogView->log(A2U(logText.c_str()));
		}
	}

	//��ȡ��������
	short fbm = msgPack.fbm;
	short fbs = msgPack.fbs;

	if(fbm == 0 || fbs ==0)
	{
		pClientLogView->log(A2U("�ѷ������������Ϣ����"));
		return;
	}
	else if (!XmlParser::getInstance()->isHaveSubElement(fbm, fbs))
	{
		pClientLogView->log(A2U("����������Ϣ�����ж�:(δ��ȷ�ҵ�������Ϣ)"));
		return;
	}

	//----�����˷�������
	FKCW_SimpleNet_Buffer sBuffer;
	MsgPack sMsgPack = XmlParser::getInstance()->getMsgPack(fbm, fbs);

	MsgPackUnpack::pack(sBuffer, sMsgPack);

	NetworkClient::sharedDelegate()->send(&sBuffer);

	//����̨���
	{
		char mainTypeBuf[6];
		char subTypeBuf[6];
		sprintf(mainTypeBuf, "%d", sMsgPack.mainType);
		sprintf(subTypeBuf, "%d", sMsgPack.subType);

		string logText = " ������:";
		logText.append(mainTypeBuf);
		logText.append(" ������:");
		logText.append(subTypeBuf);

		pClientLogView->log(A2U(("< ������Ϣ��"+logText).c_str()).c_str());

		for (unsigned int i=0; i<sMsgPack.atts.size(); i++)
		{
			logText.clear();

			logText.append("      <");
			logText.append(sMsgPack.atts.at(i).name);
			logText.append(":");
			logText.append(sMsgPack.atts.at(i).data);

			pClientLogView->log(A2U(logText.c_str()));
		}
	}
}

void MainScreen::onClientConnected()
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("��������ɹ���������"));

	IpPostView* pConnectView = (IpPostView*)getViewByID(ID_CONNECT_VIEW);
	pConnectView->setButtonText(A2U("�Ͽ�").c_str());
}

void MainScreen::onClientConnectTimeout()
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("���ӳ�ʱ"));
}

void MainScreen::onClientExceptionCaught()
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("�ͻ����쳣"));

	IpPostView* pConnectView = (IpPostView*)getViewByID(ID_CONNECT_VIEW);
	pConnectView->setButtonText(A2U("����").c_str());
}

void MainScreen::onClientDisconnected()
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("�ͻ��˶Ͽ�"));

	IpPostView* pConnectView = (IpPostView*)getViewByID(ID_CONNECT_VIEW);
	pConnectView->setButtonText(A2U("����").c_str());
}

void MainScreen::onClientConnectedEnded()
{
	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U("�ͻ��˶Ͽ�"));

	IpPostView* pConnectView = (IpPostView*)getViewByID(ID_CONNECT_VIEW);
	pConnectView->setButtonText(A2U("����").c_str());
}

/***************************************************************************/

void MainScreen::onServerMessageReceived(NetworkServer* pServer, FKCW_SimpleNet_Buffer& oBuffer)
{
	LogView* pServerLogView = (LogView*)getViewByID(ID_SERVER_LOG_VIEW);

	MsgPack msgPack;
	MsgPackUnpack::unPack(msgPack, XmlParser::getInstance(), &oBuffer);

	{
		//����̨���
		char mainTypeBuf[6];
		char subTypeBuf[6];
		sprintf(mainTypeBuf, "%d", msgPack.mainType);
		sprintf(subTypeBuf, "%d", msgPack.subType);

		string logText = " ������:";
		logText.append(mainTypeBuf);
		logText.append(" ������:");
		logText.append(subTypeBuf);

		pServerLogView->safeModeLog(A2U(("> �յ���Ϣ��"+logText).c_str()));

		for (unsigned int i=0; i<msgPack.atts.size(); i++)
		{
			logText.clear();

			logText.append("      >");
			logText.append(msgPack.atts.at(i).name);
			logText.append(":");
			logText.append(msgPack.atts.at(i).data);

			pServerLogView->safeModeLog(A2U(logText.c_str()));
		}
	}

	{
		//��ȡ��������
		short fbm = msgPack.fbm;
		short fbs = msgPack.fbs;

		if(fbm == 0 || fbs ==0)
		{
			pServerLogView->safeModeLog(A2U("�ѷ������������Ϣ����"));
			return;
		}
		if (!XmlParser::getInstance()->isHaveSubElement(fbm, fbs))
		{
			pServerLogView->safeModeLog(A2U("����������Ϣ�����ж�(δ��ȷ�ҵ�������Ϣ)"));
			return;
		}
		//----��ͻ��˷�������
		FKCW_SimpleNet_Buffer sBuffer;
		MsgPack sMsgPack = XmlParser::getInstance()->getMsgPack(fbm, fbs);

		MsgPackUnpack::pack(sBuffer, sMsgPack);

		pServer->send(&sBuffer);

		//����̨���
		char mainTypeBuf[6];
		char subTypeBuf[6];
		sprintf(mainTypeBuf, "%d", sMsgPack.mainType);
		sprintf(subTypeBuf, "%d", sMsgPack.subType);

		string logText = " ������:";
		logText.append(mainTypeBuf);
		logText.append(" ������:");
		logText.append(subTypeBuf);

		pServerLogView->safeModeLog(A2U(("< ������Ϣ��"+logText).c_str()));

		for (unsigned int i=0; i<sMsgPack.atts.size(); i++)
		{
			logText.clear();
			logText.append("      <");
			logText.append(sMsgPack.atts.at(i).name);
			logText.append(":");
			logText.append(sMsgPack.atts.at(i).data);

			pServerLogView->safeModeLog(logText);
		}
	}
}

void MainScreen::onServerConnected()
{
	LogView* pServerLogView = (LogView*)getViewByID(ID_SERVER_LOG_VIEW);
	pServerLogView->safeModeLog(A2U("�������ӳɹ�"));
}

void MainScreen::onServerDisconnected()
{
	LogView* pServerLogView = (LogView*)getViewByID(ID_SERVER_LOG_VIEW);
	pServerLogView->safeModeLog(A2U("��ͻ������ӶϿ�"));
}

void MainScreen::onServerConnectedEnded()
{
}

void MainScreen::onServerExceptionCaught()
{
	LogView* pServerLogView = (LogView*)getViewByID(ID_SERVER_LOG_VIEW);
	pServerLogView->safeModeLog(A2U("�������ѹر�"));
}

/***************************************************************************/

void MainScreen::onSendButtonClick(CCObject* pSender)
{
	FKCW_SimpleNet_Buffer sBuffer;
	MsgPack sMsgPack = XmlParser::getInstance()->getMsgPack(m_mainType, m_subType);
	MsgPackUnpack::pack(sBuffer, sMsgPack);
	NetworkClient::sharedDelegate()->send(&sBuffer);

	char clog[128];
	sprintf(clog, "��ʼ������Ϣ:  MainType-%d SubType-%d", m_mainType, m_subType);

	LogView* pClientLogView = (LogView*)getViewByID(ID_CLIENT_LOG_VIEW);
	pClientLogView->log(A2U(clog));
}

void MainScreen::onNewAttributeDialogSaveMessage(NewAttributeDialog* pSender, string attName, string typeName, string data)
{
	XmlParser::getInstance()->addAttributeElement(m_mainType, m_subType, U2A(attName.c_str()).c_str(), U2A(typeName.c_str()).c_str(), U2A(data.c_str()).c_str());
	
	AttributeListView* pAttributeListView= (AttributeListView*)getViewByID(ID_ATTRIBUTE_LIST_VIEW);
	pAttributeListView->updateDataResouse();
}

/***************************************************************************/

void MainScreen::onMessageListViewReviseSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle)
{
	short mainType = XmlParser::GetMainType(U2A(mainTitle.c_str()));

	short subType = XmlParser::GetSubType(U2A(subTitle.c_str()));
	string subName = XmlParser::GetNoFBTypeToSubName(U2A(subTitle.c_str()));
	short fbm = XmlParser::getInstance()->getSubElementFBM(mainType, subType);
	short fbs = XmlParser::getInstance()->getSubElementFBS(mainType, subType);
	
	char cFbm[15];
	char cFbs[15];
	char cSubType[15];
	_itoa(fbm, cFbm, 10);
	_itoa(fbs, cFbs, 10);
	_itoa(subType, cSubType, 10);

	ReviseSubMessageDialog* pReviseSubMessageDialog = ReviseSubMessageDialog::create(mainType, subType);
	pReviseSubMessageDialog->setPosition(SCREEN_CENTER_POS);
	pReviseSubMessageDialog->setEditBoxFbm(cFbm);
	pReviseSubMessageDialog->setEditBoxFbs(cFbs);
	pReviseSubMessageDialog->setEditBoxSubName(A2U(subName.c_str()));
	pReviseSubMessageDialog->setEditBoxSubType(cSubType);
	m_pWindow->addChild(pReviseSubMessageDialog);
	pReviseSubMessageDialog->setDelegate(this);
}

void MainScreen::onNewFileDialogDelegateSaveMessage(NewFileDialog* pSender, string pathAndFileName)
{
	FILE* isHave = fopen(U2A(pathAndFileName.c_str()).c_str(), "r");
	if (isHave != NULL)
	{
		MessageBox(NULL, L"��ǰ�ļ��Ѿ�����", L"", 0);
		fclose(isHave);
		return;
	}

	XmlParser::getInstance()->newFile(U2A(pathAndFileName.c_str()).c_str());

	isHave = fopen(U2A(pathAndFileName.c_str()).c_str(), "r");
	if (isHave == NULL)
	{
		MessageBox(NULL, L"�ļ�����ʧ��: ������Ϸ����ļ���", L"", 0);
	}
	else
	{
		fclose(isHave);

		FileView* pFileView = (FileView*)this->getViewByID(ID_FILE_VIEW);
		pFileView->setText(pathAndFileName.c_str());

		onFileViewOpenFileMessage(pathAndFileName);
	}
}

/***************************************************************************/