//
// Created by Asus on 12/27/2024.
//

#ifndef PROJECTFUM_GAMEUPDATE_H
#define PROJECTFUM_GAMEUPDATE_H
#include "raylib.h"
#include "GRID2.h"
#include "meqdardehi.h"
#include "type.h"
extern  int winner;

void Food();

void workers();

void Upgrade();

void soldier();

void Road(int xroad,int yroad,int villagecount);

void takeV(int villagecount);

void CheckCell(int xroad , int yroad);

void destroy(int looserkingdom,int xr,int yr);

void DestroyRoads(int loserKingdom, int xRoad, int yRoad,int villagecount);

void BattleV( int attacker , int defender , int i  , int Xroad , int Yroad,int villagecount);

void BattleR(int Xroad , int Yroad , int attacker , int defender,int villagecount  );

void BattleK(int Xroad , int Yroad , int attacker ,int defender ,int villagecount);

void CheckForBattle(int Xroad , int Yroad , int villageCount);

#endif //PROJECTFUM_GAMEUPDATE_H
