// ��й�ȣdlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "����3.h"
#include "��й�ȣdlg.h"
#include "afxdialogex.h"
#include "����3View.h"
#include <stdlib.h>
#include <atlstr.h>
#include "MainFrm.h"
// ��й�ȣdlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(��й�ȣdlg, CDialogEx)

��й�ȣdlg::��й�ȣdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(��й�ȣdlg::IDD, pParent)
{

	CMainFrame* p =(CMainFrame*)AfxGetMainWnd();
	for(int i=0; i<10 ; i++){
			A[i]=NULL;
	}
	this->P=(C����3View*)p->GetActiveView();
}

��й�ȣdlg::~��й�ȣdlg()
{
}

void ��й�ȣdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(��й�ȣdlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &��й�ȣdlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ��й�ȣdlg �޽��� ó�����Դϴ�.


BOOL ��й�ȣdlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	int wNoti= HIWORD(wParam);
	int wID=LOWORD(wParam);


	
	
	printf("�̺�Ʈ\n");
	if(wNoti==EN_CHANGE){
		m_edit.GetWindowTextA(A,10);;
	}
		return CDialogEx::OnCommand(wParam, lParam);
}



void ��й�ȣdlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	this->P->Skey.Format("%s",A);
	CDialogEx::OnOK();
}
