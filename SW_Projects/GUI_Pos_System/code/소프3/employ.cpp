#include "stdafx.h"
#include <iostream>
#include "employ.h"
#pragma once
using namespace std;


int EmployneeList::SaveE(){
	if(this->EFirst==NULL){cout<<"비어있다!"<<endl;}
	cout<<"E세이브실행"<<endl;
	FILE* fp;
	fopen_s(&fp,"E.txt","wt");
	if(!fp){
		cout<<"직원을 쓸 수 없습니다."<<endl;
		return 0;
	}
	Employnee* p = this->EFirst;
	if(this->EFirst ==NULL){
		cout<<"노드읎음"<<endl;
		return 0;
	}
	while(p!=NULL){
		cout<<"실행";
		//이름없음,price, 재고, event, 판매량
		cout<<p->name<<endl;
		fprintf_s(fp," %s %d %d %d %d",p->name,p->본인나이,p->급여계수,p->근무시간,p->고용코드);
		p=p->next;
	}
	fclose(fp);
	return 0;
}
int EmployneeList::LoadE(){
	cout<<"ELoad실행"<<endl;
	FILE* fp;
	fopen_s(&fp,"E.txt","rt");
	if(!fp){
		cout<<"직원을 읽을 수 없습니다."<<endl;
		return 0;
	}
		char name[100];
		for(int i=0; i<100;i++){ name[i]=NULL; }
		int 나이;
		int 급여;
		int 시간;
		int 고용;
	while(!feof(fp)){
		cout<<"<추가시작>"<<endl;
		fscanf_s(fp,"%s",name);
		fscanf_s(fp,"%d",&나이);
		fscanf_s(fp,"%d",&급여);
		fscanf_s(fp,"%d",&시간);
		fscanf_s(fp,"%d",&고용);
		cout<<"이름:"<<name<<endl;
		AddE(name,나이,급여,시간,고용);
		}
	fclose(fp);
	return 0;
}
//추가함수
int EmployneeList::AddE(char* n,int 나이,int 급여,int 시간,int 고용){
	cout<<endl<<"AddE 이름:"<<n<<"고용코드"<<고용<<endl;
	if(this->EFirst == NULL){
		EFirst = new Employnee(n,나이,급여,시간,고용);
		return 0;
	}
	Employnee* NewNode =new Employnee(n,나이,급여,시간,고용);
	Employnee* p = (EFirst); //마지막 노드를 알려주는 포인터
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
	
	cout<<"추가완료"<< p->next->name<<endl;
		return 0;
}



//포인터 반환 함수
Employnee* EmployneeList::GetE(int n){
	Employnee* Gp= EFirst;
	cout<<"E포인터 실행 n:"<<n<<endl;
	if(!(EFirst)){
		cout<<"E 반환실패";
		return NULL;
	}

	for(;n>0;n--){
		Gp=Gp->next;
	}

	return Gp;
}

//삭제함수
int EmployneeList::RemoveENode(int n){
	Employnee* Remover=NULL;
	Employnee* p=NULL;
	
	Remover =GetE(n);
	if(n==0){
		p= GetE(n+1);
		delete Remover;

		EFirst=p;
		return 0;
	}
	else if(Remover->next==NULL){
		p= GetE(n-1);
		p->next=NULL;
		delete Remover;
		return 0;
	}
	else{
		
		p= GetE(n-1);
		p->next = Remover->next;
		delete Remover;
	}
	return 0;
}
//리스트 삭제함수
int EmployneeList:: RemoveE(){
	Employnee* p=EFirst;
	Employnee*p1=NULL;
	cout<<"E리스트 삭제함수"<<endl;
	while(p){
		p1=p->next;
		delete p;
		p=p1;
	}
	cout<<"삭제끝;"<<endl;
	this->EFirst=NULL;
	return 0;
}
