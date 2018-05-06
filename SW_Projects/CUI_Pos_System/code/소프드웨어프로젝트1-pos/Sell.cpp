#include "Sell.h"
#include "Foods.h"
#include <iostream>
using namespace std;

//판매
int AddSellList(SellList** FirstNode,Food** FoodNode, int n, int xn){
	Food* p= GetFoodPointer(FoodNode,n);
	if(n>p->incount){return 0;}
	if(!(p->n)||xn> p->n){
		cout<<p->name<<" 상품의 재고가 부족합니다.";
		return 0;
	}
	//통계용 판매 수 저장.
	p->total+=xn;
	//재고에 판매량 만큼 감소.
	p->n-= xn;
	SellList* NewNode = new SellList(p,xn);

	if(!(*FirstNode)){
		*FirstNode = NewNode;
		return 0;
	}

	SellList* p1=*FirstNode;

	while(p1->p){
		p1=p1->p;
	}
	;
	p1->p=NewNode;
	return 0;
}
//판매를 위한 리스트를 보여줌
int ShowSellList(SellList** FirstNode){

	if(!(*FirstNode)){
		cout<<"<구매 목록이 없습니다>"<<endl;
		return 0;
	}
	cout<<"<구매 리스트.>"<<endl;
	int count=1;
	SellList* p = *FirstNode;
	while(p){
		cout<<"+"<<"<"<<count<<">"<<p->name<<" :  "<<p->price<<" 구매량:"<<p->n<<endl;
		p=p->p;
		count++;
	}
	return 0;

}
//판매,영수증선택,계산을하는 함수. 작동하면서 다 삭제
int RemoveSellList(SellList** FirstNode,int *t){

	SellList* p =(*FirstNode);
	SellList* p1=NULL;
	int total=0;
	int d=0;
	cout<<"영수증 종류 선택: 1-총 액만, 2-구매목록 포함"<<endl<<endl<<"입력>>";
	cin>>d;
	cout<<endl;
	int x=0;
	if(d==1){
		while(p){
			p1=p->p;
			total+=(p->price)*(p->n);

			if(p->Event){
				total-=(p->Event)*(p->n);
			}	

			delete p;
			p=p1;
		}
		(*t)+=total;
		cout<<"전부 "<<total<<"입니다."<<endl<<"받은금액:";
		int x=0;
		cin>>x;
		cout<<"거스름돈:"<<x-total<<endl<<endl;
		cout<<endl;
		cout<<"<영수증>"<<endl<<"총 구매 금액:"<<total<<endl<<"받은 금액:"<<x<<endl<<"거스름돈"<<x-total<<endl;

	}
	else{
		cout<<"<영수증>"<<endl;
		cout<<endl;
		ShowSellList(FirstNode);
		cout<<endl;
		while(p){
			p1=p->p;
			total+=(p->price)*(p->n);

			if(p->Event){
				total-=(p->Event)*(p->n);
			}	
			delete p;
			p=p1;
		}

		(*t)+=total;
		cout<<"총액: "<<total<<endl<<"받은금액:";
		cin>>x;
		cout<<"거스름돈:"<<x-total<<endl;


	}
	cout<<"■숫자를 입력하면 초기화면으로 이동합니다."<<endl;
	cin>>x;
	*FirstNode = NULL;

	return 0;
}


