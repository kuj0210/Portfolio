#ifndef EMPLOY_H
#define EMPLOY_H
#endif // !EMPLOY_H
#include <string.h>
#include <iostream>
using namespace std;

#pragma once


class Employnee{
public:
	char* name;
	int ���γ���;
	int �ٹ��ð�;
	int �޿����; //�˹ٻ��̶�� �ñ�, �������̶�� ȣ��
	int ����ڵ�;//100:�Ƹ�����Ʈ�� 200:������
	Employnee* next;

	Employnee(){
		this->name = 0;
		this->�޿����=0;
		this->���γ���=0;
		this->����ڵ�=0;
		this->�ٹ��ð�=0;
		next=0;
	};
	Employnee(char* n,int ����,int �޿�,int �ð�,int ���){
		cout<<"E�����ڽ���"<<endl;
		this->name = new char [strlen(n)];
		cout<<"�̸��迭����"<<endl;
		for(int i=0; i<strlen(n);i++){ name[i]=n[i]; }
		name[strlen(n)]=0;
		cout<<"�̸�����Ϸ�"<<endl;
		this->�޿����=�޿�;
		this->����ڵ�=���; cout<<"����ڵ�:"<<this->����ڵ�<<endl;
		this->�ٹ��ð�=�ð�;
		this->���γ���=����;

		next=0;
	};
};

class EmployneeList: public Employnee{
public:
	Employnee* EFirst;

	EmployneeList(){ EFirst=NULL; this->LoadE();}
	~EmployneeList(){this->SaveE(); this->RemoveE();}
	int AddE(char* n,int ����,int �޿�,int �ð�,int ���);
	int	RemoveE();
	int	RemoveENode(int n);
	Employnee* GetE(int n);
	int SaveE();
	int LoadE();
	 


};
