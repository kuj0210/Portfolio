#pragma once
#include "afxwin.h"


// myDlg ��ȭ �����Դϴ�.

class myDlg : public CDialogEx
{
	DECLARE_DYNAMIC(myDlg)

public:
	myDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~myDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton btn1;
	CButton btn2;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CListBox ������;
};
