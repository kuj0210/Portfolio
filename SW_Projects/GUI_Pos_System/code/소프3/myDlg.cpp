// myDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "����3.h"
#include "myDlg.h"
#include "afxdialogex.h"
#include "����3View.h"
#include <iostream>

using namespace std;
// myDlg ��ȭ �����Դϴ�.

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


// myDlg �޽��� ó�����Դϴ�.


void myDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.



}


BOOL myDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	
	

	return CDialogEx::OnCommand(wParam, lParam);
}
