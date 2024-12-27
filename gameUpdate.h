//
// Created by Asus on 12/27/2024.
//

#ifndef PROJECTFUM_GAMEUPDATE_H
#define PROJECTFUM_GAMEUPDATE_H
#include "raylib.h"
#include "GRID2.h"
#include "meqdardehi.h"
#include "type.h"

void Food();

void workers();

void Upgrade(Kingdom kingdoms[],int count);

void soldier();

void Road(int xroad,int yroad,int villagecount);

void takeV(int villagecount);

void CheckCell(int xroad , int yroad);

#endif //PROJECTFUM_GAMEUPDATE_H
