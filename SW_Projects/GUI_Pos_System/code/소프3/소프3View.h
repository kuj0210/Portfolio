
// 소프3View.h : C소프3View 클래스의 인터페이스
//
#include "UBtn.h"
#include "소프3Doc.h"
#pragma once


class C소프3View : public CView
{
protected: // serialization에서만 만들어집니다.
	C소프3View();
	DECLARE_DYNCREATE(C소프3View);

// 특성입니다.
public:
	C소프3Doc* GetDocument() const;

// 작업입니다.
public:
	int season;
	int money;
public:	int key;
public:	CString Skey;
public:
	CTime today;

	C소프3Doc* DOC;
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
	Table* 영수증;
	CStatic m_deco;
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
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
	void Show통계();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~C소프3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void On32771();
	afx_msg void On32774();
};

#ifndef _DEBUG  // 소프3View.cpp의 디버그 버전
inline C소프3Doc* C소프3View::GetDocument() const
   { return reinterpret_cast<C소프3Doc*>(m_pDocument); }
#endif

