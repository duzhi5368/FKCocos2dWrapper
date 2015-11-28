#ifndef _MAIN_SCREEN_H_
#define _MAIN_SCREEN_H_

#include "FKCWLib/FKCocos2dxWrapper.h"
#include "View/IncludeViewWidget.h"
#include "Xml/XmlParser.h"
#include "Xml/MsgPackUnpack.h"
#include "Network/NetworkClient.h"
#include "Network/NetworkServer.h"

class MainScreen : public CCLayerColor,
	public FileViewDelegate,
	public MessageListViewDelegate,
	public AttributeListViewDelegate,
	public AttributeEditViewDelegate,
	public IpPostViewDelegate,
	public NewMainMessageDialogDelegate,
	public NewSubMessageDialogDelegate,
	public NewAttributeDialogDelegate,
	public ReviseSubMessageDialogDeleget,
	public ReviseMainMessageDialogDelegate,
	public NewFileDialogDelegate
{
public:
	CREATE_FUNC(MainScreen);
	static CCScene* createScene();
public:
	//��ʼ������
	void initUI();
	
	//��������ʼ����
	void serverListen(const char* ip, short post);
	void serverClose();

	//�ͻ������ӷ�����
	void clientConnect(const char* ip, short post);
	void clientClose();
protected:
	MainScreen();
	virtual ~MainScreen();
	virtual bool init();
protected:
	CCNode* getViewByID(int id);
	/***************************************************************
							�ļ��˵�
	***************************************************************/
	virtual void onFileViewNewFileMessage(string strFilePathName);
	virtual void onFileViewOpenFileMessage(string strFilePathName);

	/***************************************************************
							��Ϣ�б�
	***************************************************************/
	//����Դ
	virtual void onMessageListViewDataSourceMessage(MessageListView* pSender);
	//ѡ����Ϣ
	virtual void onMessageListViewSelectedSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle);
	//�Ƴ����б�
	virtual void onMessageListViewRemoveMainItemMessage(MessageListView* pSender, string mainTitle);
	//�Ƴ�����
	virtual void onMessageListViewRemoveSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle);
	//�������
	virtual void onMessageListViewAddSubItemMessage(MessageListView* pSender, string mainTitle);
	//�޸����б�
	virtual void onMessageListViewReviseMainItemMessage(MessageListView* pSender, string mainTitle);
	//�޸�����
	virtual void onMessageListViewReviseSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle);
	
	/***************************************************************
							�����б�
	***************************************************************/
	//����Դ
	virtual void onAttributeListViewDataSourceMessage(AttributeListView* pSender);
	//ѡ����Ϣ
	virtual void onAttributeListViewSelectedItemMessage(AttributeListView* pSender, string attributeName);
	//�Ƴ�
	virtual void onAttributeListViewRemoveItemMessage(AttributeListView* pSender, string attributeName);
	//���
	virtual void onAttributeListViewAddItemMessage( AttributeListView* pSender );

	/***************************************************************
							�༭����ģ��
	***************************************************************/
	//����
	virtual void onSaveMessage(AttributeEditView* pAttributeEditView, string attName, string typeName, string data);

	/***************************************************************
							������-�ͻ���
	***************************************************************/
	//���Ӱ�ť���
	virtual void onIpPostButtonClickMessage(IpPostView* pSender, string ip, short post);

	/***************************************************************
							�ͻ����¼�
	***************************************************************/
	void onClientMessageReceived	(NetworkClient* client, FKCW_SimpleNet_Buffer& oBuffer);
	void onClientConnected			();
	void onClientConnectTimeout		();
	void onClientExceptionCaught	();
	void onClientDisconnected		();
	void onClientConnectedEnded		();

	/***************************************************************
							�������¼�
	***************************************************************/
	void onServerMessageReceived	(NetworkServer* pServer, FKCW_SimpleNet_Buffer& oBuffer);
	void onServerConnected			();	
	void onServerDisconnected		();
	void onServerConnectedEnded		();
	void onServerExceptionCaught	();

	/***************************************************************
							�����¼�
	***************************************************************/
	//������Ϣ��ť
	void onSendButtonClick(CCObject* pSender);
	//������б�ť
	void onAddMainMessageButtonClick(CCObject* pSender);

	/***************************************************************
							�Ի���
	***************************************************************/
	//������б� �Ի��� ����
	virtual void onNewMainMessageDialogSaveMessage( NewMainMessageDialog* pSender, short mainType, string mainName );
	//�޸����б� �Ի��� ����
	virtual void onReviseMainMessageDialogSaveMessage(ReviseMainMessageDialog* pSender, short oldMainType, short mainType, string mainName);

	//������� �Ի��� ����
	virtual void onNewSubMessageDialogSaveMessage( NewSubMessageDialog* pSender, short mainType, short subType, string subName, short fbm, short fbs );
	//�޸����� �Ի��� ����
	virtual void onReviseSubMessageDialogSaveMessage(ReviseSubMessageDialog* pSender, short mainType, short subType);

	//��������б� �Ի��� ����
	virtual void onNewAttributeDialogSaveMessage( NewAttributeDialog* pSender, string attName, string typeName, string data );
	
	//�½��ļ� �Ի��� ����
	virtual void onNewFileDialogDelegateSaveMessage(NewFileDialog* pSender, string pathAndFileName);

private:
	NetworkServer* m_pNetworkServer;
private:
	FKCW_UIWidget_WidgetWindow* m_pWindow;
	short m_mainType;
	short m_subType;
	string m_attName;
	bool m_isLoadConfigFile;		//�Ƿ��Ѽ��������ļ�
};

#endif