// FKDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FKDialog.h"
#include "afxdialogex.h"


// CFKDialog �Ի���

IMPLEMENT_DYNAMIC(CFKDialog, CDialog)

CFKDialog::CFKDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFKDialog::IDD, pParent)
{

}

CFKDialog::~CFKDialog()
{
}

BOOL CFKDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT1, m_value);
	SetWindowText(m_WindowText);
	return TRUE;
}

BOOL CFKDialog::DestroyWindow()
{
	GetDlgItemText(IDC_EDIT1, m_value);

	return CDialog::DestroyWindow();
}

void CFKDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFKDialog, CDialog)
END_MESSAGE_MAP()


// CFKDialog ��Ϣ�������
