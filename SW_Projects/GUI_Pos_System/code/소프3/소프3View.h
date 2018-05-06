
// ����3View.h : C����3View Ŭ������ �������̽�
//
#include "UBtn.h"
#include "����3Doc.h"
#pragma once


class C����3View : public CView
{
protected: // serialization������ ��������ϴ�.
	C����3View();
	DECLARE_DYNCREATE(C����3View);

// Ư���Դϴ�.
public:
	C����3Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	int season;
	int money;
public:	int key;
public:	CString Skey;
public:
	CTime today;

	C����3Doc* DOC;
	char* m_BChar[4];
	char* m_MBChar[11];
	UBtn* m_BTN[4];
	UBtn* m_MBTN[11];

	CComboBox Cbox[4];
	CEdit m_Edit[4];
	CStatic m_CStatic[3];
	UBtn m_Select[3];
	
	FoodList* FList;
	TableList* TList;
	EmployneeList* EList;
	Table* ������;
	CStatic m_deco;
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void ShowFList(int code);
	void ShowTList(int code);
	void Clear();
	void ClearScreen();
	void ShowFList(int code , int x);
	void ShowEList(int code);
	void SavePosStat();
	void LoadPosStat();
	void UpdateDeco();
	void Show���();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~C����3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void On32771();
	afx_msg void On32774();
};

#ifndef _DEBUG  // ����3View.cpp�� ����� ����
inline C����3Doc* C����3View::GetDocument() const
   { return reinterpret_cast<C����3Doc*>(m_pDocument); }
#endif

