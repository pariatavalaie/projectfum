//
// Created by Asus on 12/27/2024.
//
#include "raylib.h"
#include "GRID2.h"
#include "meqdardehi.h"
#include "type.h"


void workers() {
    if (kingdoms[currentkingdom].Serve >= 3) {
        kingdoms[currentkingdom].WorkersCount++;
        kingdoms[currentkingdom].Serve -= 3;
    }else currentkingdom--;
}

void Upgrade(Kingdom *kingdoms, int count) {
    kingdoms[count].Gold += kingdoms[count].GoldProduction;
    kingdoms[count].Serve += kingdoms[count].FoodProduction;
}

void Food() {
    if (kingdoms[currentkingdom].Gold >= 1) {
        kingdoms[currentkingdom].Serve++;
        kingdoms[currentkingdom].Gold--;
    }else currentkingdom--;
}

void soldier() {
    if (kingdoms[currentkingdom].Gold >= 2) {
        kingdoms[currentkingdom].soldierCount++;
        kingdoms[currentkingdom].Gold -= 2;
    }else currentkingdom--;
}
void CheckCell(int xroad , int yroad){
    int cellDifficulty = map[xroad][yroad];
    if (cellDifficulty > kingdoms[currentkingdom].WorkersCount) {
        int remainingDifficulty = cellDifficulty - kingdoms[currentkingdom].WorkersCount;
        map[xroad][yroad] = remainingDifficulty;
    }
    else {
        map[xroad][yroad]=-currentkingdom;
    }
}

void takeV(int villagecount) {
    for (int k = 0; k < villagecount; k++) {
        int i = villages[k].x;
        int j = villages[k].y;
        if (villages[k].ownerId < 0)
            if (map[i][j - 1] == -currentkingdom || map[i][j + 1] == -currentkingdom ||
                map[i - 1][j] == -currentkingdom || map[i + 1][j] == -currentkingdom) {
                villages[k].ownerId = currentkingdom;
                kingdoms[currentkingdom].villagenumber++;
                kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
            }
    }
}
void Road(int xroad,int yroad,int villagecount){
    int difficulty=map[xroad][yroad];

    if(map[xroad][yroad]!='c'&&map[xroad][yroad]!='x'&&map[xroad][yroad]!='v'){
        if(xroad==kingdoms[currentkingdom].x) {
            if (yroad == kingdoms[currentkingdom].y - 1 || yroad == kingdoms[currentkingdom].y + 1)
                CheckCell(xroad, yroad);
        }

        if(yroad==kingdoms[currentkingdom].y){
            if(xroad==kingdoms[currentkingdom].x-1||xroad==kingdoms[currentkingdom].x+1)
                CheckCell(xroad,yroad);
        }
        if(map[xroad][yroad+1]==-currentkingdom||map[xroad][yroad-1]==-currentkingdom||map[xroad+1][yroad]==-currentkingdom||map[xroad-1][yroad]==-currentkingdom)
            CheckCell(xroad,yroad);
        for (int i = 0; i < villagecount ; ++i) {
            if(villages[i].ownerId==currentkingdom){
                if(xroad==villages[i].x) {
                    if (yroad == villages[i].y + 1 || yroad == villages[i].y - 1) {
                        CheckCell(xroad, yroad);
                    }
                }
                if(yroad==villages[i].y){
                    if(xroad==villages[i].x-1||xroad==villages[i].x+1){
                        CheckCell(xroad,yroad);
                    }
                }
            }
        }
    }
    else if(map[xroad][yroad]==difficulty) currentkingdom--;
}


