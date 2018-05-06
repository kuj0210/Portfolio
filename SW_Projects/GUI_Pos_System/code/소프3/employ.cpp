#include "stdafx.h"
#include <iostream>
#include "employ.h"
#pragma once
using namespace std;


int EmployneeList::SaveE(){
	if(this->EFirst==NULL){cout<<"����ִ�!"<<endl;}
	cout<<"E���̺����"<<endl;
	FILE* fp;
	fopen_s(&fp,"E.txt","wt");
	if(!fp){
		cout<<"������ �� �� �����ϴ�."<<endl;
		return 0;
	}
	Employnee* p = this->EFirst;
	if(this->EFirst ==NULL){
		cout<<"������"<<endl;
		return 0;
	}
	while(p!=NULL){
		cout<<"����";
		//�̸�����,price, ���, event, �Ǹŷ�
		cout<<p->name<<endl;
		fprintf_s(fp," %s %d %d %d %d",p->name,p->���γ���,p->�޿����,p->�ٹ��ð�,p->����ڵ�);
		p=p->next;
	}
	fclose(fp);
	return 0;
}
int EmployneeList::LoadE(){
	cout<<"ELoad����"<<endl;
	FILE* fp;
	fopen_s(&fp,"E.txt","rt");
	if(!fp){
		cout<<"������ ���� �� �����ϴ�."<<endl;
		return 0;
	}
		char name[100];
		for(int i=0; i<100;i++){ name[i]=NULL; }
		int ����;
		int �޿�;
		int �ð�;
		int ���;
	while(!feof(fp)){
		cout<<"<�߰�����>"<<endl;
		fscanf_s(fp,"%s",name);
		fscanf_s(fp,"%d",&����);
		fscanf_s(fp,"%d",&�޿�);
		fscanf_s(fp,"%d",&�ð�);
		fscanf_s(fp,"%d",&���);
		cout<<"�̸�:"<<name<<endl;
		AddE(name,����,�޿�,�ð�,���);
		}
	fclose(fp);
	return 0;
}
//�߰��Լ�
int EmployneeList::AddE(char* n,int ����,int �޿�,int �ð�,int ���){
	cout<<endl<<"AddE �̸�:"<<n<<"����ڵ�"<<���<<endl;
	if(this->EFirst == NULL){
		EFirst = new Employnee(n,����,�޿�,�ð�,���);
		return 0;
	}
	Employnee* NewNode =new Employnee(n,����,�޿�,�ð�,���);
	Employnee* p = (EFirst); //������ ��带 �˷��ִ� ������
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
	
	cout<<"�߰��Ϸ�"<< p->next->name<<endl;
		return 0;
}



//������ ��ȯ �Լ�
Employnee* EmployneeList::GetE(int n){
	Employnee* Gp= EFirst;
	cout<<"E������ ���� n:"<<n<<endl;
	if(!(EFirst)){
		cout<<"E ��ȯ����";
		return NULL;
	}

	for(;n>0;n--){
		Gp=Gp->next;
	}

	return Gp;
}

//�����Լ�
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
//����Ʈ �����Լ�
int EmployneeList:: RemoveE(){
	Employnee* p=EFirst;
	Employnee*p1=NULL;
	cout<<"E����Ʈ �����Լ�"<<endl;
	while(p){
		p1=p->next;
		delete p;
		p=p1;
	}
	cout<<"������;"<<endl;
	this->EFirst=NULL;
	return 0;
}
