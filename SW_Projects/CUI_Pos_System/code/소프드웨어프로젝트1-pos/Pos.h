#include "Foods.h"
#include "Table.h"
#include "Sell.h"

#ifndef POS_H
#define POS_H


int SaveFoodList(Food** FirstNode);
int LoadFoodList(Food** FirstNode);
int SaveTableList(Table** FirstNode);
int LoadTableList(Table** FirstNode);
int SavePosMoney(int* m,int*key);
int LoadPosMoney(int* m,int*key);
int Ελ°θ(Food* FirstNode);
#endif // !POS_H
