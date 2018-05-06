#include<cstring>
#ifndef FOODS_H
#define FOODS_H


class Food{
	public:
	int Event;
	char* name;
	int price;
	int n;
	int total;
	static int incount;
Food* p;
	
	//프렌드 선언
	friend int AddFoodList(Food** FirstNode, char* name, int price ,int n,int total,int E);
	friend class SellList;
	//생성자
	Food(char* Xname="이름없음",int Xprice=0, int N=0,int Xtotal=0,int XE=0):name(Xname),price(Xprice),n(N), total(Xtotal){
		int len = strlen(Xname);
		name= new char[len];
		strcpy(name,Xname);
		
		p = 0;
		Event = XE;
		incount++;
	};
	
	
	
	void SetEvent(int a);
};
int RemoveFoodList(Food** FirstNode);
Food* GetFoodPointer(Food** FirstNode, int n);
int AddFoodList(Food** FirstNode, char* name, int price ,int n,int total,int E);
int ShowFoodList(Food** FirstNode);
int RemoveFoodNode(Food** FirstNode,int n);




#endif // !FOODS_H
