#include "Table.h"
#include <iostream>
using namespace std;


int AddTableList(Table** FirstNode,int x){
	if(!(*FirstNode)){
		*FirstNode = new Table(x);
		return 0;
	}
	Table* NewNode =new Table(x);
	Table* p = *(FirstNode); //������ ��带 �˷��ִ� ������
	while(p->p){
		p= p->p;	
	}
	p->p=NewNode;
	return 0;

}
int ShowTableList(Table** FirstNode){
	if(!(*FirstNode)){
		cout<<"<���̺� �غ����Դϴ�.>"<<endl;
		return 0;
	}
	int count=1;
	Table* p = *FirstNode;
	
	while(p){
		cout<<"+"<<"<"<<count<<">"<<"�����̺� :  ";
		
		if(p->D==0)
			cout<<"��� ����";
		else if(p->D==-1)
			cout<<"������";
		else
			cout<<"��� �Ұ���";
		
		cout<<endl;
		p= p->p;
		count++;
	}
	return 0;

}
Table* GetTablePointer(Table** FirstNode, int n){
	Table* Gp= *FirstNode;
	
	if((!Gp) || Gp->mycount > n ){
		cout<<"������ ��ȯ ���� �Է°��� Ȯ�����ּ���";
		return NULL;
	}
	
	for(;n-1>0;n--){
		Gp=Gp->p;
	}
	
	return Gp;

}
int RemoveTableNode(Table** FirstNode,int n){
	if(n==1){
		Table* Remover = GetTablePointer(FirstNode,n);
		Table* p= GetTablePointer(FirstNode,n+1);
		delete Remover;
		*FirstNode=p;
		(p->mycount)--;
		return 0;
	}
	else if(n==(*FirstNode)->mycount){
		Table* Remover = GetTablePointer(FirstNode,n);
		Table* p= GetTablePointer(FirstNode,n-1);
		delete Remover;
		(p->mycount)--;
		p->p=NULL;
		return 0;
	}
	else{
		Table* Remover = GetTablePointer(FirstNode,n);
		Table* p= GetTablePointer(FirstNode,n-1);
		(p->mycount)--;
		p->p = Remover->p;
		delete Remover;
		
	}
	return 0;
}
int RemoveTableList(Table** FirstNode){
		Table *p=*FirstNode;
	if(!(*FirstNode))
		return 0;
	
	while(p->mycount){
		RemoveTableNode(FirstNode,p->mycount);
	}
	*FirstNode = NULL;
	return 0;

}
int SetTable(Table* t, int n){
	//�Լ� �������� ����
	if(!t) cout<<"���̺��� ���� ���߽��ϴ�"<<endl;
	if(t->D!=0&&n==1){ return 0;}
	if(n<-1 || n>1){ return 0; }
	t->D = n;
	return 0;
}