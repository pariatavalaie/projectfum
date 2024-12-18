//
// Created by ASUS on 11/30/2024.
//

#ifndef UNTITLED4_MEQDARDEHI_H
#define UNTITLED4_MEQDARDEHI_H
#include "type.h"
extern int map[17][17];
struct Kingdom;
struct Village;

void Kingdoms(int k, int j , struct Kingdom kingdoms[], int* kingdomCount);

void VillageProduction(int k , int array[20][2]);

void Villages(int k, int j, struct Village villages[], int* villageCount);

void ForceClosed(int k, int j);

void Empty(int k, int j);

void Road(int xq,int yq,int xv,int yv);

#endif
