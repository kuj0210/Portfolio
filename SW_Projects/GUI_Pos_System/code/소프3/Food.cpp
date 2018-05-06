#include "stdafx.h"
#include <iostream>
#include "Food.h"
#include <String>
using namespace std;
#pragma once
/*Class FoodList F*/
void Food::ChangeName(char* Newname){
	cout<<"삭제전"<<endl;
	delete (this->Fname);
	cout<<"삭제후"<<endl;
	this->Fname=new char [strlen(Newname)+1];
		for(int i=0; i<strlen(Newname)+1; i++){
				this->Fname[i]=NULL;
			}

			for(int i=0; i<strlen(Newname); i++){
				this->Fname[i]=Newname[i];
			}
};

int FoodList::SaveFoodList(){

	FILE* fp;
	fopen_s(&fp,"food.txt","wt");
	if(!fp){
		cout<<"food를 쓸 수 없습니다."<<endl;
		return 0;
	}
	Food* p = Ffirst;
	while(p){
		//이름없음,price, 재고, event, 판매량
		fprintf_s(fp," %s %d %d %d %d",p->Fname,p->가격,p->재고,p->판매량,p->season);
		p=p->next;
		if(p==NULL) break;
	}
	fclose(fp);
	return 0;
}
int FoodList::LoadFoodList(){
	FILE* fp;
	fopen_s(&fp,"food.txt","rt");
	if(!fp){
		cout<<"food를 읽을 수 없습니다."<<endl;
		return 0;
	}
	cout<<"FOODLIST_ 읽기 시작";
		char name[100];
		for(int i=0; i<100;i++){ name[i]=NULL; }
		int price;
		int n;
		int Total;
		int season;
	while(!feof(fp)){
		fscanf_s(fp,"%s",name);
		fscanf_s(fp,"%d",&price);
		fscanf_s(fp,"%d",&n);
		fscanf_s(fp,"%d",&Total);
		fscanf_s(fp,"%d",&season);
		printf("%s : %d\n",name,season);
		printf("ADD실행\n");
		AddFoodList(name,price,n,Total,season);
		
		
	}
	fclose(fp);
	return 0;
}
//추가함수
int FoodList::AddFoodList(char* name, int price, int n,int xtotal){
	this->Fcount++;
	if(this->Ffirst==NULL){
		Ffirst = new Food(name,price,n,xtotal);

		return 0;
	}
	Food* NewNode =new Food(name,price,n);
	Food* p = (Ffirst); //마지막 노드를 알려주는 포인터
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<endl;
		return 0;
}

int FoodList::AddFoodList(char* name, int price, int n,int xtotal, int season){
	this->Fcount++;
	if(this->Ffirst==NULL){
		Ffirst = new Food(name,price,n,xtotal,season);
		cout<<endl<<"첫노드계절번호"<<Ffirst->season<<endl;
		return 0;
	}
	Food* NewNode =new Food(name,price,n,xtotal,season);
	cout<<"계절번호:"<<NewNode->season<<endl;
	Food* p = (Ffirst); //마지막 노드를 알려주는 포인터
	cout<<"포인터 받기";
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<endl;
		return 0;
}

//출력함수


//포인터 반환 함수
Food* FoodList::GetFood(int n){
	Food* Gp= Ffirst;
	cout<<"푸드 포인터 실행 n:"<<n<<endl;
	if(!(Ffirst) || this->Fcount<n){
		cout<<"FPoint 반환실패";
		return NULL;
	}

	for(;n>0;n--){
		Gp=Gp->next;
	}
	cout<<"GP->Fname:"<<Gp->Fname<<endl;
	return Gp;
}

//삭제함수
int FoodList::RemoveFoodNode(int n){
	Food* Remover;
	Food* p;
	if(n==1){

		Remover =GetFood(n);
		p= GetFood(n+1);


		delete Remover;

		Ffirst=p;
		this->Fcount--;
		return 0;
	}
	else if(n==this->Fcount){
		Remover =GetFood(n);
		p= GetFood(n-1);
		this->Fcount--;
		p->next=NULL;
		delete Remover;
		return 0;
	}
	else{
		Remover = GetFood(n);
		p= GetFood(n-1);
		(this->Fcount)--;
		p->next = Remover->next;
		delete Remover;
	}
	return 0;
}
//리스트 삭제함수
int FoodList::RemoveFoodList(){
	this->Fcount=0;
	Food* p=Ffirst;
	Food* p1=NULL;
	while(p){
		p1=p->next;
		delete p;
		p=p1;
	}
	this->Ffirst=NULL;
	return 0;
}


/*Class SellList F*/
//추가함수


//출력함수


int FoodList::AddFoodList (Food* A,int n){
	cout<<"S리스트 추가 실행"<<endl;
	if(Ffirst==NULL){
		cout<<"1번노드 추가 시작"<<endl;
		Ffirst = new Food(A->Fname,A->가격,n);
		cout<<"1번노드 추가 완료"<<endl;
		return 0;
	}
	cout<<"건너뜀";
	Food* NewNode =new Food(A->Fname,A->가격,n);;
	Food* p = (Ffirst); //마지막 노드를 알려주는 포인터
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<"n번 노드 추가 완료"<<endl;
		return 0;

}