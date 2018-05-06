#include<iostream>
#include"Foods.h"
#include"Table.h"
#include"Sell.h"
#include"Pos.h"
#include <conio.h>

#define 공백 cout<<endl;
using namespace std;
//각 타입의 FirstNode들
Table* FirstTableNode=NULL;
//static 멤버 초기화
int Food::incount=0;
int Table::mycount=0;
//프로토 타입
Table* GTable();
//메인함수
void main(){

	LoadTableList(&FirstTableNode);//테이블의 상태를 읽어옴. food와 같은 원리로 추가.
	int ESC=0; //함수의 종료나 시작을 지연시키는 변수. 의미없는 수를 받아서 지연시킴



	while(1){
		//포스기가 끝날 때 기존리스트는 지우고 시작과 동시에 firstnode들을 초기화시켜준다.
		Food::incount=0;
		Table::mycount=0;
		Food* FirstFoodNode= NULL;


		int posmoney=0;//포스기의 잔고
		int key=0;//비밀번호를 저장할 곳.
		int d=0;
		int ch=0;
		system("cls");
		LoadFoodList(&FirstFoodNode);//메모장에 저장된 각 리스트들의 정보를 읽어서 리스트 추가함수(AddFoodList)를 통해 리스트에 추가.

		LoadPosMoney(&posmoney,&key);//저장된 비밀번호와 pos기의 잔고를 읽어온다
		cout<<"■pos 잔고: "<<posmoney<<"■"<<endl;
		공백 공백
			//선택지를 출력. 
			cout<<"※1 +테이블 등록+"<<endl<<"※2 +계산+"<<endl<<"※3+테이블 확인+"<<endl<<
			"※4 +도움말+"<<endl<<"※5 시재점검+"<<endl<<endl<<"입력>>";
		//선택을 입력받음
		cin>>d;
		//선택을 받은 후 화면을 지워 화면 전환의 효과를 줌.
		system("cls");

		//if문으로 선택에 맞는 내용 실행.
		if(d==1){ //판매등록. do~while()문을 사용하여 계속해서 메뉴를 입력받게함.

			Table* p= GTable();
			if(p){
			if(p->D != -1)
				SetTable(p,1);//값변경
			do {
				system("cls");
				ShowSellList(&p->s);
				공백;
				ShowFoodList(&FirstFoodNode);
				공백;
				cout<<"메뉴의 번호를 선택해 주세요"<<endl<<"입력>>";
				int n;
				cin>>n;
				int x;
				공백;
				cout<<"개수를 입력해 주세요"<<endl<<"입력>>";
				cin>>x;

				AddSellList(&p->s,&FirstFoodNode,n,x);
				cout<<"■등록완료는 1 입력"<<endl;
				cin>>ch;	
			}while (ch!=1);//등록완료(=1 입력)를 하면 종료
			}

		}
		else if(d==2){//테이블 판매 완료.
			Table* p= GTable();
			//삭제와 동시에 계산,영수증을 출력하는 함수.
			if(p){
			if(p->D == 1 ){
				cout<<"1-1";
			RemoveSellList(&p->s,&posmoney);
			SetTable(p,0);
			}
			
			else{
				cout<<"1-2";
				cout<<"다른 테이블을 입력해주세요. 숫자를 입력하시면 초기화면으로 이동합니다"<<endl<<"입력 >>";
				cin>>ESC;
			}
			}
		}
		
		//현재 테이블의 상태를 확인하는 함수
		else if(d==3){
			ShowTableList(&FirstTableNode);
			//다음 소스로 넘어가지 않게 지연
			cout<<"숫자를 입력하시면 초기화면으로 이동합니다"<<endl;
			cin>>ESC;
		}
		//도움말: 간략한 사용법을 보여줌.
		else if(d==4){
			cout<<"환불 처리: 구매-> 물건을 선택한 후 수량을 음수로 입력"<<endl<<"관리자모드: 초기 비밀번호1011, 비밀번호 변경: 관리자모드->변경선택"<<endl;
			cout<<"■숫자를 입력하시면 초기화면으로 이동합니다"<<endl;
			cin>>ESC; //소스 지연
		}
		//사용자가 직접 지폐수를 계산해서 입력하여 포스기상의 재고와 차이액을 비교하여 저장한다.
		else if(d==5){
			int val[8] ={50000,10000,5000,1000,500,100,50,10}; //돈금액의 가치
			char* name[8]= { "오만원" , "만원" , "오천원" , "천원" , "오백원" , "백원" , "오십원" , "십원" };//돈의 지폐명
			int mn[8];//개수가 입력될곳.
			//초기화
			for(int i=0;i<8;i++)
				mn[i]=0;
			int sum =0;
			//
			for(int i=0;i<8;i++){
				cout<<name[i]<<": ";
				cin>>mn[i];
				cout<<endl;
			}
			for(int i=0;i<8;i++){
				sum += val[i] * mn[i];
			}

			cout<<"과부족: "<<sum-posmoney;
			공백;
			FILE* fp=fopen("과부족.txt","a");
			fprintf(fp," %d",sum-posmoney);
			fclose(fp);
			cout<<"종료하실려면 숫자를 입력해주세요"<<endl<<"입력>>";
			cin>>ESC;
		}
		//관리자모드시작
		else if(d==key){
			int xd=0;
			do{
				int n = 0;
				system("cls");
				cout<<"■■관리자모드 실행(주의! 종료를 하셔야 적용됩니다!)■■"<<endl; 공백
					cout<<"▷ 1테이블 추가"<<endl<<"▷ 2테이블 삭제"<<endl<<"▷ 3테이블 수리등록"<<endl<<"▷ 4메뉴추가"<<endl<<"▷ 5메뉴삭제"<<endl<<"▷ 6재고 추가"<<endl<<"▷ 7통계"<<endl<<"▷ 8비밀번호 재설정"<<endl<<"▷ 9할인등록"<<endl<<"▷ 10포스잔액관리"<<endl<<"▷ 11종료"<<endl;
				공백;
				cout<<"입력>>";
				cin>>xd;
				switch (xd){
				case 1:{
					system("cls");
					cout<<"추가하실 개수를 입력해 주세요"<<endl<<">>입력:";
					cin>>n;
					for(;n>0;n--){
						AddTableList(&FirstTableNode,0); //테이블 추가.
					}
					break;
					   }
				case 2:{
					system("cls");
					ShowTableList(&FirstTableNode); 
					cout<<"삭제하실 테이블의 숫자를 입력해주세요"<<endl<<"입력>>";
					cin>>n;
					RemoveTableNode(&FirstTableNode,n);
					break;
					   }
				case 3:{
					system("cls");
					ShowTableList(&FirstTableNode);
					cout<<"수리하실 테이블의 숫자를 입력해주세요"<<endl<<"입력>>";
					cin>>n;
					Table* p=GetTablePointer(&FirstTableNode,n);
					SetTable(p,-1);
					break;
					   }
				case 4:{
					system("cls");
					cout<<"추가할 메뉴의 이름을 입력해주세요: ";
					char name[100];
					int price;
					int n;
					int E=0;
					cin>>name;
					cout<<"추가할 메뉴의 가격을 입력해주세요: ";
					cin>>price;
					cout<<"추가할 메뉴의 재고을 입력해주세요: ";
					cin>>n;
					cout<<"추가할 메뉴의 이벤트 할인 가격을 입력해주세요: ";
					cin>>E;
					AddFoodList(&FirstFoodNode,name,price ,n,0,E); //함
					break;
					   }
				case 5:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"삭제할 메뉴의 번호를 입력해 주세요: "<<endl<<"입력>>";
					cin>>n;
					RemoveFoodNode(&FirstFoodNode,n);
					break;
					   }
				case 6:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"재고를 추가할 메뉴의 번호를 입력해 주세요: "<<endl<<"입력>>";
					cin>>n;
					system("cls");
					Food* p= GetFoodPointer(&FirstFoodNode,n);
					cout<<"현재 재고:"<<p->n<<endl<<"수정 후 재고 입력 >>";
					cin>>n;
					p->n=n;
					break;

					   }
				case 7:{
					system("cls");
					통계(FirstFoodNode);
					cout<<"■숫자를 입력하시면 초기화면으로 이동합니다"<<endl;
					cin>>ESC;
					break;
					   }
				case 8:{
					system("cls");
					cout<<"현재 비밀번호는: "<<key<<"입니다"<<endl;
					cout<<"새로 설정할 비밀번호(4자리 자연수)를 입력해주세요"<<endl<<"입력>>";
					if(0<=key && key<=9999){
						cin>>key;
					}
					break;
					   }
				case 9:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"할인 등록할 메뉴의 번호를 입력하세요"<<endl<<"입력>>";
					cin>>n;
					system("cls");
					Food* p1 = GetFoodPointer(&FirstFoodNode,n);
					cout<<endl<<p1->name<<" 메뉴의 할인액은 현재  "<<p1->Event<<" 원 입니다."<<endl;
					cout<<"새로운 할인액(0~메뉴의 가격까지의 자연수)을 입력해 주세요"<<endl<<"입력>>";
					cin>>n;
					if(0<=n&&n<=p1->price){
						p1->Event=n;
					}
					break;
					   }
				case 10:{
					system("cls");
					int m=0;
					cout<<"현재잔액:"<<posmoney<<endl;
					cout<<"1.출금 2.입금"<<endl<<"선택>>";
					cin>>n;
					system("cls");
					if(n==1){

						cout<<"출금할 금액(0~포스잔액까지의 자연수)을 입력해 주세요"<<endl<<"입력>> ";
						cin>>m;
						if(0<=m&&m<=posmoney){
							posmoney-=m;
						}
					}
					else if(n==2){
						cout<<"입금할 금액(0원 이상의 자연수)을 입력해 주세요"<<endl<<"입력>> ";
						cin>>m;
						if(0<=m){
							posmoney+=m;
						}
					}

					break;
						}
				}
			}while(xd !=11);
		}//관리자모드 끝!
		SaveFoodList(&FirstFoodNode);
		SavePosMoney(&posmoney,&key);
		RemoveFoodList(&FirstFoodNode);

	}//함수내용끝

	SaveTableList(&FirstTableNode);
	RemoveTableList(&FirstTableNode);
}//메인끝


Table* GTable(){
	ShowTableList(&FirstTableNode);//테이블 출력
	cout<<"■종료는 0입력"<<endl;
	cout<<"사용할 테이블 번호를 선택해 주세요:";//선택을 입력받음
	int x;
	cin>>x;//입력받은 값을 저장
	
	if(x!=0){//0이아니라면 실행
		
		Table* p=GetTablePointer(&FirstTableNode,x);// x번째 테이블 포인터를 반환하는 함수
		
		if(p->D == -1){
			cout<<"3-1";
			cout<<"수리중인 테이블입니다. 다른 테이블을 선택해주세요."<<endl;
			return 0;
		}
		
		return p;


	}
}



