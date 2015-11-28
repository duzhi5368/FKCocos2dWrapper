#ifndef _REVISE_SUB_MESSAGE_DIALOG_H_
#define _REVISE_SUB_MESSAGE_DIALOG_H_

#include "DialogBase.h"

class ReviseSubMessageDialog;

class ReviseSubMessageDialogDeleget
{
public:
	//�޸������ͱ�����Ϣί��
	virtual void onReviseSubMessageDialogSaveMessage(ReviseSubMessageDialog* pSender, short mainType, short subType) = 0;
};

class ReviseSubMessageDialog : public DialogBase
{
public:
	static ReviseSubMessageDialog* create(short mainType, short subType);

	void setDelegate(ReviseSubMessageDialogDeleget* pDeleget);
	//���������ͱ༭��
	void setEditBoxSubType(string subType);
	//�������������༭��
	void setEditBoxSubName(string subName);
	//���÷��������ͱ༭��
	void setEditBoxFbm(string fbm);
	//���÷��������ͱ༭��
	void setEditBoxFbs(string fbs);

	//��ȡ������
	short  getSubType();
	//��ȡ��������
	string getSubName();
	//��ȡ����������
	short  getFbm();
	//��ȡ����������
	short  getFbs();
protected:
	ReviseSubMessageDialog();
	virtual ~ReviseSubMessageDialog();
	virtual bool init(short mainType, short subType);
	virtual CCSize GetDialogSize();

	void onButtonClick(CCObject* pSender);
protected:
	CCEditBox* m_pEditBoxSubType;
	CCEditBox* m_pEditBoxSubName;
	CCEditBox* m_pEditBoxFbm;
	CCEditBox* m_pEditBoxFbs;
	ReviseSubMessageDialogDeleget* m_pDeleget;
	short m_mainType;
	short m_subType;
};

#endif