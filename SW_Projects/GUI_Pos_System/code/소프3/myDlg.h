#pragma once
#include "afxwin.h"


// myDlg 대화 상자입니다.

class myDlg : public CDialogEx
{
	DECLARE_DYNAMIC(myDlg)

public:
	myDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~myDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton btn1;
	CButton btn2;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CListBox 영수증;
};
