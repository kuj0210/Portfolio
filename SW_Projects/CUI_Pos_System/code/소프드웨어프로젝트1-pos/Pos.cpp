#include <iostream>
#include "Foods.h"
#include "Table.h"
#include "Pos.h"
#include <cstdio>
using namespace std;
//Ǫ���Լ��� ����.
int SaveFoodList(Food** FirstNode){
	FILE* fp = fopen("food.txt","wt");
	if(!fp){
		cout<<"food�� �� �� �����ϴ�."<<endl;
		return 0;
	}
	Food* p = *FirstNode;
	while(p){
		//�̸�����,price, ���, event, �Ǹŷ�
		fprintf(fp," %s %d %d %d %d",p->name,p->price,p->n,p->Event,p->total);
		p=p->p;
	}
	fclose(fp);
	return 0;
}
//����� ������ �о� ����Ʈȭ
int LoadFoodList(Food** FirstNode){
	FILE* fp= fopen("food.txt","rt");
	if(!fp){
		cout<<"food�� ���� �� �����ϴ�."<<endl;
		return 0;
	}

	while(!feof(fp)){
		char name[100];
		char* c=name;
		int price;
		int n;
		int Event;
		int Total;
		fscanf(fp,"%s",name);
		strcpy(c,name);
		fscanf(fp,"%d",&price);
		fscanf(fp,"%d",&n);
		fscanf(fp,"%d",&Event);
		fscanf(fp,"%d",&Total);
		AddFoodList(FirstNode,c,price,n,Total,Event);
	}
	fclose(fp);
	return 0;
}
//���̺� ����
int SaveTableList(Table** FirstNode){
	FILE* fp = fopen("Table.txt","wt");
	if(!fp){
		cout<<"���̺� ���� ����"<<endl;
		return 0;
	}
	Table* p= * FirstNode;
	while(p){
		fprintf(fp," %d",p->D);
		p=p->p;
	}
	fclose(fp);
	return 0;

}
//���̺������� ����
int LoadTableList(Table** FirstNode){
	FILE* fp = fopen("Table.txt","rt");
	int d;
	if(!fp){
		cout<<"���̺� ���� �б� ����"<<endl;
		return 0;
	}
	while(!feof(fp)){
		fscanf(fp,"%d",&d);
		AddTableList(FirstNode,d);
	}
	fclose(fp);
	return 0;

}
//�������� ���� ��й�ȣ�� ����
int SavePosMoney(int* m,int* key){
	FILE *fp= fopen("masterkey.txt","wt");
	fprintf(fp,"%d %d",*m,*key);
	fclose(fp);
	return 0;
}
//�������� ���� ��й�ȣ�� ����
int LoadPosMoney(int* m,int*key){
	FILE  *fp= fopen("masterkey.txt","rt");
	fscanf(fp,"%d",&(*m));
	fscanf(fp,"%d",&(*key));
	fclose(fp);
	return 0;
}
//��踦 ������.
int ���(Food* FirstNode){
	int count=1;
	int total=0;
	Food* p = FirstNode;
	while(p->p){
		cout<<"+"<<"<"<<count<<">"<<p->name<<" :  "<<p->price<<" �Ǹŷ�: "<<p->total<<" �Ǹž׼�: "<<(p->total)*(p->price)<<endl<<endl;
		count++;
		total+=(p->total)*(p->price);
		p->total=0;
		p=p->p;
	}
	cout<<endl<<"�� �Ǹž׼�: "<<total<<endl;
	return 0;

}