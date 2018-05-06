#ifndef TABLE_H
#define TABEL_H
#endif // !TABLE_H
#include "Food.h"
#include <iostream>
using namespace std;
#pragma once
class Table{
public:
	FoodList InTList;
	int d;
	Table* next;
	Table(){d=0;next=0;}
};

class TableList{
public:
	Table* TFirst;
	int Tcount;
	TableList(){TFirst=NULL;Tcount=0;this->LoadTableList();}
	~TableList(){ cout<<"테이블 소멸자: 저장 호출"<<endl; this->SaveTableList(); cout<<"테이블:노드제거호출"<<endl; this->RemoveTableList();}
	int AddTableList();
	Table* GetTablePointer(int n);
	int RemoveTableNode(int n);
	int RemoveTableList();
	int SetTable(int n);
	int SaveTableList();
	int LoadTableList();
};