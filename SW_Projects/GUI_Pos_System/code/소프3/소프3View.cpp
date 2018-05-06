
// ����3View.cpp : C����3View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "����3.h"
#endif

#include "����3Doc.h"
#include "����3View.h"
#include "UBtn.h"
#include<stdio.h>
#include<string>
#include"myDlg.h"
#include "��й�ȣdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �⺻ ���� ��ư ���̵�
#define ���̺��� 10
#define ��� 11
#define ���̺�Ȯ�� 12
#define ���� 13
#define �������� 14
//�����ڸ�� ��ư���̵�
#define ���̺��߰� 20
#define �޴����� 21
#define �޴��߰� 22
#define �޴����� 23
#define ��й�ȣ���� 24
#define ������� 25
#define �����ذ� 26
#define �������� 27
#define ��� 28
#define �����ܾװ��� 29
#define �������� 30
//�޺� �ڽ� ���̵�
#define ShowT 1
#define �߰���ư 2
#define ShowF 3
#define ���� 15
#define ShowT1 4
#define ����ϱ� 6
#define ���̺��߰��Ϸ� 7
#define �����ڽ� 8
#define ���̺�����Ϸ� 9
#define �޴�Ÿ���� 31
#define �޴��߰��Ϸ� 32
#define �޴������Ϸ� 33
#define �����޴����� 34
#define ����Ÿ���� 35
#define �����߰��Ϸ� 36
#define �޴������� 37
#define �޴������� 38
#define �޴�����Ϸ� 39
#define ��й�ȣ�����Ϸ� 40
#define �ذ��������� 41
#define �ذ�Ϸ� 42
#define ���������� 43
#define ���������Է��� 44
#define ���������Ϸ� 45
#define �ܾ��Է� 46
// C����3View

IMPLEMENT_DYNCREATE(C����3View, CView)

	BEGIN_MESSAGE_MAP(C����3View, CView)
		// ǥ�� �μ� ����Դϴ�.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_CREATE()
		ON_COMMAND(ID_32771, &C����3View::On32771)
		ON_COMMAND(ID_32774, &C����3View::On32774)
	END_MESSAGE_MAP()

	// C����3View ����/�Ҹ�

	C����3View::C����3View()
	{
		today = CTime::GetCurrentTime();
		this->������=NULL;
		key=0;
		season=0;
		money=0;
		this->LoadPosStat();
		

		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		//1~5�� �޼��� id ���
		this->EList= new EmployneeList();
		printf("E����Ʈ ����");
		this->FList=new FoodList();
		this->FList->LoadFoodList();
		this->TList=new TableList();

		this->m_BChar[0] ="���̺� ���";
		this->m_BChar[1] ="���";
		this->m_BChar[2] ="���̺� Ȯ��";
		this->m_BChar[3] ="����";
		// 20~ 30�� �޼��� id���
		this->m_MBChar[0] ="���̺� �߰�/����";
		this->m_MBChar[1] ="�޴� ����";
		this->m_MBChar[2] ="�޴� �߰�";
		this->m_MBChar[3] ="�޴� ����";
		this->m_MBChar[4] ="��й�ȣ ����";
		this->m_MBChar[5] ="�������";
		this->m_MBChar[6] ="�����ذ�";
		this->m_MBChar[7] ="��������";
		this->m_MBChar[8] ="���";
		this->m_MBChar[9] ="�����ܾ׼���";
		this->m_MBChar[10] ="��������";
		for(int i=0; i<5; i++){
			this->m_BTN[i]= NULL;
		}
		for(int i=0; i<11; i++){
			this->m_MBTN[i]= NULL;
		}

	}

	C����3View::~C����3View()
	{
		this->FList->SaveFoodList();
		this->SavePosStat();
		this->FList->RemoveFoodList();
		this->TList->~TableList();
		printf("E����Ʈ ����\n");
		this->EList->~EmployneeList();
		printf("�����Ϸ�\n");
		//delete this->EList;
		//delete this->TList;
		//delete this->FList;
		printf("������ �Ҵ�Ϸ�\n");
	}

	BOOL C����3View::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
		//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

		return CView::PreCreateWindow(cs);
	}

	// C����3View �׸���

	void C����3View::OnDraw(CDC* /*pDC*/)
	{
		C����3Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	}


	// C����3View �μ�

	BOOL C����3View::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// �⺻���� �غ�
		return DoPreparePrinting(pInfo);
	}

	void C����3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	}

	void C����3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
	}


	// C����3View ����

#ifdef _DEBUG
	void C����3View::AssertValid() const
	{
		CView::AssertValid();
	}

	void C����3View::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	C����3Doc* C����3View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C����3Doc)));
		return (C����3Doc*)m_pDocument;
	}
