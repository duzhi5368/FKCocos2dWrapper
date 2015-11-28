#ifndef _NEW_FILE_DIALOG_H_
#define _NEW_FILE_DIALOG_H_

#include "DialogBase.h"

class NewFileDialog;

class NewFileDialogDelegate
{
public:
	//������Ϣί��
	virtual void onNewFileDialogDelegateSaveMessage(NewFileDialog* pSender, string pathAndFileName) = 0;
};

/**
 * NewFileDialog
 * �½��ļ��Ի���
 */
class NewFileDialog : public DialogBase
{
public:
	//path: �ļ��о���·��
	static NewFileDialog* create(string path);
	//���¼�ί��
	void setDelegate(NewFileDialogDelegate* pDelegate);
protected:
	NewFileDialog();
	virtual ~NewFileDialog();
	virtual bool init(string path);
	virtual CCSize GetDialogSize();

	//���水ť�ص�
	void onSaveButtonClick(CCObject* pSender);
private:
	CCEditBox* m_pEditBoxFileName;
	NewFileDialogDelegate* m_pDelegate;
	string m_path;
};

#endif