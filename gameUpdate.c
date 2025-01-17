//
// Created by Asus on 12/27/2024.
//
#include "raylib.h"
#include "GRID2.h"
#include "meqdardehi.h"
#include "type.h"
#include "gameUpdate.h"
extern int x,y;

void workers() {
    if (kingdoms[currentkingdom].Serve >= 3) {
        kingdoms[currentkingdom].WorkersCount++;
        kingdoms[currentkingdom].Serve -= 3;
        Upgrade();
    }else currentkingdom--;
}

void Upgrade() {
    kingdoms[currentkingdom].Gold+=kingdoms[currentkingdom].GoldProduction;
    kingdoms[currentkingdom].Serve+=kingdoms[currentkingdom].FoodProduction;
}

void Food() {
    if (kingdoms[currentkingdom].Gold >= 1) {
        kingdoms[currentkingdom].Serve++;
        kingdoms[currentkingdom].Gold--;
        Upgrade();
    }else currentkingdom--;
}

void soldier() {
    if (kingdoms[currentkingdom].Gold >= 2) {
        kingdoms[currentkingdom].soldierCount++;
        kingdoms[currentkingdom].Gold -= 2;
        Upgrade();
    }else currentkingdom--;
}
void CheckCell(int xroad , int yroad){
    int cellDifficulty = map[xroad][yroad].type;
    if (cellDifficulty > kingdoms[currentkingdom].WorkersCount) {
        int remainingDifficulty = cellDifficulty - kingdoms[currentkingdom].WorkersCount;
        map[xroad][yroad].type = remainingDifficulty;
    }
    else {
        map[xroad][yroad].type=-currentkingdom;
    }
}

void takeV(int villagecount) {
    for (int k = 0; k < villagecount; k++) {
        int i = villages[k].x;
        int j = villages[k].y;

        if (villages[k].ownerId < 0) {

            if (i == 0 && j == 0) {
                if (map[i][j + 1].type == -currentkingdom || map[i + 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom + 1;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (i == 0 && j == y - 1) {
                if (map[i][j - 1].type== -currentkingdom || map[i + 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (i == x - 1 && j == 0) {
                if (map[i - 1][j].type == -currentkingdom || map[i][j + 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (i == x - 1 && j == y - 1) {
                if (map[i][j - 1].type == -currentkingdom || map[i - 1][j].type== -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }else if (i == 0) {
                if (map[i][j - 1].type == -currentkingdom || map[i][j + 1].type == -currentkingdom ||
                    map[i + 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (i == x - 1) {
                if (map[i][j - 1].type == -currentkingdom || map[i][j + 1].type == -currentkingdom ||
                    map[i - 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (j == 0) {
                if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                    map[i][j + 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (j == y - 1) {
                if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                    map[i][j - 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom ;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            }
            else if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                     map[i][j - 1].type== -currentkingdom || map[i][j + 1].type == -currentkingdom) {
                villages[k].ownerId = currentkingdom ;
                kingdoms[currentkingdom].villagenumber++;
                kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
            }
        }
    }
}
void Road(int xroad,int yroad,int villagecount) {
    int dificult = map[xroad][yroad].type;
    if (map[xroad][yroad].type != 'c' && map[xroad][yroad].type != 'x' && map[xroad][yroad].type != 'v') {
        if (xroad == kingdoms[currentkingdom].x) {
            if (yroad == kingdoms[currentkingdom].y - 1 || yroad == kingdoms[currentkingdom].y + 1) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        }

        if (yroad == kingdoms[currentkingdom].y) {
            if (xroad == kingdoms[currentkingdom].x - 1 || xroad == kingdoms[currentkingdom].x + 1) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        }
        if (xroad == 0 && yroad == 0) {
            if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad + 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        }
    } else if (xroad == 0)
        if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad][yroad - 1].type == -currentkingdom ||
            map[xroad + 1][yroad].type == -currentkingdom) {
            CheckCell(xroad, yroad);
            Upgrade();
        } else if (yroad == 0)
            if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad + 1][yroad].type == -currentkingdom ||
                map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            } else if (xroad == x - 1 && yroad == y - 1) {
                if (map[xroad][yroad - 1].type == -currentkingdom || map[xroad - 1][yroad].type == -currentkingdom) {
                    CheckCell(xroad, yroad);
                    Upgrade();
                }
            }else if(xroad==x-1)if(map[xroad][yroad+1].type==-currentkingdom||map[xroad][yroad-1].type==-currentkingdom||map[xroad-1][yroad].type==-currentkingdom){
                    CheckCell(xroad,yroad);
                    Upgrade();
                }else if(yroad==y-1)if(map[xroad][yroad-1].type==-currentkingdom||map[xroad+1][yroad].type==-currentkingdom||map[xroad-1][yroad].type==-currentkingdom){
                        CheckCell(xroad,yroad);
                        Upgrade();
                    }

                    else if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad][yroad - 1].type == -currentkingdom ||
                             map[xroad + 1][yroad].type == -currentkingdom || map[xroad - 1][yroad].type == -currentkingdom) {
                        CheckCell(xroad, yroad);
                        Upgrade();
                    }
    for (int i = 0; i < villagecount; ++i) {
        if (villages[i].ownerId == currentkingdom) {
            if (xroad == villages[i].x) {
                if (yroad == villages[i].y + 1 || yroad == villages[i].y - 1) {
                    CheckCell(xroad, yroad);
                    Upgrade();
                }
            }
            if (yroad == villages[i].y) {
                if (xroad == villages[i].x - 1 || xroad == villages[i].x + 1) {
                    CheckCell(xroad, yroad);
                    Upgrade();
                }
            }
        }
    }

    if(map[xroad][yroad].type==dificult) currentkingdom--;
}