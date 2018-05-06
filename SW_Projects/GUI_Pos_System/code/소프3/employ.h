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
	int 본인나이;
	int 근무시간;
	int 급여계수; //알바생이라면 시급, 정직원이라면 호봉
	int 고용코드;//100:아르바이트생 200:정직원
	Employnee* next;

	Employnee(){
		this->name = 0;
		this->급여계수=0;
		this->본인나이=0;
		this->고용코드=0;
		this->근무시간=0;
		next=0;
	};
	Employnee(char* n,int 나이,int 급여,int 시간,int 고용){
		cout<<"E생성자실행"<<endl;
		this->name = new char [strlen(n)];
		cout<<"이름배열생성"<<endl;
		for(int i=0; i<strlen(n);i++){ name[i]=n[i]; }
		name[strlen(n)]=0;
		cout<<"이름복사완료"<<endl;
		this->급여계수=급여;
		this->고용코드=고용; cout<<"고용코드:"<<this->고용코드<<endl;
		this->근무시간=시간;
		this->본인나이=나이;

		next=0;
	};
};

class EmployneeList: public Employnee{
public:
	Employnee* EFirst;

	EmployneeList(){ EFirst=NULL; this->LoadE();}
	~EmployneeList(){this->SaveE(); this->RemoveE();}
	int AddE(char* n,int 나이,int 급여,int 시간,int 고용);
	int	RemoveE();
	int	RemoveENode(int n);
	Employnee* GetE(int n);
	int SaveE();
	int LoadE();
	 


};
