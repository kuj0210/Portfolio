#include "stdafx.h"
#include "Table.h"
#include <iostream>

using namespace std;
	
	int TableList::AddTableList(){
		
	this->Tcount++;
	if(!this->TFirst){
		TFirst = new Table();
		return 0;
	}
	
	Table* NewNode =new Table();
	Table* p = (TFirst); //마지막 노드를 알려주는 포인터
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
	return 0;
	}
	Table* TableList::GetTablePointer(int n){
		cout<<"테이블 포인터 실행 n:"<<n<<endl;
			Table* Gp= TFirst;
	
	if( Gp==NULL ){
		cout<<"포인터 반환 오류 입력값을 확인해주세요";
		return NULL;
	}
	
	for(;n>0;n--){
		Gp=Gp->next;
	}
	
	return Gp;
	}
	int TableList::RemoveTableNode(int n){
		cout<<"리무브 노드 호출"<<endl;
		this->Tcount--;
		Table* Remover = GetTablePointer(n);	
		if(n==1){
			TFirst=Remover->next;
			delete Remover;
			return 0;
		}
	else if(Remover->next==NULL){
		Table* p= GetTablePointer(n-1);
		delete Remover;
		p->next=NULL;
		return 0;
	}
	else{
		Table* p= GetTablePointer(n-1);
		p->next = Remover->next;
		delete Remover;
	}
	return 0;
	}
	int TableList::RemoveTableList(){
	this->Tcount=0;
	Table *p=TFirst;
	Table *p1=TFirst;
	cout<<"첫노드 받기성공";

	
	cout<<"제거문 실행"<<endl;
	while(p){
		p1=p->next;
		delete p;
		p= p1;
	}
	cout<<"제거문 종료"<<endl;
	TFirst= NULL;
	cout<<"테이블노드 제거 종료"<<endl;
	return 0;
	}


	int TableList::SetTable(int n){
		if(this->GetTablePointer(n)->d!=-1)
			this->GetTablePointer(n)->d= !(this->GetTablePointer(n)->d);
		return 0;
	}
	int TableList::SaveTableList(){
			FILE* fp;
	fopen_s(&fp,"table.txt","wt");
	if(!fp){
		cout<<"Table를 쓸 수 없습니다."<<endl;
		return 0;
	}
	
	fprintf(fp,"%d",this->Tcount);

	fclose(fp);
	return 0;
	}
	int TableList::LoadTableList(){
	FILE* fp;
	fopen_s(&fp,"Table.txt","rt");
	if(!fp){
		cout<<"Table를 읽을 수 없습니다."<<endl;
		return 0;
	}

	
	int n;
	fscanf_s(fp,"%d",&n);
	for(;n>0;n--) 
		this->AddTableList();

	fclose(fp);
	return 0;
	}