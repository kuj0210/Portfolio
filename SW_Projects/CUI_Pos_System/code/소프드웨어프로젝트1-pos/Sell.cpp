#include "Sell.h"
#include "Foods.h"
#include <iostream>
using namespace std;

//�Ǹ�
int AddSellList(SellList** FirstNode,Food** FoodNode, int n, int xn){
	Food* p= GetFoodPointer(FoodNode,n);
	if(n>p->incount){return 0;}
	if(!(p->n)||xn> p->n){
		cout<<p->name<<" ��ǰ�� ��� �����մϴ�.";
		return 0;
	}
	//���� �Ǹ� �� ����.
	p->total+=xn;
	//��� �Ǹŷ� ��ŭ ����.
	p->n-= xn;
	SellList* NewNode = new SellList(p,xn);

	if(!(*FirstNode)){
		*FirstNode = NewNode;
		return 0;
	}

	SellList* p1=*FirstNode;

	while(p1->p){
		p1=p1->p;
	}
	;
	p1->p=NewNode;
	return 0;
}
//�ǸŸ� ���� ����Ʈ�� ������
int ShowSellList(SellList** FirstNode){

	if(!(*FirstNode)){
		cout<<"<���� ����� �����ϴ�>"<<endl;
		return 0;
	}
	cout<<"<���� ����Ʈ.>"<<endl;
	int count=1;
	SellList* p = *FirstNode;
	while(p){
		cout<<"+"<<"<"<<count<<">"<<p->name<<" :  "<<p->price<<" ���ŷ�:"<<p->n<<endl;
		p=p->p;
		count++;
	}
	return 0;

}
//�Ǹ�,����������,������ϴ� �Լ�. �۵��ϸ鼭 �� ����
int RemoveSellList(SellList** FirstNode,int *t){

	SellList* p =(*FirstNode);
	SellList* p1=NULL;
	int total=0;
	int d=0;
	cout<<"������ ���� ����: 1-�� �׸�, 2-���Ÿ�� ����"<<endl<<endl<<"�Է�>>";
	cin>>d;
	cout<<endl;
	int x=0;
	if(d==1){
		while(p){
			p1=p->p;
			total+=(p->price)*(p->n);

			if(p->Event){
				total-=(p->Event)*(p->n);
			}	

			delete p;
			p=p1;
		}
		(*t)+=total;
		cout<<"���� "<<total<<"�Դϴ�."<<endl<<"�����ݾ�:";
		int x=0;
		cin>>x;
		cout<<"�Ž�����:"<<x-total<<endl<<endl;
		cout<<endl;
		cout<<"<������>"<<endl<<"�� ���� �ݾ�:"<<total<<endl<<"���� �ݾ�:"<<x<<endl<<"�Ž�����"<<x-total<<endl;

	}
	else{
		cout<<"<������>"<<endl;
		cout<<endl;
		ShowSellList(FirstNode);
		cout<<endl;
		while(p){
			p1=p->p;
			total+=(p->price)*(p->n);

			if(p->Event){
				total-=(p->Event)*(p->n);
			}	
			delete p;
			p=p1;
		}

		(*t)+=total;
		cout<<"�Ѿ�: "<<total<<endl<<"�����ݾ�:";
		cin>>x;
		cout<<"�Ž�����:"<<x-total<<endl;


	}
	cout<<"����ڸ� �Է��ϸ� �ʱ�ȭ������ �̵��մϴ�."<<endl;
	cin>>x;
	*FirstNode = NULL;

	return 0;
}


