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
        } else if (xroad == 0) {
            if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad][yroad - 1].type == -currentkingdom ||
                map[xroad + 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        } else if (yroad == 0) {
            if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad + 1][yroad].type == -currentkingdom ||
                map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        } else if (xroad == x - 1 && yroad == y - 1) {
            if (map[xroad][yroad - 1].type == -currentkingdom || map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            }
        }else if (xroad == x - 1){
            if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad][yroad - 1].type == -currentkingdom ||
                map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();}}

        else if (yroad == y - 1) {
            if (map[xroad][yroad - 1].type == -currentkingdom || map[xroad + 1][yroad].type == -currentkingdom ||
                map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();

            }}

        else {if (map[xroad][yroad + 1].type == -currentkingdom || map[xroad][yroad - 1].type == -currentkingdom ||
                  map[xroad + 1][yroad].type == -currentkingdom || map[xroad - 1][yroad].type == -currentkingdom) {
                CheckCell(xroad, yroad);
                Upgrade();
            }}

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
        }}

    if (map[xroad][yroad].type == dificult) currentkingdom--;
}
//phase 4;

void DestroyRoads(int loserKingdom, int xRoad, int yRoad) {
    // Validate battlefield coordinates
    if (xRoad < 0 || xRoad >= x|| yRoad < 0 || yRoad >= y) {
        return;
    }

    // Array to represent directions for adjacent tiles
    int directionsx[4] = {0,0,1,-1};
    int directionsy[4]={1,-1,0,0};
    map[xRoad][yRoad].type=map[xRoad][yRoad].dificulty;
    while (1){
      int  found=0;
     // Loop through adjacent tiles and destroy roads related to the loser
       for (int i = 0; i < 4; i++) {
           int nx = xRoad + directionsx[i];
           int ny = yRoad + directionsy[i];

           // Check if the adjacent tile is within bounds
           if (nx >= 0 && nx < x && ny >= 0 && ny < y) {
               // Remove the road if it belongs to the losing kingdom
               if (map[nx][ny].type == -loserKingdom) {
                   xRoad=nx;
                   yRoad=ny;
                   found = 1;
                   map[nx][ny].type = map[nx][ny].dificulty; // Reset road state to initial (destroyed)
                   i=0;
               } else if (map[nx][ny].type == 'c'&&kingdoms[loserKingdom].x==nx&&kingdoms[loserKingdom].y==ny) {
                   return;
               }

           }
       }
       if(!found) return;
    }

 }


void BattleV(int attacker, int defender, int i, int Xroad, int Yroad) {
    if(kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount){
        villages[i] . ownerId = attacker;
        kingdoms[attacker].GoldProduction += villages[i].GoldProduction;
        kingdoms[attacker].FoodProduction += villages[i].FoodProduction;
        kingdoms[attacker].villagenumber ++;
        kingdoms[attacker].soldierCount -= kingdoms[defender].soldierCount;

        kingdoms[defender].villagenumber --;
        kingdoms[defender].FoodProduction -= villages[i].FoodProduction;
        kingdoms[defender].GoldProduction -= villages[i].GoldProduction;
        kingdoms[defender].soldierCount = 0;
        DestroyRoads(defender , Xroad ,Yroad );
    }
    else if(kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount){
        kingdoms[attacker] .soldierCount = 0;
        kingdoms[defender] .soldierCount = 0;
        DestroyRoads(attacker , Xroad , Yroad );
        DestroyRoads(defender , Xroad ,Yroad );
    }
}
void BattleR(int Xroad , int Yroad , int attacker , int defender  ){
    int loser;
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {
        loser = defender;
    }
    else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {
        loser = attacker;

    }
    else if(kingdoms[attacker] . soldierCount == kingdoms[defender].soldierCount){
        loser = attacker;
        DestroyRoads(defender,Xroad,Yroad);
    }
    DestroyRoads( loser, Xroad , Yroad );
}

void BattleK(int Xroad , int Yroad , int attacker ,int defender ){
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {

    }
    else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {

    }
    else if(kingdoms[attacker] . soldierCount == kingdoms[defender].soldierCount){
        DestroyRoads(attacker , Xroad ,Yroad );
        DestroyRoads(defender , Xroad ,Yroad );
    }
}

void CheckForBattle(int Xroad , int Yroad , int villageCount) {
    int attacker, defender;
    if (currentkingdom == 0) {
        attacker = 1;
        defender = 0;
    } else {
        attacker = 0;
        defender = 1;
    }
    int xv = -1, yv = -1;

    if (map[Xroad + 1][Yroad].type == -attacker && map[Xroad + 1][Yroad].type != -defender && Xroad != x - 1) {
        BattleR(Xroad, Yroad, attacker, defender);
    } else if (map[Xroad - 1][Yroad].type == -attacker && map[Xroad - 1][Yroad].type != -defender && Xroad != 0) {
        BattleR(Xroad, Yroad, attacker, defender);
    } else if (map[Xroad][Yroad + 1].type == -attacker && map[Xroad][Yroad + 1].type != -defender && Yroad != y - 1) {
        BattleR(Xroad, Yroad, attacker, defender);
    } else if (map[Xroad][Yroad - 1].type == -attacker && map[Xroad][Yroad - 1].type != -defender && Yroad != y - 1) {
        BattleR(Xroad, Yroad, attacker, defender);
    } else if (map[Xroad + 1][Yroad].type == 'v' && Xroad != x - 1) {
        xv = Xroad + 1, yv = Yroad;
    } else if (map[Xroad - 1][Yroad].type == 'v' && Xroad != 0) {
        xv = Xroad - 1, yv = Yroad;
    } else if (map[Xroad][Yroad - 1].type == 'v' && Yroad != 0) {
        xv = Xroad, yv = Yroad - 1;
    } else if (map[Xroad][Yroad + 1].type == 'v' && Yroad != y - 1) {
        xv = Xroad, yv = Yroad + 1;
    }

    if (xv >= 0 && yv >= 0) {
        for (int i = 0; i < villageCount; i++) {
            if (villages[i].x == xv && villages[i].y == yv && villages[i].ownerId != -1) {
                if (villages[i].ownerId != defender) {
                    BattleV(attacker, defender, i, Xroad, Yroad);
                    return;
                }
            }
        }
    }
}
