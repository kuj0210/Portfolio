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
	
	//������ ����
	friend int AddFoodList(Food** FirstNode, char* name, int price ,int n,int total,int E);
	friend class SellList;
	//������
	Food(char* Xname="�̸�����",int Xprice=0, int N=0,int Xtotal=0,int XE=0):name(Xname),price(Xprice),n(N), total(Xtotal){
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
