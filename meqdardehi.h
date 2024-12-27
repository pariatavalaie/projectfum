//
// Created by ASUS on 11/30/2024.
//

#ifndef UNTITLED4_MEQDARDEHI_H
#define UNTITLED4_MEQDARDEHI_H
#include "type.h"
extern int map[17][17];
extern Kingdom kingdoms[4];
extern Village villages[20];
extern int currentkingdom;
struct Kingdom;
struct Village;

void Kingdoms(int k, int j , struct Kingdom kingdoms[], int* kingdomCount);

void Villages(int k, int j, struct Village villages[], int* villageCount);

void ForceClosed(int k, int j);

void Empty(int k, int j);

void SuggestedRoad(int xq,int yq,int xv,int yv);

void DrawButtons(int screenWidth, int screenHeight, const char *buttonLabels[5], void (*buttonActions[5])());

void Attack();

void Food();

void workers();

void Upgrade(Kingdom kingdoms[],int count);

void soldier();
void Road(int xroad,int yroad,int villagecount);
void takeV(int villagecount);
#endif
