#ifndef _NEW_MAIN_MESSAGE_DIALOG_H_
#define _NEW_MAIN_MESSAGE_DIALOG_H_

#include "DialogBase.h"

class NewMainMessageDialog;

class NewMainMessageDialogDelegate
{
public:
	//�½������� ������Ϣί��
	virtual void onNewMainMessageDialogSaveMessage(NewMainMessageDialog* pSender, short mainType, string mainName) = 0;
};

/**
 * NewMainMessageDialog
 * �½������ͶԻ���
 */
class NewMainMessageDialog : public DialogBase
{
public:
	CREATE_FUNC(NewMainMessageDialog);
	//�����¼�ί��
	void setDelegate(NewMainMessageDialogDelegate* pDelegate);
protected:
	NewMainMessageDialog();
	~NewMainMessageDialog();
	virtual bool	init();
	virtual CCSize	GetDialogSize();

	void onButtonClick(CCObject* pSender);
private:
	CCEditBox* m_pEditBoxMainType;
	CCEditBox* m_pEditBoxMainName;

	NewMainMessageDialogDelegate* m_pDelegate;
};

#endif