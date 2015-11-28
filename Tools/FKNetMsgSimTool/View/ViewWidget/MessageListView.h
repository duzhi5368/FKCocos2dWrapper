#ifndef _MESSAGE_LIST_VIEW_
#define _MESSAGE_LIST_VIEW_

#include "FKCWLib/FKCocos2dxWrapper.h"

class MessageListView;

class MainItemObject : public CCObject
{
public:
	CREATE_FUNC(MainItemObject);
	virtual bool init(){return true;}
public:
	string mainTitle;
};

class SubItemUserObject : public CCObject
{
public:
	CREATE_FUNC(SubItemUserObject);
	virtual bool init(){return true;}
public:
	string mainTitle;
	string subTitle;
	FKCW_UIWidget_Label* pMainLabel;
};

class MessageListViewDelegate
{
public:
	MessageListViewDelegate(){}
	virtual ~MessageListViewDelegate(){}
	//��������ί��
	virtual void onMessageListViewDataSourceMessage(MessageListView* pSender) = 0;
	//ѡ��������ί��
	virtual void onMessageListViewSelectedSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle) = 0;
	//ɾ��������ί��  �����onMessageListViewDataSourceMessage
	virtual void onMessageListViewRemoveMainItemMessage(MessageListView* pSender, string mainTitle) = 0;
	//�޸�������
	virtual void onMessageListViewReviseMainItemMessage(MessageListView* pSender, string mainTitle) = 0;
	//ɾ��������ί��  �����onMessageListViewDataSourceMessage
	virtual void onMessageListViewRemoveSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle) = 0;
	//���������ί��
	virtual void onMessageListViewAddSubItemMessage(MessageListView* pSender, string mainTitle) = 0;
	//�޸�������ί��
	virtual void onMessageListViewReviseSubItemMessage(MessageListView* pSender, string mainTitle, string subTitle) = 0;
};

class MessageListView : public FKCW_UIWidget_ExpandableListView
{
public:
	CREATE_FUNC(MessageListView);
	MessageListView();
	virtual ~MessageListView();
public:
	//���һ�����ڵ�
	void addMainItem(string mainTitle);
	//���һ������
	void addSubItem(int index, string subTitle);
	//��һ�����ڵ���׷��һ����Ӱ�ť
	void addSubItemAddButton(int index);

	//�����¼�ί��Ŀ��
	void setDelegate(MessageListViewDelegate* pDelegate);
	//��������Դ ����ӦonMessageListViewDataSourceMessage�¼�
	void updateDataResouse();
	//���
	void clear();
protected:
	virtual bool init();
	void onRemoveMainItemButtonClick(CCObject* pSender);
	void onAddSubItemButtonClick(CCObject* pSender);
	void onSelectedSubItemClick(CCObject* pSender);
	void onRemoveSubItemButtonClick(CCObject* pSender);
	//��һ֡ˢ������
	void autoReloadData();
	virtual void update(float delta);
private:
	MessageListViewDelegate* m_pDelegate;
	FKCW_UIWidget_ColorView* m_pSelectColorView;	//��ǰѡ�е�ColorView
	bool m_isReloadData;							//��һ֡��ձ�ʶ
};



#endif