#endif //_DEBUG


	// C����3View �޽��� ó����


	int C����3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
		this->UpdateDeco();
		for(int i=0 ;i<4; i++){
			this->m_BTN[i]= new UBtn();
			this->m_BTN[i]->Create(this->m_BChar[i],WS_VISIBLE|WS_CHILD,CRect(0,0,100,80),this,10+i);
			m_BTN[i]->MoveWindow(900,30+50*i,100,50);
		}

		// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

		return 0;
	}

	//��ư �޼��� ó��
	BOOL C����3View::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		WORD wNotifyCode = HIWORD(wParam); // notification code
		WORD wID   = LOWORD(wParam); // item, control, or accelerator identifier
		//10~15��: ����� �޴� �ڵ� , 20~30��: ������ �޴��ڵ�
		static Table* p=NULL;//���̺�������
		static int n=-1,n1=-1;
		static Food* Add=NULL;//���� ������
		static Food* fix=NULL;
		// �޴��߰��� ������
		static char iName[30];
		static int i����;
		static int i���;
		static int i����;
		static int rm=-1;
		//���������� ������
		static int i�̸�;
		static int i����;
		static int i�޿�;
		static int i�ð�;
		static int i����=0;
		//�޴������� ������
		static char FName[30];
		static int F����;
		static int F���;
		static int F����;
		static int index=-1;
		//���� ������ ����
		static int Erm=NULL;
		//���� ������ ����
		static Employnee* Efix;
		static char Ename[30];
		static int E�ñ�;
		static int E�ٹ��ð�;
		static int E���;


		//���̺� ����� ���� �̺�Ʈ ó�� �κ�1: ȭ�� ���̱�
		if(wID== ���̺���){
			this->ClearScreen();
			//���̺� �޴��� ������ �� ���� ��ư
			m_Select[0].DestroyWindow();
			m_Select[0].Create("�߰�",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,�߰���ư);
			m_Select[0].MoveWindow(580,100,50,28);
			//�ʱ� ȭ������ ���� ���� ��ư
			m_Select[1].DestroyWindow();
			m_Select[1].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,����);
			m_Select[1].MoveWindow(630,100,50,28);
			//���ڷ��̼�
			m_Edit[0].DestroyWindow();
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,CRect(150,0,200,50),this,0);
			m_Edit[0].MoveWindow(150,50,700,28);
			m_Edit[0].SetWindowTextA("+���̺� ����+             +�޴� ����(�̸�-����-���)+");
			//���ڷ��̼�
			//���� ����� ������ �ִ� �ؽ�Ʈ ����
			m_Edit[2].DestroyWindow();
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(150,0,200,50),this,0);
			m_Edit[2].MoveWindow(530,100,50,28);
			m_Edit[2].SetWindowTextA("0");
			// Show'?'List(code)- �޺� �ڽ����·� ? ����Ʈ�� ����ϰ� �޺� �ڽ��� id ���� code�� ����
			this->ShowTList(ShowT);//���̺� ����Ʈ�� �޺��ڽ��� �����ְ� �޺��ڽ��� ���̵�� ShowT.
			this->ShowFList(ShowF);
		}
		//���̺� ����� ���� �̺�Ʈ ó�� �κ�2 :���� �޺��ڽ��� ���Ȱ� ���� ������ ��ȭ �ϸ� ����
		if(wID== ShowF &&wNotifyCode== CBN_SELCHANGE){
			//���������� �޾ƿ���
			n1=Cbox[0].GetCurSel();
			//���� �޴��� ������ ���ٸ� Food�� ������ Add�� �����Ų��
			if(FList->GetFood(n1)->season == this->season || FList->GetFood(n1)->season==0){
				Add=this->FList->GetFood(n1);
			}//������ �ٸ��ٸ� �߰��� �Ұ��� �ϴ� ���� Ŀ���� ���þȵ� ���·� �ű��.
			else{
				Add=NULL;
				this->MessageBox("�����޴�, �߰��Ұ���");
				Cbox[0].SetCurSel(-1);
			}

		}//���̺� ����� ���� �̺�Ʈ ó�� �κ�3 :���̺� �޺��ڽ��� ���Ȱ� ���� ������ ��ȭ �ϸ� ����
		if(wID== ShowT &&wNotifyCode== CBN_SELCHANGE){
			//�޺��ڽ��� ���� �κ� �ޱ�
			n=Cbox[1].GetCurSel();
			p=this->TList->GetTablePointer(n);
			//����� ���̺� �������� p�� ������ ��¿� ���� ������ �������� �־���
			������=p; //������ ��¿� ���� ������

			Cbox[2].DestroyWindow();

			CString A;//����� ���� ���� ��Ʈ�� ��ü
			int total=0;//�Ѿ��� ����� ��
			//���õ� ���̺��� �����Ͱ� �����ϰ� ���̺� ������ �Ǹſ� ����Ʈ�� �����ϸ� 
			if(p && p->InTList.Ffirst){
				Food* Food= p->InTList.Ffirst; //Food�� �Ǹſ� ����Ʈ�� 1�� ���
				//���̺� ��ϵ� ������ ������ �޺��ڽ�
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
				Cbox[2].MoveWindow(150,200,200,300);

				while(Food){ 
					A.Format("%s , %d ��",Food->Fname,Food->���);
					total+=Food->���*Food->����;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
				A.Format("�Ѿ� : %d��",total);
				Cbox[2].InsertString(-1,A);
				Cbox[2].SetCurSel(-1);
			}


		}
		//���̺� ����� ���� �̺�Ʈ ó�� �κ�4 :�߰� ��ư�� ������ ���
		if(wID==�߰���ư){
			//���̺�� ��ϵ� ���ĸ���Ʈ���� ������ ���� �ִٸ�
			if(p&&Add){
				//edit�ڽ����� �Էµ� ������ ���ڷ� �ٲ�
				char s[5];
				m_Edit[2].GetWindowTextA(s,5);
				int k=0;
				k=atoi(s);
				//�����Ϸ��� ���� ��� ������ �۰ų� ���ٸ� �߰��Ѵ�
				if(Add->���-k>=0){
					//���� �Ϸ� �� ���� ���� ����� 45% ���϶�� ��� ���� �޼��� ���
					if((Add->���)-k <= (Add->���)*0.45){this->MessageBox("��� ����!");}
					Add->���-=k;//��� ����
					Add->�Ǹŷ�+=k;//�Ǹŷ� ����
					p->InTList.AddFoodList(Add,k);//�ǸŸ���Ʈ�� �߰�
					//������ ����� C�޺��ڽ� ����
					Cbox[2].DestroyWindow();
					Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
					Cbox[2].MoveWindow(150,200,200,300);
					Food* Food = p->InTList.Ffirst;
					CString A;
					int total=0;
					//C�ڽ��� ���� ä���
					while(Food){ 
						A.Format("%s , %d ��",Food->Fname,Food->���);
						total+=Food->���*Food->����;
						Cbox[2].AddString(A);
						Food=Food->next;
					}
					A.Format("�Ѿ� : %d��",total);
					Cbox[2].InsertString(-1,A);
					Cbox[2].SetCurSel(-1);
				}
				else {
					//��� �ʰ���� �ʰ� �޼��� ���
					this->MessageBox("��� �ʰ�!");
				}

			}
		}//�ʱ�ȭ������ �������� ��ư.
		if(wID==����){
			n=-1;
			n1=-1;
			p=NULL;
			Add=NULL;
			this->ClearScreen();
			UpdateDeco();
		}
		if(wID==����){
			this->MessageBox("1.���̺���: ���̺��� �����ϰ� �޴��� ������ �� ������ �Է��ϰ� �߰�.�ϷḦ �ϸ�(��� ����,���п� �������) �ʱ�ȭ�� �̵�\n\n2.���: �ֹ��� ��ϵ� ���̺��� �����ϸ� �ֹ� ����Ʈ�� �Ϸ��ư�� ���. �� �� �ֹ� ����� ���ٸ� ����Ʈ�� ����ư�� ������ ������ �ϷḦ ������ �������� ������ ���ϸ� �������� �Բ� ���Ϸ�.\n\n3.���̺� Ȯ��:���̺��� ���ϸ� ���̺� �޴��� �� �� �ִ� ���ٸ� �޴��� �����ʴ´�. �ϷḦ ������ � ��Ȳ������ �ʱ�ȭ������ ���ư���(���̺� Ȯ�ο��� �ٷ� ����ϱ� ����)");
		}
		//���̺� Ȯ�� �̺�Ʈ�� ó��
		if(wID==���̺�Ȯ��){
			this->ClearScreen();
			ShowTList(ShowT1);
			m_Select[1].DestroyWindow();
			m_Select[1].Create("������",WS_VISIBLE|WS_CHILD,CRect(350,100,50,50),this,����);
			m_Select[1].MoveWindow(800,100,50,30);
		}
		//��� �̺�Ʈ ó��1:ȭ�� ������
		if(wID==���){
			//n~n1,p�� ���̺� ��Ͽ��� ���Ǿ����Ƿ� �ʱ�ȭ
			n=-1; n1=-1;
			p=NULL;
			//ȭ�� �ʱ�ȭ
			this->ClearScreen();
			ShowTList(ShowT1);
			//���̺� ���: ���̺��� ��µ� �� ���õǸ� p�� ���̺� ���� ����ȴ�


			CString A;
			int total=0;
			//���õ� ���̺��� �ְ� ���̺�ȿ� ����Ʈ�� �����ϸ� �ڽ��� ����Ʈ������ �߰���
			if(p && p->InTList.Ffirst){
				Food* Food= p->InTList.Ffirst;
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
				Cbox[2].MoveWindow(300,100,200,300);
				while(Food){ 
					A.Format("%s , %d ��",Food->Fname,Food->���);
					total+=Food->���*Food->����;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
			}
			//�ʱ�ȭ�鰡�� ��ư ���
			m_Select[1].DestroyWindow();
			m_Select[1].Create("������",WS_VISIBLE|WS_CHILD,CRect(800,100,50,50),this,����);
			m_Select[1].MoveWindow(800,100,50,30);
		}
		//��� �̺�Ʈ ó��2:���õ� �� ó���� ȭ�� ���
		if(wID==ShowT1){
			//���õ� ���� ���̺� ������ �޾ƿ���
			n=Cbox[1].GetCurSel();
			p=this->TList->GetTablePointer(n);
			//�������� ���� ������ p
			������=p;
			Cbox[2].DestroyWindow();
			CString A;
			int total=0;
			//�޾ƿ� ���̺��� ���� ����Ʈ ���
			if(p){//���̺��� �����ϸ�
				m_Select[0].DestroyWindow();

				Food* Food= p->InTList.Ffirst;
				//���ĸ���Ʈ�� �����ϸ� ����ϱ� ��ư ���̱�
				if(Food!=0){
					Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , 0);
					Cbox[2].MoveWindow(300,100,200,300);
					m_Select[0].Create("����ϱ�",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,����ϱ�);
					m_Select[0].MoveWindow(600,100,100,28);
				}
				//cbox�� ����Ʈ �߰�
				while(Food){ 
					A.Format("%s , %d ��",Food->Fname,Food->���);
					total+=Food->���*Food->����;
					Cbox[2].AddString(A);
					Food=Food->next;
				}
				A.Format("�Ѿ� : %d��",total);
				Cbox[2].InsertString(-1,A);
				Cbox[2].SetCurSel(-1);
			}
		}
		//��� �̺�Ʈ ó��3:���Ϸ�
		if(wID==����ϱ�){
			ClearScreen();
			������=p; //������ ����� ���� ������ p
			int total=0;
			myDlg X(this);
			CString A;
			Food* p=������->InTList.Ffirst;
			//������ ��¿� ������
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_READONLY,CRect(150,0,200,50),this,0);
			m_Edit[0].MoveWindow(150,80,300,400);

			//�������� ������ �Է¹޴� ���̾�α�
			if((X.DoModal()!=IDOK)){//����Ʈ���� ���
				while(p){
					total +=p->���*p->����;
					A.Format("%s, %d�� %d�� = %d��\r\n",p->Fname,p->���,p->����,p->���*p->����);
					m_Edit[0].SetSel(0,0);
					m_Edit[0].ReplaceSel(A);
					p=p->next;

				}
				A.Format("\r\n");
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);
				A.Format("�Ѿ�: %d��\r\n",total);
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);

			}
			else{//�Ѿ׸����
				while(p){
					total +=p->���*p->����;
					p=p->next;
				}
				A.Format("�Ѿ�: %d��\r\n",total);
				m_Edit[0].SetSel(0,0);
				m_Edit[0].ReplaceSel(A);


			}
			this->money+=total;
			������->InTList.RemoveFoodList(); //���Ϸ� �� ���̺� ��ϵ� ����Ʈ ����
			this->UpdateDeco();
		}
		//���̺� �߰� ������ ���� �̺�Ʈ
		if(wID==���̺��߰�){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("���̺��߰�\n");
			//����Ʈ�� ��ϵ� ���̺��� �ִ��� Ȯ��
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("������� ���̺��� �ս��ϴ�. ����� �Ϸ����ּ���"); x=1;break;}
				p=p->next;
			}//���ٸ�
			if(!x){
				p= this->TList->TFirst;
				printf("���̺��߰�����\n");



				//�߰� �Ǵ� ������ ������ �޴� ��
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(150,0,200,50),this,0);
				m_Edit[0].MoveWindow(200,70,50,60);
				//�߰���ư
				this->m_Select[0].Create("�߰�",WS_VISIBLE|WS_CHILD,CRect(150,0,200,50),this,���̺��߰��Ϸ�);
				this->m_Select[0].MoveWindow(250,70,50,30);		
				//������ư
				this->m_Select[1].Create("����",WS_VISIBLE|WS_CHILD,CRect(150,0,200,50),this,���̺�����Ϸ�);
				this->m_Select[1].MoveWindow(250,100,50,30);


			}

		}//���̺� �߰�/���� �̺�Ʈ - �߰��ϱ�
		if(wID==���̺��߰��Ϸ�){

			char s[5];
			m_Edit[0].GetWindowTextA(s,5);
			int k=0;
			k=atoi(s);
			for(int i=0; i<k ;i++){
				this->TList->AddTableList();
			}
			this->MessageBox("�߰��Ϸ�");
			ClearScreen();
		}
		//���̺� �߰�/�����̺�Ʈ-����
		if(wID==���̺�����Ϸ�){
			char s[5];
			m_Edit[0].GetWindowTextA(s,5);
			int k=0;
			k=atoi(s);
			for(int i=0; i<k ;i++){
				this->TList->RemoveTableNode(1);
			}
			this->MessageBox("�����Ϸ�");
			ClearScreen();
		}
		//������ ������ ���� ������ ����
		if(wID==��������){
			ClearScreen();
			this->m_CStatic[0].Create("������ �����Ͽ� �ּ���",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
			this->m_CStatic[0].MoveWindow(150,50,500,30);
			Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , �����ڽ�);
			Cbox[2].MoveWindow(150,150,100,300);
			Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("��");Cbox[2].AddString("����");Cbox[2].AddString("����");Cbox[2].AddString("�ܿ�");

			m_Select[0].DestroyWindow();
			m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,����);
			m_Select[0].MoveWindow(250,150,50,30);
		}//���������� ���� �����ϴ� ��
		if(wID==�����ڽ�){
			this->season=Cbox[2].GetCurSel();
			if(season==-1){ season =0;}
		}

		//�Ÿ޴� �߰� �̺�Ʈ ó��:ȭ��
		if(wID== �޴��߰�){
			ClearScreen();
			//���ڷ��̼�
			this->m_CStatic[0].Create("�̸� + ���� + ��� + ����  ������ �Է� ���ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,0,200,50),this,0);
			m_CStatic[0].MoveWindow(200,100,400,30);
			//�߰��Ϸ��ư
			this->m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,�޴��߰��Ϸ�);
			this->m_Select[0].MoveWindow(650,150,50,30);
			//���������� �Է¹��� C�޺��ڽ�
			Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this , �޴�Ÿ����);
			Cbox[2].MoveWindow(380,150,140,300);
			Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("��");Cbox[2].AddString("����");Cbox[2].AddString("����");Cbox[2].AddString("�ܿ�");
			Cbox[2].SetCurSel(4);//�⺻������ NO_SEASON
			// ������� �̸� ���� ��� �� �Է¹��� �ؽ�Ʈ �ڽ�
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,�޴�Ÿ����);
			m_Edit[0].MoveWindow(200,150,60,30);
			m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,�޴�Ÿ����);
			m_Edit[1].MoveWindow(270,150,40,30);
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,�޴�Ÿ����);
			m_Edit[2].MoveWindow(320,150,40,30);

		}
		//�Ÿ޴� �߰� �̺�Ʈ ó��: 3���� �ؽ�Ʈ �ڽ��� �Է��� �ְų� �޺��ڽ����� ������ ���õ� �� ���� ȣ���
		if( wID==�޴�Ÿ���� && wNotifyCode == EN_CHANGE ||wID==�޴�Ÿ���� && wNotifyCode == CBN_SELCHANGE ){
			char A[30]; 
			m_Edit[0].GetWindowText(A,30);
			printf("1:%s\n",A);
			strcpy_s(iName,A);
			printf("1:%s\n",iName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			i���� =atoi(A);
			printf("2:%d\n",i����);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			i��� =atoi(A);
			printf("3:%d\n",i���);

			i����= Cbox[2].GetCurSel();
			//�޴��� ���� �ʿ��� �����͸� ���˿� �°� ����
		}
		//�Ÿ޴� �߰� �̺�Ʈ ó��: �Ϸ��ư����
		if(wID==�޴��߰��Ϸ�){
			ClearScreen();
			//3���� �ؽ�Ʈ�ڽ��� ���� ���� �������� �⺻���̶�� ���޼��� ���
			if(iName[0]==NULL &&i����==0 &&i���==NULL && i����==0){
				this->MessageBox("�߰��� ���� �����ϴ�");
			}
			else{//�Է¹��� ��� �߰�
				this->FList->AddFoodList(iName,i����,i���,0,i����);
				this->MessageBox("�߰� �Ϸ�");
			}

		}
		//�����̺�Ʈ 1 : ȭ�� �׸���
		if(wID==�޴�����){
			rm=-1;
			ClearScreen();

			Table* p= this->TList->TFirst;
			int x=0;
			printf("�޴�����\n");
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("������� ���̺��� �ս��ϴ�. ����� �Ϸ����ּ���"); x=1;break;}
				p=p->next;
			}//����߿� �������Ǹ� �ȵǹǷ� ������� ���̺��� ������ Ȯ��
			if(!x){
				this->m_CStatic[0].Create("������ �޴��� �����Ͽ� �ּ���",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
				this->m_CStatic[0].MoveWindow(150,50,500,30);
				ShowFList(�����޴�����,0); //0�� �ڽ� ���
				this->m_Select[0].Create("����",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,�޴������Ϸ�);
				this->m_Select[0].MoveWindow(500,100,50,30);
			}//���ٸ�
		}
		//�����̺�Ʈ 2: �޺��ڽ� ó��
		if(wID==�����޴����� && wNotifyCode==CBN_SELCHANGE){
			rm=Cbox[0].GetCurSel();
		}
		//�����̺�Ʈ 3: �����ϱ� ����
		if(wID==�޴������Ϸ�){

			if(rm!=-1){
				this->FList->RemoveFoodNode(rm);
				ClearScreen();
				rm=-1; //�ʱ�ȭ
				this->MessageBox("�����Ϸ�");
			}
		}
		//�������
		if(wID==�������){
			Employnee* p=this->EList->EFirst;
			while(p){
				printf("�̸�: %s\n",p->name);
				p=p->next;
			}
			ClearScreen();
			this->m_CStatic[0].Create("�̸� + ���� + �޿� + �ð� + ���  ������ �Է� ���ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,0,200,50),this,0);
			m_CStatic[0].MoveWindow(200,100,400,30);
			this->m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,�����߰��Ϸ�);
			this->m_Select[0].MoveWindow(650,150,50,30);
			Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,���������Է���);
			Cbox[1].MoveWindow(482,150,80,100);
			Cbox[1].AddString("������");Cbox[1].AddString("����");
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,����Ÿ����);
			m_Edit[0].MoveWindow(200,150,60,30);
			m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,����Ÿ����);
			m_Edit[1].MoveWindow(270,150,40,30);
			m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,����Ÿ����);
			m_Edit[2].MoveWindow(320,150,40,30);
			m_Edit[3].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,����Ÿ����);
			m_Edit[3].MoveWindow(380,150,100,30);
		}
		if( wID==����Ÿ���� && wNotifyCode == EN_CHANGE ||wID==����Ÿ���� && wNotifyCode == CBN_SELCHANGE ){
			char A[30]; 
			m_Edit[0].GetWindowText(A,30);
			i����=0;
			printf("1:%s\n",A);
			strcpy_s(iName,A);
			printf("1:%s\n",iName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			i���� =atoi(A);
			printf("2:%d\n",i����);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			i�޿� =atoi(A);
			printf("3:%d\n",i�޿�);

			m_Edit[3].GetWindowText(A,30);
			printf("4:%s\n",A);
			i�ð� =atoi(A);
			printf("4:%d\n",i�ð�);
			i����=100+Cbox[1].GetCurSel();
			printf("�Է����� �����ڵ�:%d\n",i����);


		}
		if(wID==�����߰��Ϸ�){
			printf("�����߰� �����ڵ�:%d",i����);

			if(iName[0]==NULL &&i����==0 &&i�޿�==NULL && i����==0){
				this->MessageBox("�߰��� ���� �����ϴ�");
			}
			else{
				i����=100+Cbox[1].GetCurSel();
				this->EList->AddE(iName,i����,i�޿�,i�ð�,i����);
				this->MessageBox("�߰� �Ϸ�");
			}
			ClearScreen();
		}

		if(wID==�޴�����){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("�޴�����\n");
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("������� ���̺��� �ս��ϴ�. ����� �Ϸ����ּ���"); x=1;break;}
				p=p->next;
			}
			if(!x){
				ClearScreen();
				//��� �޴� ���
				this->ShowFList(�޴�������,3);

				//���ڷ��̼�+���
				this->m_CStatic[0].Create("�̸� + �ܰ� + ��� ������ �Է� ���ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,200,400,30);

				//�޴��� ���� ������ �����ϴ� ��ư
				this->m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(600,350,50,30),this,�޴�����Ϸ�);
				this->m_Select[0].MoveWindow(520,250,50,30);

				//���ڷ��̼�+����
				this->m_CStatic[1].Create("�����޴�����",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[1].MoveWindow(150,100,120,30);
				this->m_CStatic[2].Create("������ �޴��� �̸�, ���, ����, �Ǹ� ������ ���� �� �� �ֽ��ϴ�.",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[2].MoveWindow(150,50,500,30);
				//�޴��� ���� ������ ������ �ڽ�
				Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,�޴�������);
				Cbox[2].MoveWindow(360,250,140,300);
				Cbox[2].AddString("NO_SEASON");Cbox[2].AddString("��");Cbox[2].AddString("����");Cbox[2].AddString("����");Cbox[2].AddString("�ܿ�");
				Cbox[2].SetCurSel(4);
				//�޴��� ������ ������ �ؽ�Ʈ ����
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,�޴�������);
				m_Edit[0].MoveWindow(150,250,60,30);//�̸�
				m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,�޴�������);
				m_Edit[1].MoveWindow(230,250,50,30);//���
				m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,�޴�������);
				m_Edit[2].MoveWindow(290,250,50,30);//����

			}
		}
		if(wID==�޴������� && wNotifyCode==CBN_SELCHANGE){
			printf("�޴�������\n");
			m_Edit[0].Clear();
			m_Edit[1].Clear();
			if(Cbox[0].GetCurSel()!=-1){
				printf("�޴���������\n");
				fix=this->FList->GetFood(Cbox[0].GetCurSel());
				index=Cbox[0].GetCurSel();
				m_Edit[0].Clear();
				m_Edit[1].Clear();
				m_Edit[0].SetWindowTextA(fix->Fname);
				CString A;
				A.Format("%d",fix->����);
				m_Edit[1].SetWindowTextA((A));
				A.Format("%d",fix->���);
				m_Edit[2].SetWindowTextA(A);
				Cbox[2].SetCurSel(fix->season);

			}
		}
		if((wID==�޴������� && wNotifyCode==EN_CHANGE) || (wID==�޴������� && wNotifyCode==CBN_SELCHANGE)  ){
			printf("�޴�������\n");
			char A[30]; 
			m_Edit[0].GetWindowText(FName,30);
			printf("1:%s\n",FName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			F���� =atoi(A);
			printf("2:%d\n",F����);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			F��� =atoi(A);
			printf("3:%d\n",F���);
			F���� =Cbox[2].GetCurSel();
			printf("4:%d\n",F����);
		}
		if(wID==�޴�����Ϸ�){
			fix->ChangeName(FName);
			printf("��\n");
			fix->����=F����;
			fix->���=F���;
			fix->season=F����;
			printf("��\n");
			this->MessageBox("�����Ϸ�!");
			this->ClearScreen();
		}
		if(wID==��й�ȣ����){
			this->ClearScreen();
			this->m_CStatic[1].Create("������ ��й�ȣ�� �Է����ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,300,50),this,0);
			m_CStatic[1].MoveWindow(150,100,300,30);
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER|ES_NUMBER,CRect(200,150,60,30),this,�޴�������);
			m_Edit[0].MoveWindow(150,150,60,30);//�̸�
			this->m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,��й�ȣ�����Ϸ�);
			this->m_Select[0].MoveWindow(210,150,50,30);
		}
		if(wID==��й�ȣ�����Ϸ�){
			int nkey;
			char A[5];
			m_Edit[0].GetWindowText(A,30);
			nkey =atoi(A);
			printf("nkey:%d\n",nkey);
			this->key =nkey;
			printf("key:%d\n",nkey);
			CString S;
			S.Format("��й�ȣ ����Ϸ�!\n���ο� ��й�ȣ: %d",key);
			this->MessageBox(S);
			ClearScreen();
		}


		//�޴������̺�Ʈ 1 : ȭ�� �׸���
		if(wID==�����ذ�){
			Erm=-1;
			ClearScreen();

			Employnee* p= this->EList->EFirst;
			int x=0;
			printf("��������\n");
			if(!x){
				this->m_CStatic[0].Create("�ذ��� ������ �����Ͽ� �ּ���",WS_VISIBLE|WS_CHILD,CRect(100,100,400,50),this,0);
				this->m_CStatic[0].MoveWindow(150,50,500,30);
				ShowEList(�ذ���������); //0�� �ڽ� ���
				this->m_Select[0].Create("����",WS_VISIBLE|WS_CHILD,CRect(600,150,50,30),this,�ذ�Ϸ�);
				this->m_Select[0].MoveWindow(500,100,50,30);
			}//���ٸ�
		}
		//�����̺�Ʈ 2: �޺��ڽ� ó��
		if(wID==�ذ��������� && wNotifyCode==CBN_SELCHANGE){
			if(Cbox[2].GetCurSel()!=-1)
				Erm=Cbox[2].GetCurSel();
		}
		//�����̺�Ʈ 3: �����ϱ� ����
		if(wID==�ذ�Ϸ�){

			if(Erm!=-1){
				printf("%d �� ��������",Erm);
				this->EList->RemoveENode(Erm);
				printf("ȭ�������");
				ClearScreen();
				this->MessageBox("�ذ�Ϸ�");
			}
		}


		if(wID==��������){
			ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("��������\n");
			if(!x){
				ClearScreen();
				//��� �޴� ���
				this->ShowEList(����������);

				//���ڷ��̼�+���
				this->m_CStatic[0].Create("�̸�, �ñ�, �ٹ��ð�, ���Ÿ�� ������ �Է� ���ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,200,400,30);

				//�޴��� ���� ������ �����ϴ� ��ư
				this->m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(600,350,50,30),this,���������Ϸ�);
				this->m_Select[0].MoveWindow(520,250,50,30);

				//���ڷ��̼�+����
				this->m_CStatic[1].Create("����",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,50,100),this,0);
				m_CStatic[1].MoveWindow(150,100,50,30);
				this->m_CStatic[2].Create("������ ������ �̸�, �ñ�, �ٹ��ð�, ���Ÿ���� ���� �� �� �ֽ��ϴ�.",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[2].MoveWindow(150,50,500,30);
				//���Ÿ���� ���� �ڽ�
				Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|WS_BORDER,CRect(150,50,100,50), this ,���������Է���);
				Cbox[1].MoveWindow(360,250,140,300);
				Cbox[1].AddString("������");Cbox[1].AddString("����");

				//������ ������ ������ �ؽ�Ʈ ����
				m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER,CRect(200,150,60,30),this,���������Է���);
				m_Edit[0].MoveWindow(150,250,60,30);//�̸�
				m_Edit[1].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(270,150,40,30),this,���������Է���);
				m_Edit[1].MoveWindow(230,250,50,30);//�ñ�
				m_Edit[2].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|ES_NUMBER|WS_BORDER,CRect(320,150,40,30),this,���������Է���);
				m_Edit[2].MoveWindow(290,250,50,30);//�ٹ��ð�

			}
		}
		if(wID==���������� && wNotifyCode==CBN_SELCHANGE){
			printf("����������\n");
			m_Edit[0].Clear();
			m_Edit[1].Clear();
			if(Cbox[0].GetCurSel()!=-1){
				printf("�������ý���\n");
				Efix=this->EList->GetE(Cbox[2].GetCurSel());
				index=Cbox[0].GetCurSel();
				m_Edit[0].Clear();
				m_Edit[1].Clear();
				m_Edit[0].SetWindowTextA(Efix->name);
				CString A;
				A.Format("%d",Efix->�޿����);
				m_Edit[1].SetWindowTextA((A));
				A.Format("%d",Efix->�ٹ��ð�);
				m_Edit[2].SetWindowTextA(A);
				Cbox[1].SetCurSel((Efix->����ڵ�-100));

			}
		}
		if((wID==���������Է��� && wNotifyCode==EN_CHANGE) || (wID==���������Է��� && wNotifyCode==CBN_SELCHANGE)  ){
			printf("�޴�������\n");
			char A[30]; 
			m_Edit[0].GetWindowText(Ename,30);
			printf("1:%s\n",FName);

			m_Edit[1].GetWindowText(A,30);
			printf("2:%s\n",A);
			E�ñ� =atoi(A);
			printf("2:%d\n",E�ñ�);

			m_Edit[2].GetWindowText(A,30);
			printf("3:%s\n",A);
			E�ٹ��ð� =atoi(A);
			printf("3:%d\n",E�ٹ��ð�);
			E��� =100+ Cbox[1].GetCurSel();
			printf("4:%d\n",E���);
		}
		if(wID==���������Ϸ�){
			delete Efix->name;
			Efix->name=new char [strlen(Ename)+1];
			for(int i=0; i<strlen(Ename)+1; i++){
				Efix->name[i]=NULL;
			}
			for(int i=0; i<strlen(Ename); i++){
				Efix->name[i]=Ename[i];
			}
			printf("1");
			Efix->�ٹ��ð�=E�ٹ��ð�;
			printf("2");
			Efix->�޿����=E�ñ�;
			printf("3");
			Efix->����ڵ�=E���;
			printf("4");
			this->MessageBox("�����Ϸ�!");
			this->ClearScreen();
		}
		if(wID==�����ܾװ���){
			this->ClearScreen();
			this->m_CStatic[0].Create("����� �������� �ܾ��� �Է��� �ּ���",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
			m_CStatic[0].MoveWindow(150,100,400,30);
			m_Edit[0].Create(WS_VISIBLE|WS_CHILD|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_BORDER|ES_NUMBER,CRect(200,150,60,30),this,�ܾ��Է�);
			m_Edit[0].MoveWindow(150,150,100,30);//�ݾ��� �Էµ� ��
			CString m;
			m.Format("%d",this->money);
			m_Edit[0].SetWindowTextA(m);
			m_Select[0].DestroyWindow();
			m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,����);
			m_Select[0].MoveWindow(260,150,50,30);
		}
		if(wID==�ܾ��Է� && wNotifyCode==EN_CHANGE){
			char a[50];
			m_Edit[0].GetWindowText(a,50);
			this->money = atoi(a);
		}
		if(wID==���){
			this->ClearScreen();
			Table* p= this->TList->TFirst;
			int x=0;
			printf("���̺��߰�\n");
			//����Ʈ�� ��ϵ� ���̺��� �ִ��� Ȯ��
			while(p){
				if(p->InTList.Ffirst !=0){this->MessageBox("������� ���̺��� �ս��ϴ�. ����� �Ϸ����ּ���"); x=1;break;}
				p=p->next;
			}//���ٸ�
			if(!x){
				this->m_CStatic[0].Create("������ ��踦 �������� Ȯ�� ���������� �Ǹŷ��� ����մϴ�",WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
				m_CStatic[0].MoveWindow(150,100,400,30);
				this->Show���();
				m_Select[0].DestroyWindow();
				m_Select[0].Create("�Ϸ�",WS_VISIBLE|WS_CHILD,CRect(350,300,150,50),this,����);
				m_Select[0].MoveWindow(650,150,50,30);
			}
		}
		return CView::OnCommand(wParam, lParam);
	}

	//������ �޴� ���� Ŭ��
	void C����3View::On32771()
	{
		// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
		��й�ȣdlg A(this);
		//��й�ȣ�� �´ٸ� �����ٰ�
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
				this->MessageBox(" ��й�ȣ ����");
		}



	}

	//�����ڸ�� ���� �޴� Ŭ��
	void C����3View::On32774()
	{
		if(this->m_MBTN[0]!=NULL)
			for(int i=0; i<11; i++){ this->m_MBTN[i]->DestroyWindow(); }
			// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	}

	void C����3View::ShowFList(int code =ShowF){
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,code);
		Cbox[0].MoveWindow(300,100,200,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){
			if(p->season == this->season  || p->season ==0){
				A.Format("+ %s + %d + %d +",p->Fname,p->����,p->���);
				this->Cbox[0].AddString(A);
			}
			else{
				A.Format("�����޴�. ���úҰ�",p->Fname,p->����,p->���);
				this->Cbox[0].AddString(A);
			}
			p=p->next;
		}	

	}
	void C����3View::ShowFList(int code , int x){
		x=0;
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,code);
		Cbox[0].MoveWindow(300,100,200,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){

			A.Format("+ %s + %d + %d +",p->Fname,p->����,p->���);
			this->Cbox[0].AddString(A);

			p=p->next;
		}	

	}

	void C����3View::ShowTList(int code=ShowT){
		Cbox[1].DestroyWindow();
		Cbox[1].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , code);
		Cbox[1].MoveWindow(150,100,100,300);
		CString A;
		for(int i=0; i<this->TList->Tcount; i++){ 
			A.Format("%d�� ���̺�",i+1);
			Cbox[1].AddString(A);
		}
	}

	void C����3View::ShowEList(int code){
		Cbox[2].DestroyWindow();
		Cbox[2].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL,CRect(150,50,100,50), this , code);
		Cbox[2].MoveWindow(150,100,300,300);
		CString A;
		Employnee* p =this->EList->EFirst;
		while(p){
			A.Format("�̸�:%s-�޿�:%d-�ٹ��ð�:%d",p->name,p->�޿����,p->�ٹ��ð�);
			Cbox[2].AddString(A);
			p=p->next;
		}
	}
	void C����3View:: Clear(){
		ClearScreen();
		for(int i=0; i< 3 ; i++){
			m_BTN[i]->DestroyWindow();
		}

	}
	void C����3View:: ClearScreen(){
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

	void C����3View::SavePosStat(){
		FILE *fp =NULL;
		fopen_s(&fp,"PosData.txt","wt");
		if(fp==NULL){return;}
		fprintf(fp," %d %d %d",this->money,this->key,this->season);
		fclose(fp);
	}

	void C����3View::LoadPosStat(){
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
		printf("Load���: %d %d %d",this->money,this->key,this->season);
	}
	void C����3View::UpdateDeco(){

		this->m_deco.DestroyWindow();
		CString D;
		char* sea[5]={"�Ϲ�","��","����","����","�ܿ�"};
		D.Format("PosSystem                                                                                                                                     �ܰ�:%d                         ����: %s �޴� �Ǹ�",this->money,sea[this->season]);
		this->m_deco.Create(D,WS_VISIBLE|WS_CHILD|WS_BORDER,CRect(150,200,200,50),this,0);
		this->m_deco.MoveWindow(0,0,1000,30);

	}
	void C����3View::Show���(){
		Cbox[0].DestroyWindow();
		Cbox[0].Create(WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|WS_VSCROLL|CBS_AUTOHSCROLL,CRect(150,50,100,50), this ,0);
		Cbox[0].MoveWindow(150,150,500,300);
		Food* p=this->FList->Ffirst;
		CString A;
		while(p){
			A.Format("+ �̸�: %s +�Ǹŷ�: %d +�Ǹž�: %d +",p->Fname,p->�Ǹŷ�,p->�Ǹŷ�*p->����);
			this->Cbox[0].AddString(A);
			p->�Ǹŷ�=0;
			p=p->next;
		}	
	}