#include<iostream>
#include"Foods.h"
#include"Table.h"
#include"Sell.h"
#include"Pos.h"
#include <conio.h>

#define ���� cout<<endl;
using namespace std;
//�� Ÿ���� FirstNode��
Table* FirstTableNode=NULL;
//static ��� �ʱ�ȭ
int Food::incount=0;
int Table::mycount=0;
//������ Ÿ��
Table* GTable();
//�����Լ�
void main(){

	LoadTableList(&FirstTableNode);//���̺��� ���¸� �о��. food�� ���� ������ �߰�.
	int ESC=0; //�Լ��� ���ᳪ ������ ������Ű�� ����. �ǹ̾��� ���� �޾Ƽ� ������Ŵ



	while(1){
		//�����Ⱑ ���� �� ��������Ʈ�� ����� ���۰� ���ÿ� firstnode���� �ʱ�ȭ�����ش�.
		Food::incount=0;
		Table::mycount=0;
		Food* FirstFoodNode= NULL;


		int posmoney=0;//�������� �ܰ�
		int key=0;//��й�ȣ�� ������ ��.
		int d=0;
		int ch=0;
		system("cls");
		LoadFoodList(&FirstFoodNode);//�޸��忡 ����� �� ����Ʈ���� ������ �о ����Ʈ �߰��Լ�(AddFoodList)�� ���� ����Ʈ�� �߰�.

		LoadPosMoney(&posmoney,&key);//����� ��й�ȣ�� pos���� �ܰ� �о�´�
		cout<<"��pos �ܰ�: "<<posmoney<<"��"<<endl;
		���� ����
			//�������� ���. 
			cout<<"��1 +���̺� ���+"<<endl<<"��2 +���+"<<endl<<"��3+���̺� Ȯ��+"<<endl<<
			"��4 +����+"<<endl<<"��5 ��������+"<<endl<<endl<<"�Է�>>";
		//������ �Է¹���
		cin>>d;
		//������ ���� �� ȭ���� ���� ȭ�� ��ȯ�� ȿ���� ��.
		system("cls");

		//if������ ���ÿ� �´� ���� ����.
		if(d==1){ //�Ǹŵ��. do~while()���� ����Ͽ� ����ؼ� �޴��� �Է¹ް���.

			Table* p= GTable();
			if(p){
			if(p->D != -1)
				SetTable(p,1);//������
			do {
				system("cls");
				ShowSellList(&p->s);
				����;
				ShowFoodList(&FirstFoodNode);
				����;
				cout<<"�޴��� ��ȣ�� ������ �ּ���"<<endl<<"�Է�>>";
				int n;
				cin>>n;
				int x;
				����;
				cout<<"������ �Է��� �ּ���"<<endl<<"�Է�>>";
				cin>>x;

				AddSellList(&p->s,&FirstFoodNode,n,x);
				cout<<"���ϿϷ�� 1 �Է�"<<endl;
				cin>>ch;	
			}while (ch!=1);//��ϿϷ�(=1 �Է�)�� �ϸ� ����
			}

		}
		else if(d==2){//���̺� �Ǹ� �Ϸ�.
			Table* p= GTable();
			//������ ���ÿ� ���,�������� ����ϴ� �Լ�.
			if(p){
			if(p->D == 1 ){
				cout<<"1-1";
			RemoveSellList(&p->s,&posmoney);
			SetTable(p,0);
			}
			
			else{
				cout<<"1-2";
				cout<<"�ٸ� ���̺��� �Է����ּ���. ���ڸ� �Է��Ͻø� �ʱ�ȭ������ �̵��մϴ�"<<endl<<"�Է� >>";
				cin>>ESC;
			}
			}
		}
		
		//���� ���̺��� ���¸� Ȯ���ϴ� �Լ�
		else if(d==3){
			ShowTableList(&FirstTableNode);
			//���� �ҽ��� �Ѿ�� �ʰ� ����
			cout<<"���ڸ� �Է��Ͻø� �ʱ�ȭ������ �̵��մϴ�"<<endl;
			cin>>ESC;
		}
		//����: ������ ������ ������.
		else if(d==4){
			cout<<"ȯ�� ó��: ����-> ������ ������ �� ������ ������ �Է�"<<endl<<"�����ڸ��: �ʱ� ��й�ȣ1011, ��й�ȣ ����: �����ڸ��->���漱��"<<endl;
			cout<<"����ڸ� �Է��Ͻø� �ʱ�ȭ������ �̵��մϴ�"<<endl;
			cin>>ESC; //�ҽ� ����
		}
		//����ڰ� ���� ������� ����ؼ� �Է��Ͽ� ��������� ���� ���̾��� ���Ͽ� �����Ѵ�.
		else if(d==5){
			int val[8] ={50000,10000,5000,1000,500,100,50,10}; //���ݾ��� ��ġ
			char* name[8]= { "������" , "����" , "��õ��" , "õ��" , "�����" , "���" , "���ʿ�" , "�ʿ�" };//���� �����
			int mn[8];//������ �Էµɰ�.
			//�ʱ�ȭ
			for(int i=0;i<8;i++)
				mn[i]=0;
			int sum =0;
			//
			for(int i=0;i<8;i++){
				cout<<name[i]<<": ";
				cin>>mn[i];
				cout<<endl;
			}
			for(int i=0;i<8;i++){
				sum += val[i] * mn[i];
			}

			cout<<"������: "<<sum-posmoney;
			����;
			FILE* fp=fopen("������.txt","a");
			fprintf(fp," %d",sum-posmoney);
			fclose(fp);
			cout<<"�����ϽǷ��� ���ڸ� �Է����ּ���"<<endl<<"�Է�>>";
			cin>>ESC;
		}
		//�����ڸ�����
		else if(d==key){
			int xd=0;
			do{
				int n = 0;
				system("cls");
				cout<<"�������ڸ�� ����(����! ���Ḧ �ϼž� ����˴ϴ�!)���"<<endl; ����
					cout<<"�� 1���̺� �߰�"<<endl<<"�� 2���̺� ����"<<endl<<"�� 3���̺� �������"<<endl<<"�� 4�޴��߰�"<<endl<<"�� 5�޴�����"<<endl<<"�� 6��� �߰�"<<endl<<"�� 7���"<<endl<<"�� 8��й�ȣ �缳��"<<endl<<"�� 9���ε��"<<endl<<"�� 10�����ܾװ���"<<endl<<"�� 11����"<<endl;
				����;
				cout<<"�Է�>>";
				cin>>xd;
				switch (xd){
				case 1:{
					system("cls");
					cout<<"�߰��Ͻ� ������ �Է��� �ּ���"<<endl<<">>�Է�:";
					cin>>n;
					for(;n>0;n--){
						AddTableList(&FirstTableNode,0); //���̺� �߰�.
					}
					break;
					   }
				case 2:{
					system("cls");
					ShowTableList(&FirstTableNode); 
					cout<<"�����Ͻ� ���̺��� ���ڸ� �Է����ּ���"<<endl<<"�Է�>>";
					cin>>n;
					RemoveTableNode(&FirstTableNode,n);
					break;
					   }
				case 3:{
					system("cls");
					ShowTableList(&FirstTableNode);
					cout<<"�����Ͻ� ���̺��� ���ڸ� �Է����ּ���"<<endl<<"�Է�>>";
					cin>>n;
					Table* p=GetTablePointer(&FirstTableNode,n);
					SetTable(p,-1);
					break;
					   }
				case 4:{
					system("cls");
					cout<<"�߰��� �޴��� �̸��� �Է����ּ���: ";
					char name[100];
					int price;
					int n;
					int E=0;
					cin>>name;
					cout<<"�߰��� �޴��� ������ �Է����ּ���: ";
					cin>>price;
					cout<<"�߰��� �޴��� ����� �Է����ּ���: ";
					cin>>n;
					cout<<"�߰��� �޴��� �̺�Ʈ ���� ������ �Է����ּ���: ";
					cin>>E;
					AddFoodList(&FirstFoodNode,name,price ,n,0,E); //��
					break;
					   }
				case 5:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"������ �޴��� ��ȣ�� �Է��� �ּ���: "<<endl<<"�Է�>>";
					cin>>n;
					RemoveFoodNode(&FirstFoodNode,n);
					break;
					   }
				case 6:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"��� �߰��� �޴��� ��ȣ�� �Է��� �ּ���: "<<endl<<"�Է�>>";
					cin>>n;
					system("cls");
					Food* p= GetFoodPointer(&FirstFoodNode,n);
					cout<<"���� ���:"<<p->n<<endl<<"���� �� ��� �Է� >>";
					cin>>n;
					p->n=n;
					break;

					   }
				case 7:{
					system("cls");
					���(FirstFoodNode);
					cout<<"����ڸ� �Է��Ͻø� �ʱ�ȭ������ �̵��մϴ�"<<endl;
					cin>>ESC;
					break;
					   }
				case 8:{
					system("cls");
					cout<<"���� ��й�ȣ��: "<<key<<"�Դϴ�"<<endl;
					cout<<"���� ������ ��й�ȣ(4�ڸ� �ڿ���)�� �Է����ּ���"<<endl<<"�Է�>>";
					if(0<=key && key<=9999){
						cin>>key;
					}
					break;
					   }
				case 9:{
					system("cls");
					ShowFoodList(&FirstFoodNode);
					cout<<"���� ����� �޴��� ��ȣ�� �Է��ϼ���"<<endl<<"�Է�>>";
					cin>>n;
					system("cls");
					Food* p1 = GetFoodPointer(&FirstFoodNode,n);
					cout<<endl<<p1->name<<" �޴��� ���ξ��� ����  "<<p1->Event<<" �� �Դϴ�."<<endl;
					cout<<"���ο� ���ξ�(0~�޴��� ���ݱ����� �ڿ���)�� �Է��� �ּ���"<<endl<<"�Է�>>";
					cin>>n;
					if(0<=n&&n<=p1->price){
						p1->Event=n;
					}
					break;
					   }
				case 10:{
					system("cls");
					int m=0;
					cout<<"�����ܾ�:"<<posmoney<<endl;
					cout<<"1.��� 2.�Ա�"<<endl<<"����>>";
					cin>>n;
					system("cls");
					if(n==1){

						cout<<"����� �ݾ�(0~�����ܾױ����� �ڿ���)�� �Է��� �ּ���"<<endl<<"�Է�>> ";
						cin>>m;
						if(0<=m&&m<=posmoney){
							posmoney-=m;
						}
					}
					else if(n==2){
						cout<<"�Ա��� �ݾ�(0�� �̻��� �ڿ���)�� �Է��� �ּ���"<<endl<<"�Է�>> ";
						cin>>m;
						if(0<=m){
							posmoney+=m;
						}
					}

					break;
						}
				}
			}while(xd !=11);
		}//�����ڸ�� ��!
		SaveFoodList(&FirstFoodNode);
		SavePosMoney(&posmoney,&key);
		RemoveFoodList(&FirstFoodNode);

	}//�Լ����볡

	SaveTableList(&FirstTableNode);
	RemoveTableList(&FirstTableNode);
}//���γ�


Table* GTable(){
	ShowTableList(&FirstTableNode);//���̺� ���
	cout<<"������� 0�Է�"<<endl;
	cout<<"����� ���̺� ��ȣ�� ������ �ּ���:";//������ �Է¹���
	int x;
	cin>>x;//�Է¹��� ���� ����
	
	if(x!=0){//0�̾ƴ϶�� ����
		
		Table* p=GetTablePointer(&FirstTableNode,x);// x��° ���̺� �����͸� ��ȯ�ϴ� �Լ�
		
		if(p->D == -1){
			cout<<"3-1";
			cout<<"�������� ���̺��Դϴ�. �ٸ� ���̺��� �������ּ���."<<endl;
			return 0;
		}
		
		return p;


	}
}



