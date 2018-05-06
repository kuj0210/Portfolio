// 비밀번호dlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "소프3.h"
#include "비밀번호dlg.h"
#include "afxdialogex.h"
#include "소프3View.h"
#include <stdlib.h>
#include <atlstr.h>
#include "MainFrm.h"
// 비밀번호dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(비밀번호dlg, CDialogEx)

비밀번호dlg::비밀번호dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(비밀번호dlg::IDD, pParent)
{

	CMainFrame* p =(CMainFrame*)AfxGetMainWnd();
	for(int i=0; i<10 ; i++){
			A[i]=NULL;
	}
	this->P=(C소프3View*)p->GetActiveView();
}

비밀번호dlg::~비밀번호dlg()
{
}

void 비밀번호dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(비밀번호dlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &비밀번호dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// 비밀번호dlg 메시지 처리기입니다.


BOOL 비밀번호dlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int wNoti= HIWORD(wParam);
	int wID=LOWORD(wParam);


	
	
	printf("이벤트\n");
	if(wNoti==EN_CHANGE){
		m_edit.GetWindowTextA(A,10);;
	}
		return CDialogEx::OnCommand(wParam, lParam);
}



void 비밀번호dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	this->P->Skey.Format("%s",A);
	CDialogEx::OnOK();
}
