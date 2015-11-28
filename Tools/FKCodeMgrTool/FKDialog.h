//*************************************************************************
//	��������:	2015-3-30
//	�ļ�����:	FKDialog.h
//  �� �� ��:   �˹۸� Rect 	
//	��Ȩ����:	MIT
//	˵    ��:	
//*************************************************************************

#pragma once

//-------------------------------------------------------------------------
#include "resource.h"


// CFKDialog �Ի���

class CFKDialog : public CDialog
{
	DECLARE_DYNAMIC(CFKDialog)
	CString m_value;
	CString m_WindowText;
public:
	CFKDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFKDialog();
	CString GetValue() const {return m_value;}
	void SetValue(const CString& value) {m_value = value;}
	CString GetWindowTextString() const {return m_WindowText;}
	void SetWindowTextString(const CString& value) {m_WindowText = value;}

	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow( );
// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
