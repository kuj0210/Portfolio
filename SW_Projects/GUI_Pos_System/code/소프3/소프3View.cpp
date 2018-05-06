
// 소프3View.cpp : C소프3View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "소프3.h"
#endif

#include "소프3Doc.h"
#include "소프3View.h"
#include "UBtn.h"
#include<stdio.h>
#include<string>
#include"myDlg.h"
#include "비밀번호dlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 기본 제공 버튼 아이디
#define 테이블등록 10
#define 계산 11
#define 테이블확인 12
#define 도움말 13
#define 시재점검 14
//관리자모드 버튼아이디
#define 테이블추가 20
#define 메뉴관리 21
#define 메뉴추가 22
#define 메뉴삭제 23
#define 비밀번호설정 24
#define 직원등록 25
#define 직원해고 26
#define 직원관리 27
#define 통계 28
#define 포스잔액관리 29
#define 계절설정 30
//콤보 박스 아이디
#define ShowT 1
#define 추가버튼 2
#define ShowF 3
#define 지움 15
#define ShowT1 4
#define 계산하기 6
#define 테이블추가완료 7
#define 계절박스 8
#define 테이블삭제완료 9
#define 메뉴타이핑 31
#define 메뉴추가완료 32
#define 메뉴삭제완료 33
#define 삭제메뉴선택 34
#define 직원타이핑 35
#define 직원추가완료 36
#define 메뉴설정중 37
#define 메뉴선택중 38
#define 메뉴변경완료 39
#define 비밀번호설정완료 40
#define 해고직원선택 41
#define 해고완료 42
#define 직원선택중 43
#define 직원정보입력중 44
#define 직원관리완료 45
#define 잔액입력 46
// C소프3View

IMPLEMENT_DYNCREATE(C소프3View, CView)

	BEGIN_MESSAGE_MAP(C소프3View, CView)
		// 표준 인쇄 명령입니다.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_CREATE()
		ON_COMMAND(ID_32771, &C소프3View::On32771)
		ON_COMMAND(ID_32774, &C소프3View::On32774)
	END_MESSAGE_MAP()

	// C소프3View 생성/소멸

	C소프3View::C소프3View()
	{
		today = CTime::GetCurrentTime();
		this->영수증=NULL;
		key=0;
		season=0;
		money=0;
		this->LoadPosStat();
		

		// TODO: 여기에 생성 코드를 추가합니다.
		//1~5번 메세지 id 사용
		this->EList= new EmployneeList();
		printf("E리스트 생성");
		this->FList=new FoodList();
		this->FList->LoadFoodList();
		this->TList=new TableList();

		this->m_BChar[0] ="테이블 등록";
		this->m_BChar[1] ="계산";
		this->m_BChar[2] ="테이블 확인";
		this->m_BChar[3] ="도움말";
		// 20~ 30번 메세지 id사용
		this->m_MBChar[0] ="테이블 추가/삭제";
		this->m_MBChar[1] ="메뉴 관리";
		this->m_MBChar[2] ="메뉴 추가";
		this->m_MBChar[3] ="메뉴 삭제";
		this->m_MBChar[4] ="비밀번호 설정";
		this->m_MBChar[5] ="직원등록";
		this->m_MBChar[6] ="직원해고";
		this->m_MBChar[7] ="직원관리";
		this->m_MBChar[8] ="통계";
		this->m_MBChar[9] ="포스잔액설정";
		this->m_MBChar[10] ="계절설정";
		for(int i=0; i<5; i++){
			this->m_BTN[i]= NULL;
		}
		for(int i=0; i<11; i++){
			this->m_MBTN[i]= NULL;
		}

	}

	C소프3View::~C소프3View()
	{
		this->FList->SaveFoodList();
		this->SavePosStat();
		this->FList->RemoveFoodList();
		this->TList->~TableList();
		printf("E리스트 삭제\n");
		this->EList->~EmployneeList();
		printf("삭제완료\n");
		//delete this->EList;
		//delete this->TList;
		//delete this->FList;
		printf("포인터 할당완료\n");
	}

	BOOL C소프3View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// C소프3View 그리기

	void C소프3View::OnDraw(CDC* /*pDC*/)
	{
		C소프3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	}


	// C소프3View 인쇄

	BOOL C소프3View::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void C소프3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void C소프3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// C소프3View 진단

#ifdef _DEBUG
	void C소프3View::AssertValid() const
	{
		CView::AssertValid();
	}

	void C소프3View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	C소프3Doc* C소프3View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C소프3Doc)));
		return (C소프3Doc*)m_pDocument;
	}
