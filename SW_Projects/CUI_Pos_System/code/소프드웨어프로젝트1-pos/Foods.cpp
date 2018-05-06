#include "Foods.h"
#include <iostream>
using namespace std;

void Food::SetEvent(int a){
	Event = a;
}

/*추가함수*/
int AddFoodList(Food** FirstNode, char* name, int price ,int n,int total=0,int E=0){
	if(!(*FirstNode)){
		*FirstNode = new Food(name,price,n,total,E);
		return 0;
	}
	Food* NewNode =new Food(name,price,n,total,E);
	Food* p = *(FirstNode); //마지막 노드를 알려주는 포인터
	while(p->p){
		p= p->p;	
	}
	p->p=NewNode;
	return 0;
}


/*출력함수*/
int ShowFoodList(Food** FirstNode){
	if(!(*FirstNode)){
		cout<<"<상품 준비중입니다.>"<<endl;
		return 0;
	}
	cout<<"<판매 상품>"<<endl;
	int count=1;
	Food* p = *FirstNode;
	while(p){
		cout<<"+"<<"<"<<count<<">"<<p->name<<" : "<<p->price<<"    재고:"<<p->n<<endl;
		p=p->p;
		count++;
	}
	return 0;
}


//포인터 반환 함수
Food* GetFoodPointer(Food** FirstNode, int n){
	Food* Gp= *FirstNode;
	if(!(*FirstNode) || (*FirstNode)->incount<n){
		return NULL;
	}
	
	for(;n-1>0;n--){
		Gp=Gp->p;
	}
	
	return Gp;
}

//삭제함수
int RemoveFoodNode(Food** FirstNode,int n){
	Food* Remover;
	Food* p;
	if(n==1){
		
		Remover = GetFoodPointer(FirstNode,n);
		p= GetFoodPointer(FirstNode,n+1);
		
		cout<<Remover;
		delete Remover;
		
		*FirstNode=p;
		(p->incount)--;
		return 0;
	}
	else if(n==(*FirstNode)->incount && (*FirstNode)->incount!=1){
		
		Remover = GetFoodPointer(FirstNode,n);
		p= GetFoodPointer(FirstNode,n-1);
		cout<<Remover->name;
		(p->incount)--;
		p->p=NULL;
		
		delete Remover;
		
		
		return 0;
	}
	else{
	
		Remover = GetFoodPointer(FirstNode,n);
	
		p= GetFoodPointer(FirstNode,n-1);
		
		(p->incount)--;
		p->p = NULL;
		
		delete Remover;
		
	}
	return 0;
}


//리스트 삭제함수
int RemoveFoodList(Food** FirstNode){
	Food* p=*FirstNode;
	Food* p1=NULL;
	while(p){
	p1=p->p;
	delete p;
	p=p1;
	}
	return 0;
}




