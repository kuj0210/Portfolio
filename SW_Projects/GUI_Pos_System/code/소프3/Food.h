#ifndef FOOD_H
#define FOOD_H
#endif // !FOOD_H
#include <iostream>
#pragma once
class Food{
public:
	char* Fname;
	int 가격;
	int 재고;
	int 판매량;
	int season;
	Food* next;

	//생성자
	Food(){
		Fname=NULL;
		가격=0;
		재고=0;
		판매량=0;
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

		가격=price;
		재고=n;
		판매량=0;
		season =0;
		next=NULL;

	}
	Food(char* xname,int price,int n,int x판매량){
		Fname=new char [strlen(xname)];
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=NULL;
		}
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=xname[i];
		}
		가격=price;
		재고=n;
		판매량=x판매량;
		season=0;
		next=NULL;

	}
	Food(char* xname,int price,int n,int x판매량, int s){
		Fname=new char [strlen(xname)];
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=NULL;
		}
		for(int i=0; i<strlen(xname)+1; i++){
			Fname[i]=xname[i];
		}
		가격=price;
		재고=n;
		판매량=x판매량;
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


	

	/*추가함수*/
	int AddFoodList(char* name,int price,int n,int xtotal);
	int AddFoodList(char* name,int price,int n,int xtotal,int season);
	int AddFoodList(Food* p,int n);
	/*출력함수*/

	//포인터 반환 함수
	virtual Food* GetFood(int n);
	//삭제함수
	int RemoveFoodNode(int n);
	//리스트 삭제함수
	int RemoveFoodList();
	int SaveFoodList();
	int LoadFoodList();
};

