// myDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "소프3.h"
#include "myDlg.h"
#include "afxdialogex.h"
#include "소프3View.h"
#include <iostream>

using namespace std;
// myDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(myDlg, CDialogEx)

myDlg::myDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(myDlg::IDD, pParent)
{

}

myDlg::~myDlg()
{
}

void myDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(myDlg, CDialogEx)

END_MESSAGE_MAP()


// myDlg 메시지 처리기입니다.


void myDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



}


BOOL myDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	
	

	return CDialogEx::OnCommand(wParam, lParam);
}
