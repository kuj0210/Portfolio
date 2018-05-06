#include "Sell.h"

#ifndef TABLE_H
#define TABLE_H

class Table{
public:
	int D; //����
	Table* p;//����Ʈ
	static int mycount;//�����̺��
	SellList* s;
	
	Table(int x=0): D(x){p=0; mycount++; s=0;};
};

int AddTableList(Table** FirstNode,int x);
int ShowTableList(Table** FirstNode);
Table* GetTablePointer(Table** FirstNode, int n);
int RemoveTableNode(Table** FirstNode,int n);
int RemoveTableList(Table** FirstNode);
int SetTable(Table* t, int n);


#endif // !TABLE_H
