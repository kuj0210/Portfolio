#include "Foods.h"
#include <iostream>
using namespace std;
#ifndef SELL_H
#define SELL_H

//ToDo 판매용리스트, 연산자 오버로딩

class SellList{
public:
	char* name;
	int price;
	int n;
	int Event;
	SellList* p;
	SellList(Food* A,int N){
		Event = A->Event;
		int len = strlen(A->name);
		name= new char[len];
		strcpy(name,A->name);
		price = A->price;
		n=N;
		p=NULL;
	}
};

int AddSellList(SellList** FirstNode,Food** FoodNode, int n, int xn);
int ShowSellList(SellList** FirstNode);
int RemoveSellList(SellList** FirstNode,int *t);


#endif // !SELL_H
