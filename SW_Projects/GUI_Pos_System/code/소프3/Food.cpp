#include "stdafx.h"
#include <iostream>
#include "Food.h"
#include <String>
using namespace std;
#pragma once
/*Class FoodList F*/
void Food::ChangeName(char* Newname){
	cout<<"������"<<endl;
	delete (this->Fname);
	cout<<"������"<<endl;
	this->Fname=new char [strlen(Newname)+1];
		for(int i=0; i<strlen(Newname)+1; i++){
				this->Fname[i]=NULL;
			}

			for(int i=0; i<strlen(Newname); i++){
				this->Fname[i]=Newname[i];
			}
};

int FoodList::SaveFoodList(){

	FILE* fp;
	fopen_s(&fp,"food.txt","wt");
	if(!fp){
		cout<<"food�� �� �� �����ϴ�."<<endl;
		return 0;
	}
	Food* p = Ffirst;
	while(p){
		//�̸�����,price, ���, event, �Ǹŷ�
		fprintf_s(fp," %s %d %d %d %d",p->Fname,p->����,p->���,p->�Ǹŷ�,p->season);
		p=p->next;
		if(p==NULL) break;
	}
	fclose(fp);
	return 0;
}
int FoodList::LoadFoodList(){
	FILE* fp;
	fopen_s(&fp,"food.txt","rt");
	if(!fp){
		cout<<"food�� ���� �� �����ϴ�."<<endl;
		return 0;
	}
	cout<<"FOODLIST_ �б� ����";
		char name[100];
		for(int i=0; i<100;i++){ name[i]=NULL; }
		int price;
		int n;
		int Total;
		int season;
	while(!feof(fp)){
		fscanf_s(fp,"%s",name);
		fscanf_s(fp,"%d",&price);
		fscanf_s(fp,"%d",&n);
		fscanf_s(fp,"%d",&Total);
		fscanf_s(fp,"%d",&season);
		printf("%s : %d\n",name,season);
		printf("ADD����\n");
		AddFoodList(name,price,n,Total,season);
		
		
	}
	fclose(fp);
	return 0;
}
//�߰��Լ�
int FoodList::AddFoodList(char* name, int price, int n,int xtotal){
	this->Fcount++;
	if(this->Ffirst==NULL){
		Ffirst = new Food(name,price,n,xtotal);

		return 0;
	}
	Food* NewNode =new Food(name,price,n);
	Food* p = (Ffirst); //������ ��带 �˷��ִ� ������
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<endl;
		return 0;
}

int FoodList::AddFoodList(char* name, int price, int n,int xtotal, int season){
	this->Fcount++;
	if(this->Ffirst==NULL){
		Ffirst = new Food(name,price,n,xtotal,season);
		cout<<endl<<"ù��������ȣ"<<Ffirst->season<<endl;
		return 0;
	}
	Food* NewNode =new Food(name,price,n,xtotal,season);
	cout<<"������ȣ:"<<NewNode->season<<endl;
	Food* p = (Ffirst); //������ ��带 �˷��ִ� ������
	cout<<"������ �ޱ�";
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<endl;
		return 0;
}

//����Լ�


//������ ��ȯ �Լ�
Food* FoodList::GetFood(int n){
	Food* Gp= Ffirst;
	cout<<"Ǫ�� ������ ���� n:"<<n<<endl;
	if(!(Ffirst) || this->Fcount<n){
		cout<<"FPoint ��ȯ����";
		return NULL;
	}

	for(;n>0;n--){
		Gp=Gp->next;
	}
	cout<<"GP->Fname:"<<Gp->Fname<<endl;
	return Gp;
}

//�����Լ�
int FoodList::RemoveFoodNode(int n){
	Food* Remover;
	Food* p;
	if(n==1){

		Remover =GetFood(n);
		p= GetFood(n+1);


		delete Remover;

		Ffirst=p;
		this->Fcount--;
		return 0;
	}
	else if(n==this->Fcount){
		Remover =GetFood(n);
		p= GetFood(n-1);
		this->Fcount--;
		p->next=NULL;
		delete Remover;
		return 0;
	}
	else{
		Remover = GetFood(n);
		p= GetFood(n-1);
		(this->Fcount)--;
		p->next = Remover->next;
		delete Remover;
	}
	return 0;
}
//����Ʈ �����Լ�
int FoodList::RemoveFoodList(){
	this->Fcount=0;
	Food* p=Ffirst;
	Food* p1=NULL;
	while(p){
		p1=p->next;
		delete p;
		p=p1;
	}
	this->Ffirst=NULL;
	return 0;
}


/*Class SellList F*/
//�߰��Լ�


//����Լ�


int FoodList::AddFoodList (Food* A,int n){
	cout<<"S����Ʈ �߰� ����"<<endl;
	if(Ffirst==NULL){
		cout<<"1����� �߰� ����"<<endl;
		Ffirst = new Food(A->Fname,A->����,n);
		cout<<"1����� �߰� �Ϸ�"<<endl;
		return 0;
	}
	cout<<"�ǳʶ�";
	Food* NewNode =new Food(A->Fname,A->����,n);;
	Food* p = (Ffirst); //������ ��带 �˷��ִ� ������
	while(p->next){
		p= p->next;	
	}
	p->next=NewNode;
		cout<<"n�� ��� �߰� �Ϸ�"<<endl;
		return 0;

}