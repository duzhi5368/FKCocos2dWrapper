#ifndef _ATTRIBUTE_LIST_VIEW_H_
#define _ATTRIBUTE_LIST_VIEW_H_

#include "FKCWLib/FKCocos2dxWrapper.h"

class AttributeListView;

class AttributeListViewDelegate
{
public:
	//��������ί��
	virtual void onAttributeListViewDataSourceMessage(AttributeListView* pSender) = 0;
	//ѡ��ѡ��ί��
	virtual void onAttributeListViewSelectedItemMessage(AttributeListView* pSender, string attributeName) = 0;
	//ɾ��ѡ��ί��
	virtual void onAttributeListViewRemoveItemMessage(AttributeListView* pSender, string attributeName) = 0;
	//�������
	virtual void onAttributeListViewAddItemMessage(AttributeListView* pSender) = 0;
};

class AttributeListView : public FKCW_UIWidget_ExpandableListView
{
public:
	CREATE_FUNC(AttributeListView);
public:
	void setTitle(string title);
	void setSubTitle(string title);

	void addItem(string title);
	//��������Դ ����ӦonMessageListViewDataSourceMessage�¼�
	void updateDataResouse();
	//�����¼�ί��Ŀ��
	void setDelegate(AttributeListViewDelegate* pDelegate);
	void clear();

	//�������԰�ť
	void addItemAddButton();
protected:
	AttributeListView();
	~AttributeListView();
	virtual bool init();

	void onSelectedItemClick(CCObject* pSender);
	void onRemoveItemButtonClick(CCObject* pSender);
	void onAddItemButtonClick(CCObject* pSender);

	//��һ֡ˢ������
	void autoReloadData();
	virtual void update(float delta);
private:
	AttributeListViewDelegate* m_pDelegate;
	FKCW_UIWidget_Label* m_pTitleLabel;
	FKCW_UIWidget_Label* m_pSubTitleLabel;
	FKCW_UIWidget_ColorView* m_pSelectColorView;	//��ǰѡ�е�
	bool m_isReloadData;							//��һ֡��ձ�ʶ
};

#endif