#include <iostream>
#include "Foods.h"
#include "Table.h"
#include "Pos.h"
#include <cstdio>
using namespace std;
//푸드함수를 저장.
int SaveFoodList(Food** FirstNode){
	FILE* fp = fopen("food.txt","wt");
	if(!fp){
		cout<<"food를 쓸 수 없습니다."<<endl;
		return 0;
	}
	Food* p = *FirstNode;
	while(p){
		//이름없음,price, 재고, event, 판매량
		fprintf(fp," %s %d %d %d %d",p->name,p->price,p->n,p->Event,p->total);
		p=p->p;
	}
	fclose(fp);
	return 0;
}
//저장된 내용을 읽어 리스트화
int LoadFoodList(Food** FirstNode){
	FILE* fp= fopen("food.txt","rt");
	if(!fp){
		cout<<"food를 읽을 수 없습니다."<<endl;
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
//테이블 저장
int SaveTableList(Table** FirstNode){
	FILE* fp = fopen("Table.txt","wt");
	if(!fp){
		cout<<"테이블 쓰기 실패"<<endl;
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
//테이블정보를 읽음
int LoadTableList(Table** FirstNode){
	FILE* fp = fopen("Table.txt","rt");
	int d;
	if(!fp){
		cout<<"테이블 파일 읽기 실패"<<endl;
		return 0;
	}
	while(!feof(fp)){
		fscanf(fp,"%d",&d);
		AddTableList(FirstNode,d);
	}
	fclose(fp);
	return 0;

}
//포스기의 돈과 비밀번호를 저장
int SavePosMoney(int* m,int* key){
	FILE *fp= fopen("masterkey.txt","wt");
	fprintf(fp,"%d %d",*m,*key);
	fclose(fp);
	return 0;
}
//포스기의 돈과 비밀번호를 읽음
int LoadPosMoney(int* m,int*key){
	FILE  *fp= fopen("masterkey.txt","rt");
	fscanf(fp,"%d",&(*m));
	fscanf(fp,"%d",&(*key));
	fclose(fp);
	return 0;
}
//통계를 내어줌.
int 통계(Food* FirstNode){
	int count=1;
	int total=0;
	Food* p = FirstNode;
	while(p->p){
		cout<<"+"<<"<"<<count<<">"<<p->name<<" :  "<<p->price<<" 판매량: "<<p->total<<" 판매액수: "<<(p->total)*(p->price)<<endl<<endl;
		count++;
		total+=(p->total)*(p->price);
		p->total=0;
		p=p->p;
	}
	cout<<endl<<"총 판매액수: "<<total<<endl;
	return 0;

}