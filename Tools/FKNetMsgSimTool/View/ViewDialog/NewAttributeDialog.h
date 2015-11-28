#ifndef _NEW_ATTRIBUTE_DIALOG_H_
#define _NEW_ATTRIBUTE_DIALOG_H_

#include "DialogBase.h"
#include "../../FKExpand/ComboBox.h"

class NewAttributeDialog;

class NewAttributeDialogDelegate
{
public:
	//����������Ϣί��
	virtual void onNewAttributeDialogSaveMessage(NewAttributeDialog* pSender, string attName, string typeName, string data) = 0;
};


/**
 * NewAttributeDialog
 * �������ԶԻ���
 */
class NewAttributeDialog : public DialogBase
{
public:
	CREATE_FUNC(NewAttributeDialog);
	//���¼�ί��
	void setDelegate(NewAttributeDialogDelegate* pDelegate);
protected:
	NewAttributeDialog();
	virtual ~NewAttributeDialog();
	virtual bool init();
	virtual CCSize GetDialogSize();
	//���水ť�ص�
	void onSaveButtonClick(CCObject* pSender);
private:
	NewAttributeDialogDelegate* m_pDelegate;
	CCEditBox* m_pEditBoxAttName;
	ComboBox* m_pTypeNameComboBox;
	CCEditBox* m_pEditBoxData;
};

#endif