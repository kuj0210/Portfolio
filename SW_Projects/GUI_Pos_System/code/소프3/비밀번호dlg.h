#pragma once
#include "afxwin.h"
#include "����3View.h"

// ��й�ȣdlg ��ȭ �����Դϴ�.

class ��й�ȣdlg : public CDialogEx
{
	DECLARE_DYNAMIC(��й�ȣdlg)

public:
	��й�ȣdlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	

	virtual ~��й�ȣdlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	CEdit m_edit;
	 char A[10];
	 C����3View* P;
	afx_msg void OnBnClickedOk();
};
