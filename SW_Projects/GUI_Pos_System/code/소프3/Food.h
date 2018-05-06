#ifndef FOOD_H
#define FOOD_H
#endif // !FOOD_H
#include <iostream>
#pragma once
class Food{
public:
	char* Fname;
	int ����;
	int ���;
	int �Ǹŷ�;
	int season;
	Food* next;

	//������
	Food(){
		Fname=NULL;
		����=0;
		���=0;
		�Ǹŷ�=0;
		season =0;
		next=NULL;

	}
	Food(char* xname,int price,int n){
		Fname=new char [strlen(xname)+1];
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=NULL;
		}
		for(int i=0; i<strlen(xname); i++){
			Fname[i]=xname[i];
		}

		����=price;
		���=n;
		�Ǹŷ�=0;
		season =0;
		next=NULL;

	}
	Food(char* xname,int price,int n,int x�Ǹŷ�){
		Fname=new char [strlen(xname)];
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=NULL;
		}
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=xname[i];
		}
		����=price;
		���=n;
		�Ǹŷ�=x�Ǹŷ�;
		season=0;
		next=NULL;

	}
	Food(char* xname,int price,int n,int x�Ǹŷ�, int s){
		Fname=new char [strlen(xname)];
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=NULL;
		}
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=xname[i];
		}
		����=price;
		���=n;
		�Ǹŷ�=x�Ǹŷ�;
		season =s;
		next =NULL;

	}
	void ChangeName(char* Newname);
};
class FoodList{
public:
	Food* Ffirst;
	int Fcount;
	FoodList(){Ffirst=NULL, Fcount=0;}


	

	/*�߰��Լ�*/
	int AddFoodList(char* name,int price,int n,int xtotal);
	int AddFoodList(char* name,int price,int n,int xtotal,int season);
	int AddFoodList(Food* p,int n);
	/*����Լ�*/

	//������ ��ȯ �Լ�
	virtual Food* GetFood(int n);
	//�����Լ�
	int RemoveFoodNode(int n);
	//����Ʈ �����Լ�
	int RemoveFoodList();
	int SaveFoodList();
	int LoadFoodList();
};

