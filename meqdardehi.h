//
// Created by ASUS on 11/30/2024.
//

#ifndef UNTITLED4_MEQDARDEHI_H
#define UNTITLED4_MEQDARDEHI_H
extern int map[17][17];
extern int vProduction[20][2];
extern int KingdomPos[5][2];

void Kingdom(int k, int j);

void VillageProduction(int k , int array[20][2]);

void Village(int k, int j,int VillageNum);

void ForceClosed(int k, int j);

void Empty(int k, int j);

void Road(int xq,int yq,int xv,int yv);

#endif