#endif //_DEBUG


	// C소프3View 메시지 처리기


	int C소프3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
		this->UpdateDeco();
		for(int i=0 ;i<4; i++){
			this->m_BTN[i]= new UBtn();
			this->m_BTN[i]->Create(this->m_BChar[i],WS_VISIBLE|WS_CHILD,CRect(0,0,100,80),this,10+i);
			m_BTN[i]->MoveWindow(900,30+50*i,100,50);
		}

		// TODO:  여기에 특수화된 작성 코드를 추가합니다.

		return 0;
	}

	//버튼 메세지 처리
	BOOL C소프3View::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
		WORD wNotifyCode = HIWORD(wParam); // notification code
		WORD wID   = LOWORD(wParam); // item, control, or accelerator identifier
		//10~15번: 사용자 메뉴 코드 , 20~30번: 관리자 메뉴코드
		static Table* p=NULL;//테이블포인터
		static int n=-1,n1=-1;
		static Food* Add=NULL;//음식 포인터
		static Food* fix=NULL;
		// 메뉴추가용 변수들
		static char iName[30];
		static int i가격;
		static int i재고;
		static int i계절;
		static int rm=-1;
		//직원과리용 변수들
		static int i이름;
		static int i나이;
		static int i급여;
		static int i시간;
		static int i종류=0;
		//메뉴관리용 변수들
		static char FName[30];
		static int F가격;
		static int F재고;
		static int F계절;
		static int index=-1;
		//직원 삭제용 변수
		static int Erm=NULL;
		//직원 관리용 변수
		static Employnee* Efix;
		static char Ename[30];
		static int E시급;
		static int E근무시간;
		static int E고용;


		//테이블 등록을 위한 이벤트 처리 부분1: 화면 보이기
		if(wID== 테이블등록){
			this->ClearScreen();
			//테이블에 메뉴를 선택한 후 누를 버튼
			m_Select[0].DestroyWindow();
			m_Select[0].Create("추가",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,추가버튼);
			m_Select[0].MoveWindow(580,100,50,28);
			//초기 화면으로 가기 위한 버튼
			m_Select[1].DestroyWindow();
			m_Select[1].Create("완료",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,지움);
			m_Select[1].MoveWindow(630,100,50,28);
			//데코레이션
			m_Edit[0].DestroyWindow();
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,CRect(150,0,200,50),this,0);
			m_Edit[0].MoveWindow(150,50,700,28);
			m_Edit[0].SetWindowTextA("+테이블 선택+             +메뉴 선택(이름-가격-재고)+");
			//테코레이션
			//구매 등록할 개수를 넣는 텍스트 윈도
			m_Edit[2].DestroyWindow();
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(150,0,200,50),this,0);
			m_Edit[2].MoveWindow(530,100,50,28);
			m_Edit[2].SetWindowTextA("0");
			// Show'?'List(code)- 콤보 박스형태로 ? 리스트를 출력하고 콤보 박스의 id 값은 code로 지정
			this->ShowTList(ShowT);//테이블 리스트를 콤보박스로 보여주고 콤보박스의 아이디는 ShowT.
			this->ShowFList(ShowF);
		}
		//테이블 등록을 위한 이벤트 처리 부분2 :음식 콤보박스가 눌렸고 내부 내용이 변화 하면 실행
		if(wID== ShowF &&wNotifyCode== CBN_SELCHANGE){
			//눌려진곳을 받아오고
			n1=Cbox[0].GetCurSel();
			//받은 메뉴가 계절과 같다면 Food형 포인터 Add에 연결시킨다
			if(FList->GetFood(n1)->season == this->season || FList->GetFood(n1)->season==0){
				Add=this->FList->GetFood(n1);
			}//계절과 다르다면 추가가 불가능 하다 띄우고 커서를 선택안된 상태로 옮긴다.
			else{
				Add=NULL;
				this->MessageBox("계절메뉴, 추가불가능");
				Cbox[0].SetCurSel(-1);
			}

		}//테이블 등록을 위한 이벤트 처리 부분3 :테이블 콤보박스가 눌렸고 내부 내용이 변화 하면 실행
		if(wID== ShowT &&wNotifyCode== CBN_SELCHANGE){
			//콤보박스의 눌린 부분 받기
			n=Cbox[1].GetCurSel();
			p=this->TList->GetTablePointer(n);
			//출력할 테이블 포인터인 p를 영수증 출력에 사용될 포인터 영수증에 넣어줌
			영수증=p; //영수증 출력에 쓰일 포인터

			Cbox[2].DestroyWindow();

			CString A;//출력을 위해 사용될 스트링 객체
			int total=0;//총액이 저장될 곳
			//선택된 테이블의 포인터가 존재하고 테이블 내부의 판매용 리스트가 존재하면 
			if(p && p->InTList.Ffirst){
				Food* Food= p->InTList.Ffirst; //Food는 판매용 리스트의 1번 노드
				//테이블에 등록된 음식을 보여줄 콤보박스
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
				Cbox[2].MoveWindow(150,200,200,300);

				while(Food){ 
					A.Format("%s , %d 개",Food->Fname,Food->재고);
					total+=Food->재고*Food->가격;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
				A.Format("총액 : %d원",total);
				Cbox[2].InsertString(-1,A);
				Cbox[2].SetCurSel(-1);
			}


		}
		//테이블 등록을 위한 이벤트 처리 부분4 :추가 버튼이 눌렸을 경우
		if(wID==추가버튼){
			//테이블과 등록된 음식리스트에서 가져온 값이 있다면
			if(p&&Add){
				//edit박스에서 입력된 수량을 숫자로 바꿈
				char s[5];
				m_Edit[2].GetWindowTextA(s,5);
				int k=0;
				k=atoi(s);
				//구매하려는 값이 재고 값보다 작거나 같다면 추가한다
				if(Add->재고-k>=0){
					//구매 완료 후 값이 원래 재고의 45% 이하라면 재고 부족 메세지 출력
					if((Add->재고)-k <= (Add->재고)*0.45){this->MessageBox("재고 부족!");}
					Add->재고-=k;//재고값 감소
					Add->판매량+=k;//판매량 증가
					p->InTList.AddFoodList(Add,k);//판매리스트에 추가
					//내용을 출력할 C콤보박스 생성
					Cbox[2].DestroyWindow();
					Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
					Cbox[2].MoveWindow(150,200,200,300);
					Food* Food = p->InTList.Ffirst;
					CString A;
					int total=0;
					//C박스에 내용 채우기
					while(Food){ 
						A.Format("%s , %d 개",Food->Fname,Food->재고);
						total+=Food->재고*Food->가격;
						Cbox[2].AddString(A);
						Food=Food->next;
					}
					A.Format("총액 : %d원",total);
					Cbox[2].InsertString(-1,A);
					Cbox[2].SetCurSel(-1);
				}
				else {
					//재고량 초과라면 초과 메세지 출력
					this->MessageBox("재고량 초과!");
				}

			}
		}//초기화면으로 가기위한 버튼.
		if(wID==지움){
			n=-1;
			n1=-1;
			p=NULL;
			Add=NULL;
			this->ClearScreen();
			UpdateDeco();
		}
		if(wID==도움말){
			this->MessageBox("1.테이블등록: 테이블을 선택하고 메뉴를 선택한 뒤 개수를 입력하고 추가.완료를 하면(등록 성공,실패와 관계없이) 초기화면 이동\n\n2.계산: 주문이 등록된 테이블을 선택하면 주문 리스트와 완료버튼이 뜬다. 이 때 주문 목록이 없다면 리스트과 계산버튼은 보이지 않으며 완료를 누르고 영수증의 종류를 택하면 영수증과 함께 계산완료.\n\n3.테이블 확인:테이블을 택하면 테이블별 메뉴를 볼 수 있다 없다면 메뉴는 뜨지않는다. 완료를 누르면 어떤 상황에서도 초기화면으로 돌아간다(테이블 확인에서 바로 계산하기 가능)");
		}
		//테이블 확인 이베트를 처리
		if(wID==테이블확인){
			this->ClearScreen();
			ShowTList(ShowT1);
			m_Select[1].DestroyWindow();
			m_Select[1].Create("끝내기",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,지움);
			m_Select[1].MoveWindow(800,100,50,30);
		}
		//계산 이벤트 처리1:화면 디자인
		if(wID==계산){
			//n~n1,p는 테이블 등록에서 사용되었으므로 초기화
			n=-1; n1=-1;
			p=NULL;
			//화면 초기화
			this->ClearScreen();
			ShowTList(ShowT1);
			//테이블 출력: 테이블이 출력된 뒤 선택되면 p에 테이블 값이 저장된다


			CString A;
			int total=0;
			//선택된 테이블이 있고 테이블안에 리스트가 존재하면 박스에 리스트내용을 추가함
			if(p && p->InTList.Ffirst){
				Food* Food= p->InTList.Ffirst;
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
				Cbox[2].MoveWindow(300,100,200,300);
				while(Food){ 
					A.Format("%s , %d 개",Food->Fname,Food->재고);
					total+=Food->재고*Food->가격;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
			}
			//초기화면가기 버튼 출력
			m_Select[1].DestroyWindow();
			m_Select[1].Create("끝내기",WS_VISIBLE|WS_CHILD,CRect(800,100,50,50),this,지움);
			m_Select[1].MoveWindow(800,100,50,30);
		}
		//계산 이벤트 처리2:선택된 값 처리와 화면 출력
		if(wID==ShowT1){
			//선택된 곳의 테이블 포인터 받아오기
			n=Cbox[1].GetCurSel();
			p=this->TList->GetTablePointer(n);
			//영수증을 위한 포인터 p
			영수증=p;
			Cbox[2].DestroyWindow();
			CString A;
			int total=0;
			//받아온 테이블의 내부 리스트 출력
			if(p){//테이블이 존재하면
				m_Select[0].DestroyWindow();

				Food* Food= p->InTList.Ffirst;
				//음식리스트가 존재하면 계산하기 버튼 보이기
				if(Food!=0){
					Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
					Cbox[2].MoveWindow(300,100,200,300);
					m_Select[0].Create("계산하기",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,계산하기);
					m_Select[0].MoveWindow(600,100,100,28);
				}
				//cbox에 리스트 추가
				while(Food){ 
					A.Format("%s , %d 개",Food->Fname,Food->재고);
					total+=Food->재고*Food->가격;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
				A.Format("총액 : %d원",total);
				Cbox[2].InsertString(-1,A);
				Cbox[2].SetCurSel(-1);
			}
		}
		//계산 이벤트 처리3:계산완료
		if(wID==계산하기){
			ClearScreen();
			영수증=p; //영수증 출력을 위한 포인터 p
			int total=0;
			myDlg X(this);
			CString A;
			Food* p=영수증->InTList.Ffirst;
			//영수증 출력용 윈도우
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,CRect(150,0,200,50),this,0);
			m_Edit[0].MoveWindow(150,80,300,400);

			//영수증의 종류를 입력받는 다이얼로그
			if((X.DoModal()!=IDOK)){//리스트포함 출력
				while(p){
					total +=p->재고*p->가격;
					A.Format("%s, %d개 %d원 = %d원\r\n",p->Fname,p->재고,p->가격,p->재고*p->가격);
					m_Edit[0].SetSel(0,0);
					m_Edit[0].ReplaceSel(A);
					p=p->next;

				}
				A.Format("\r\n");
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);
				A.Format("총액: %d원\r\n",total);
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);

			}
			else{//총액만출력
				while(p){
					total +=p->재고*p->가격;
					p=p->next;
				}
				A.Format("총액: %d원\r\n",total);
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);


			}
			this->money+=total;
			영수증->InTList.RemoveFoodList(); //계산완료 후 테이블에 등록된 리스트 삭제
			this->UpdateDeco();
		}
		//테이블 추가 삭제를 위한 이벤트
		if(wID==테이블추가){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("테이블추가\n");
			//리스트가 등록된 테이블이 있는지 확인
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("계산중인 테이블이 잇습니다. 계산을 완료해주세요"); x=1;break;}
				p=p->next;
			}//없다면
			if(!x){
				p= this->TList->TFirst;
				printf("테이블추가실행\n");



				//추가 또는 삭제할 개수를 받는 곳
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(150,0,200,50),this,0);
				m_Edit[0].MoveWindow(200,70,50,60);
				//추가버튼
				this->m_Select[0].Create("추가",WS_VISIBLE|WS_CHILD,CRect(150,0,200,50),this,테이블추가완료);
				this->m_Select[0].MoveWindow(250,70,50,30);		
				//삭제버튼
				this->m_Select[1].Create("삭제",WS_VISIBLE|WS_CHILD,CRect(150,0,200,50),this,테이블삭제완료);
				this->m_Select[1].MoveWindow(250,100,50,30);


			}

		}//테이블 추가/삭제 이벤트 - 추가하기
		if(wID==테이블추가완료){

			char s[5];
			m_Edit[0].GetWindowTextA(s,5);
			int k=0;
			k=atoi(s);
			for(int i=0; i<k ;i++){
				this->TList->AddTableList();
			}
			this->MessageBox("추가완료");
			ClearScreen();
		}
		//테이블 추가/삭제이벤트-삭제
		if(wID==테이블삭제완료){
			char s[5];
			m_Edit[0].GetWindowTextA(s,5);
			int k=0;
			k=atoi(s);
			for(int i=0; i<k ;i++){
				this->TList->RemoveTableNode(1);
			}
			this->MessageBox("삭제완료");
			ClearScreen();
		}
		//포스기 내부의 계절 변수를 변경
		if(wID==계절설정){
			ClearScreen();
			this->m_CStatic[0].Create("계절을 선택하여 주세요",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
			this->m_CStatic[0].MoveWindow(150,50,500,30);
			Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 계절박스);
			Cbox[2].MoveWindow(150,150,100,300);
			Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("봄");Cbox[2].AddString("여름");Cbox[2].AddString("가을");Cbox[2].AddString("겨울");

			m_Select[0].DestroyWindow();
			m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,지움);
			m_Select[0].MoveWindow(250,150,50,30);
		}//계절변수를 직접 변경하는 곳
		if(wID==계절박스){
			this->season=Cbox[2].GetCurSel();
			if(season==-1){ season =0;}
		}

		//신메뉴 추가 이벤트 처리:화면
		if(wID== 메뉴추가){
			ClearScreen();
			//데코레이션
			this->m_CStatic[0].Create("이름 + 가격 + 재고 + 계절  순서로 입력 해주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,0,200,50),this,0);
			m_CStatic[0].MoveWindow(200,100,400,30);
			//추가완료버튼
			this->m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,메뉴추가완료);
			this->m_Select[0].MoveWindow(650,150,50,30);
			//계절정보를 입력받을 C콤보박스
			Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this , 메뉴타이핑);
			Cbox[2].MoveWindow(380,150,140,300);
			Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("봄");Cbox[2].AddString("여름");Cbox[2].AddString("가을");Cbox[2].AddString("겨울");
			Cbox[2].SetCurSel(4);//기본계절은 NO_SEASON
			// 순서대로 이름 가격 재고 를 입력받을 텍스트 박스
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,메뉴타이핑);
			m_Edit[0].MoveWindow(200,150,60,30);
			m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,메뉴타이핑);
			m_Edit[1].MoveWindow(270,150,40,30);
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,메뉴타이핑);
			m_Edit[2].MoveWindow(320,150,40,30);

		}
		//신메뉴 추가 이벤트 처리: 3개의 텍스트 박스중 입력이 있거나 콤보박스에서 계절이 선택될 때 마다 호출됨
		if( wID==메뉴타이핑 && wNotifyCode == EN_CHANGE ||wID==메뉴타이핑 && wNotifyCode == CBN_SELCHANGE ){
			char A[30]; 
			m_Edit[0].GetWindowText(A,30);
			printf("1:%s\n",A);
			strcpy_s(iName,A);
			printf("1:%s\n",iName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			i가격 =atoi(A);
			printf("2:%d\n",i가격);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			i재고 =atoi(A);
			printf("3:%d\n",i재고);

			i계절= Cbox[2].GetCurSel();
			//메뉴를 위해 필요한 데이터를 포맷에 맞게 변경
		}
		//신메뉴 추가 이벤트 처리: 완료버튼눌림
		if(wID==메뉴추가완료){
			ClearScreen();
			//3개의 텍스트박스에 값이 없고 계절마저 기본값이라면 경고메세지 출력
			if(iName[0]==NULL &&i가격==0 &&i재고==NULL && i계절==0){
				this->MessageBox("추가할 것이 없습니다");
			}
			else{//입력받은 대로 추가
				this->FList->AddFoodList(iName,i가격,i재고,0,i계절);
				this->MessageBox("추가 완료");
			}

		}
		//삭제이벤트 1 : 화면 그리기
		if(wID==메뉴삭제){
			rm=-1;
			ClearScreen();

			Table* p= this->TList->TFirst;
			int x=0;
			printf("메뉴삭제\n");
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("계산중인 테이블이 잇습니다. 계산을 완료해주세요"); x=1;break;}
				p=p->next;
			}//계산중에 삭제가되면 안되므로 계산중인 테이블이 없는지 확인
			if(!x){
				this->m_CStatic[0].Create("제거할 메뉴를 선택하여 주세요",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
				this->m_CStatic[0].MoveWindow(150,50,500,30);
				ShowFList(삭제메뉴선택,0); //0번 박스 사용
				this->m_Select[0].Create("삭제",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,메뉴삭제완료);
				this->m_Select[0].MoveWindow(500,100,50,30);
			}//없다면
		}
		//삭제이벤트 2: 콤보박스 처리
		if(wID==삭제메뉴선택 && wNotifyCode==CBN_SELCHANGE){
			rm=Cbox[0].GetCurSel();
		}
		//삭제이벤트 3: 삭제하기 수행
		if(wID==메뉴삭제완료){

			if(rm!=-1){
				this->FList->RemoveFoodNode(rm);
				ClearScreen();
				rm=-1; //초기화
				this->MessageBox("삭제완료");
			}
		}
		//직원등록
		if(wID==직원등록){
			Employnee* p=this->EList->EFirst;
			while(p){
				printf("이름: %s\n",p->name);
				p=p->next;
			}
			ClearScreen();
			this->m_CStatic[0].Create("이름 + 나이 + 급여 + 시간 + 고용  순서로 입력 해주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,0,200,50),this,0);
			m_CStatic[0].MoveWindow(200,100,400,30);
			this->m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,직원추가완료);
			this->m_Select[0].MoveWindow(650,150,50,30);
			Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,직원정보입력중);
			Cbox[1].MoveWindow(482,150,80,100);
			Cbox[1].AddString("비정규");Cbox[1].AddString("정규");
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,직원타이핑);
			m_Edit[0].MoveWindow(200,150,60,30);
			m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,직원타이핑);
			m_Edit[1].MoveWindow(270,150,40,30);
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,직원타이핑);
			m_Edit[2].MoveWindow(320,150,40,30);
			m_Edit[3].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,직원타이핑);
			m_Edit[3].MoveWindow(380,150,100,30);
		}
		if( wID==직원타이핑 && wNotifyCode == EN_CHANGE ||wID==직원타이핑 && wNotifyCode == CBN_SELCHANGE ){
			char A[30]; 
			m_Edit[0].GetWindowText(A,30);
			i종류=0;
			printf("1:%s\n",A);
			strcpy_s(iName,A);
			printf("1:%s\n",iName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			i나이 =atoi(A);
			printf("2:%d\n",i나이);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			i급여 =atoi(A);
			printf("3:%d\n",i급여);

			m_Edit[3].GetWindowText(A,30);
			printf("4:%s\n",A);
			i시간 =atoi(A);
			printf("4:%d\n",i시간);
			i종류=100+Cbox[1].GetCurSel();
			printf("입력정보 직원코드:%d\n",i종류);


		}
		if(wID==직원추가완료){
			printf("직원추가 직원코드:%d",i종류);

			if(iName[0]==NULL &&i나이==0 &&i급여==NULL && i종류==0){
				this->MessageBox("추가할 것이 없습니다");
			}
			else{
				i종류=100+Cbox[1].GetCurSel();
				this->EList->AddE(iName,i나이,i급여,i시간,i종류);
				this->MessageBox("추가 완료");
			}
			ClearScreen();
		}

		if(wID==메뉴관리){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("메뉴관리\n");
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("계산중인 테이블이 잇습니다. 계산을 완료해주세요"); x=1;break;}
				p=p->next;
			}
			if(!x){
				ClearScreen();
				//모든 메뉴 출력
				this->ShowFList(메뉴선택중,3);

				//데코레이션+출력
				this->m_CStatic[0].Create("이름 + 단가 + 재고 순서로 입력 해주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,200,400,30);

				//메뉴의 변경 사항을 저장하는 버튼
				this->m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(600,350,50,30),this,메뉴변경완료);
				this->m_Select[0].MoveWindow(520,250,50,30);

				//데코레이션+설명
				this->m_CStatic[1].Create("관리메뉴선택",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[1].MoveWindow(150,100,120,30);
				this->m_CStatic[2].Create("기존의 메뉴의 이름, 재고, 가격, 판매 계절을 변경 할 수 있습니다.",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[2].MoveWindow(150,50,500,30);
				//메뉴의 계절 정보를 수정할 박스
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,메뉴설정중);
				Cbox[2].MoveWindow(360,250,140,300);
				Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("봄");Cbox[2].AddString("여름");Cbox[2].AddString("가을");Cbox[2].AddString("겨울");
				Cbox[2].SetCurSel(4);
				//메뉴의 내용을 수정할 텍스트 윈도
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,메뉴설정중);
				m_Edit[0].MoveWindow(150,250,60,30);//이름
				m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,메뉴설정중);
				m_Edit[1].MoveWindow(230,250,50,30);//재고
				m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,메뉴설정중);
				m_Edit[2].MoveWindow(290,250,50,30);//가격

			}
		}
		if(wID==메뉴선택중 && wNotifyCode==CBN_SELCHANGE){
			printf("메뉴조정중\n");
			m_Edit[0].Clear();
			m_Edit[1].Clear();
			if(Cbox[0].GetCurSel()!=-1){
				printf("메뉴조정실행\n");
				fix=this->FList->GetFood(Cbox[0].GetCurSel());
				index=Cbox[0].GetCurSel();
				m_Edit[0].Clear();
				m_Edit[1].Clear();
				m_Edit[0].SetWindowTextA(fix->Fname);
				CString A;
				A.Format("%d",fix->가격);
				m_Edit[1].SetWindowTextA((A));
				A.Format("%d",fix->재고);
				m_Edit[2].SetWindowTextA(A);
				Cbox[2].SetCurSel(fix->season);

			}
		}
		if((wID==메뉴설정중 && wNotifyCode==EN_CHANGE) || (wID==메뉴설정중 && wNotifyCode==CBN_SELCHANGE)  ){
			printf("메뉴설정중\n");
			char A[30]; 
			m_Edit[0].GetWindowText(FName,30);
			printf("1:%s\n",FName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			F가격 =atoi(A);
			printf("2:%d\n",F가격);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			F재고 =atoi(A);
			printf("3:%d\n",F재고);
			F계절 =Cbox[2].GetCurSel();
			printf("4:%d\n",F계절);
		}
		if(wID==메뉴변경완료){
			fix->ChangeName(FName);
			printf("다\n");
			fix->가격=F가격;
			fix->재고=F재고;
			fix->season=F계절;
			printf("라\n");
			this->MessageBox("수정완료!");
			this->ClearScreen();
		}
		if(wID==비밀번호설정){
			this->ClearScreen();
			this->m_CStatic[1].Create("변경할 비밀번호를 입력해주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,300,50),this,0);
			m_CStatic[1].MoveWindow(150,100,300,30);
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER|ES_NUMBER,CRect(200,150,60,30),this,메뉴설정중);
			m_Edit[0].MoveWindow(150,150,60,30);//이름
			this->m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,비밀번호설정완료);
			this->m_Select[0].MoveWindow(210,150,50,30);
		}
		if(wID==비밀번호설정완료){
			int nkey;
			char A[5];
			m_Edit[0].GetWindowText(A,30);
			nkey =atoi(A);
			printf("nkey:%d\n",nkey);
			this->key =nkey;
			printf("key:%d\n",nkey);
			CString S;
			S.Format("비밀번호 변경완료!\n새로운 비밀번호: %d",key);
			this->MessageBox(S);
			ClearScreen();
		}


		//메뉴삭제이벤트 1 : 화면 그리기
		if(wID==직원해고){
			Erm=-1;
			ClearScreen();

			Employnee* p= this->EList->EFirst;
			int x=0;
			printf("직원삭제\n");
			if(!x){
				this->m_CStatic[0].Create("해고할 직원을 선택하여 주세요",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
				this->m_CStatic[0].MoveWindow(150,50,500,30);
				ShowEList(해고직원선택); //0번 박스 사용
				this->m_Select[0].Create("삭제",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,해고완료);
				this->m_Select[0].MoveWindow(500,100,50,30);
			}//없다면
		}
		//삭제이벤트 2: 콤보박스 처리
		if(wID==해고직원선택 && wNotifyCode==CBN_SELCHANGE){
			if(Cbox[2].GetCurSel()!=-1)
				Erm=Cbox[2].GetCurSel();
		}
		//삭제이벤트 3: 삭제하기 수행
		if(wID==해고완료){

			if(Erm!=-1){
				printf("%d 번 직원삭제",Erm);
				this->EList->RemoveENode(Erm);
				printf("화면지우기");
				ClearScreen();
				this->MessageBox("해고완료");
			}
		}


		if(wID==직원관리){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("직원관리\n");
			if(!x){
				ClearScreen();
				//모든 메뉴 출력
				this->ShowEList(직원선택중);

				//데코레이션+출력
				this->m_CStatic[0].Create("이름, 시급, 근무시간, 고용타입 순서로 입력 해주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,200,400,30);

				//메뉴의 변경 사항을 저장하는 버튼
				this->m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(600,350,50,30),this,직원관리완료);
				this->m_Select[0].MoveWindow(520,250,50,30);

				//데코레이션+설명
				this->m_CStatic[1].Create("직원",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,50,100),this,0);
				m_CStatic[1].MoveWindow(150,100,50,30);
				this->m_CStatic[2].Create("기존의 직원의 이름, 시급, 근무시간, 고용타입을 변경 할 수 있습니다.",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[2].MoveWindow(150,50,500,30);
				//고용타입을 정할 박스
				Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,직원정보입력중);
				Cbox[1].MoveWindow(360,250,140,300);
				Cbox[1].AddString("비정규");Cbox[1].AddString("정규");

				//직원의 내용을 수정할 텍스트 윈도
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,직원정보입력중);
				m_Edit[0].MoveWindow(150,250,60,30);//이름
				m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,직원정보입력중);
				m_Edit[1].MoveWindow(230,250,50,30);//시급
				m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,직원정보입력중);
				m_Edit[2].MoveWindow(290,250,50,30);//근무시간

			}
		}
		if(wID==직원선택중 && wNotifyCode==CBN_SELCHANGE){
			printf("직원선택중\n");
			m_Edit[0].Clear();
			m_Edit[1].Clear();
			if(Cbox[0].GetCurSel()!=-1){
				printf("직원선택실행\n");
				Efix=this->EList->GetE(Cbox[2].GetCurSel());
				index=Cbox[0].GetCurSel();
				m_Edit[0].Clear();
				m_Edit[1].Clear();
				m_Edit[0].SetWindowTextA(Efix->name);
				CString A;
				A.Format("%d",Efix->급여계수);
				m_Edit[1].SetWindowTextA((A));
				A.Format("%d",Efix->근무시간);
				m_Edit[2].SetWindowTextA(A);
				Cbox[1].SetCurSel((Efix->고용코드-100));

			}
		}
		if((wID==직원정보입력중 && wNotifyCode==EN_CHANGE) || (wID==직원정보입력중 && wNotifyCode==CBN_SELCHANGE)  ){
			printf("메뉴설정중\n");
			char A[30]; 
			m_Edit[0].GetWindowText(Ename,30);
			printf("1:%s\n",FName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			E시급 =atoi(A);
			printf("2:%d\n",E시급);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			E근무시간 =atoi(A);
			printf("3:%d\n",E근무시간);
			E고용 =100+ Cbox[1].GetCurSel();
			printf("4:%d\n",E고용);
		}
		if(wID==직원관리완료){
			delete Efix->name;
			Efix->name=new char [strlen(Ename)+1];
			for(int i=0; i<strlen(Ename)+1; i++){
				Efix->name[i]=NULL;
			}
			for(int i=0; i<strlen(Ename); i++){
				Efix->name[i]=Ename[i];
			}
			printf("1");
			Efix->근무시간=E근무시간;
			printf("2");
			Efix->급여계수=E시급;
			printf("3");
			Efix->고용코드=E고용;
			printf("4");
			this->MessageBox("수정완료!");
			this->ClearScreen();
		}
		if(wID==포스잔액관리){
			this->ClearScreen();
			this->m_CStatic[0].Create("변경된 포스기의 잔액을 입력해 주세요",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
			m_CStatic[0].MoveWindow(150,100,400,30);
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER|ES_NUMBER,CRect(200,150,60,30),this,잔액입력);
			m_Edit[0].MoveWindow(150,150,100,30);//금액이 입력될 곳
			CString m;
			m.Format("%d",this->money);
			m_Edit[0].SetWindowTextA(m);
			m_Select[0].DestroyWindow();
			m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,지움);
			m_Select[0].MoveWindow(260,150,50,30);
		}
		if(wID==잔액입력 && wNotifyCode==EN_CHANGE){
			char a[50];
			m_Edit[0].GetWindowText(a,50);
			this->money = atoi(a);
		}
		if(wID==통계){
			this->ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("테이블추가\n");
			//리스트가 등록된 테이블이 있는지 확인
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("계산중인 테이블이 잇습니다. 계산을 완료해주세요"); x=1;break;}
				p=p->next;
			}//없다면
			if(!x){
				this->m_CStatic[0].Create("마지막 통계를 기준으로 확인 직전까지의 판매량을 출력합니다",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,100,400,30);
				this->Show통계();
				m_Select[0].DestroyWindow();
				m_Select[0].Create("완료",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,지움);
				m_Select[0].MoveWindow(650,150,50,30);
			}
		}
		return CView::OnCommand(wParam, lParam);
	}

	//관리자 메뉴 실행 클릭
	void C소프3View::On32771()
	{
		// TODO: 여기에 명령 처리기 코드를 추가합니다.
		비밀번호dlg A(this);
		//비밀번호가 맞다면 보여줄것
		if(A.DoModal()==IDOK){
			if(this->key == atoi(this->Skey)){
				for(int i=0 ;i<11; i++){
					if(this->m_MBTN[i]==NULL){
						this->m_MBTN[i]= new UBtn();
					}
					this->m_MBTN[i]->Create(this->m_MBChar[i],WS_VISIBLE|WS_CHILD,CRect(0,0,100,80),this,20+i);
					m_MBTN[i]->MoveWindow(0,30+30*i,125,30);

				}
			}
			else
				this->MessageBox(" 비밀번호 오류");
		}



	}

	//관리자모드 종료 메뉴 클릭
	void C소프3View::On32774()
	{
		if(this->m_MBTN[0]!=NULL)
			for(int i=0; i<11; i++){ this->m_MBTN[i]->DestroyWindow(); }
			// TODO: 여기에 명령 처리기 코드를 추가합니다.
	}

	void C소프3View::ShowFList(int code =ShowF){
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,code);
		Cbox[0].MoveWindow(300,100,200,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){
			if(p->season == this->season  || p->season ==0){
				A.Format("+ %s + %d + %d +",p->Fname,p->가격,p->재고);
				this->Cbox[0].AddString(A);
			}
			else{
				A.Format("계절메뉴. 선택불가",p->Fname,p->가격,p->재고);
				this->Cbox[0].AddString(A);
			}
			p=p->next;
		}	

	}
	void C소프3View::ShowFList(int code , int x){
		x=0;
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,code);
		Cbox[0].MoveWindow(300,100,200,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){

			A.Format("+ %s + %d + %d +",p->Fname,p->가격,p->재고);
			this->Cbox[0].AddString(A);

			p=p->next;
		}	

	}

	void C소프3View::ShowTList(int code=ShowT){
		Cbox[1].DestroyWindow();
		Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , code);
		Cbox[1].MoveWindow(150,100,100,300);
		CString A;
		for(int i=0; i<this->TList->Tcount; i++){ 
			A.Format("%d번 테이블",i+1);
			Cbox[1].AddString(A);
		}
	}

	void C소프3View::ShowEList(int code){
		Cbox[2].DestroyWindow();
		Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , code);
		Cbox[2].MoveWindow(150,100,300,300);
		CString A;
		Employnee* p =this->EList->EFirst;
		while(p){
			A.Format("이름:%s-급여:%d-근무시간:%d",p->name,p->급여계수,p->근무시간);
			Cbox[2].AddString(A);
			p=p->next;
		}
	}
	void C소프3View:: Clear(){
		ClearScreen();
		for(int i=0; i< 3 ; i++){
			m_BTN[i]->DestroyWindow();
		}

	}
	void C소프3View:: ClearScreen(){
		for(int i=0; i< sizeof(m_Edit)/sizeof(CEdit) ; i++){
			m_Edit[i].DestroyWindow();
		}

		for(int i=0; i< sizeof(m_CStatic)/sizeof(CStatic) ; i++){
			m_CStatic[i].DestroyWindow();
		}

		for(int i=0; i< sizeof(m_Select)/sizeof(UBtn) ; i++){
			m_Select[i].DestroyWindow();
		}
		for(int i=0; i< sizeof(Cbox)/sizeof(CComboBox) ; i++){
			Cbox[i].DestroyWindow();
		}


	}

	void C소프3View::SavePosStat(){
		FILE *fp =NULL;
		fopen_s(&fp,"PosData.txt","wt");
		if(fp==NULL){return;}
		fprintf(fp," %d %d %d",this->money,this->key,this->season);
		fclose(fp);
	}

	void C소프3View::LoadPosStat(){
		FILE *fp=NULL;
		fopen_s(&fp,"PosData.txt","rt");
		if(fp==NULL){return;}
		int a=0,b=0,c=0;
		fscanf_s(fp," %d",&a);
		fscanf_s(fp," %d",&b);
		fscanf_s(fp," %d",&c);
		printf("a,b,c : %d | %d | %d",a,b,c);
		fclose(fp);
		this->money=a;
		this->key=b;
		this->season=c;
		printf("Load결과: %d %d %d",this->money,this->key,this->season);
	}
	void C소프3View::UpdateDeco(){

		this->m_deco.DestroyWindow();
		CString D;
		char* sea[5]={"일반","봄","여름","가을","겨울"};
		D.Format("PosSystem                                                                                                                                     잔고:%d                         계절: %s 메뉴 판매",this->money,sea[this->season]);
		this->m_deco.Create(D,WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
		this->m_deco.MoveWindow(0,0,1000,30);

	}
	void C소프3View::Show통계(){
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,0);
		Cbox[0].MoveWindow(150,150,500,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){
			A.Format("+ 이름: %s +판매량: %d +판매액: %d +",p->Fname,p->판매량,p->판매량*p->가격);
			this->Cbox[0].AddString(A);
			p->판매량=0;
			p=p->next;
		}	
	}