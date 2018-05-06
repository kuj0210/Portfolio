#pragma once
#include "afxwin.h"
#include "소프3View.h"

// 비밀번호dlg 대화 상자입니다.

class 비밀번호dlg : public CDialogEx
{
	DECLARE_DYNAMIC(비밀번호dlg)

public:
	비밀번호dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	

	virtual ~비밀번호dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	CEdit m_edit;
	 char A[10];
	 C소프3View* P;
	afx_msg void OnBnClickedOk();
};
