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

void DestroyRoads(int loserKingdom, int xRoad, int yRoad, int maxX, int maxY) {
    // Validate battlefield coordinates
    if (xRoad < 0 || xRoad >= maxX || yRoad < 0 || yRoad >= maxY) {
        return;
    }

    // Array to represent directions for adjacent tiles
    int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // Loop through adjacent tiles and destroy roads related to the loser
    for (int i = 0; i < 4; i++) {
        int nx = xRoad + directions[i][0];
        int ny = yRoad + directions[i][1];

        // Check if the adjacent tile is within bounds
        if (nx >= 0 && nx < maxX && ny >= 0 && ny < maxY) {
            // Remove the road if it belongs to the losing kingdom
            if (map[nx][ny].type == -loserKingdom) {
                map[nx][ny].type = map[nx][ny].dificulty; // Reset road state to initial (destroyed)
            }
        }
    }

    // Destroy the road at the battlefield itself
    if (map[xRoad][yRoad].type == -loserKingdom) {
        map[xRoad][yRoad].type = map[xRoad][yRoad].dificulty;
    }
}

void BattleV( int attacker , int defender , int i  , int Xroad , int Yroad){
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
        DestroyRoads(defender , Xroad ,Yroad , x , y);
    }
    else if(kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount){
        kingdoms[attacker] .soldierCount = 0;
        kingdoms[defender] .soldierCount = 0;
        DestroyRoads(attacker , Xroad , Yroad , x ,y);
        DestroyRoads(defender , Xroad ,Yroad , x , y);
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
        DestroyRoads(defender,Xroad,Yroad,x,y);
    }
    DestroyRoads( loser, Xroad , Yroad , x , y);
}

void BattleK(int Xroad , int Yroad , int attacker ,int defender ){
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {

    }
    else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {

    }
    else if(kingdoms[attacker] . soldierCount == kingdoms[defender].soldierCount){
        DestroyRoads(attacker , Xroad ,Yroad ,x , y);
        DestroyRoads(defender , Xroad ,Yroad ,x ,y);
    }
}

void CheckForBattle(int Xroad , int Yroad , int villageCount){
    int attacker , defender;
     int xv = -1 , yv = -1;
     if(Xroad == 0 && Yroad == 0){
         if (map[Xroad + 1][Yroad].type < 0 && map[Xroad + 1][Yroad].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad + 1][Yroad].type;
             BattleR(Xroad , Yroad ,attacker, defender);
         }
         else if (map[Xroad][Yroad + 1].type < 0 && map[Xroad][Yroad + 1].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad][Yroad + 1].type;
             BattleR(Xroad , Yroad,attacker, defender);
         }
         else if (map[Xroad + 1][Yroad].type == 'v') {
             xv = Xroad + 1, yv = Yroad;
         }
         else if (map[Xroad][Yroad + 1].type == 'v') {
             xv = Xroad, yv = Yroad + 1;
         }
     }
     else {
         if (map[Xroad + 1][Yroad].type < 0 && map[Xroad + 1][Yroad].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad + 1][Yroad].type;
             BattleR(Xroad , Yroad,attacker, defender);
         } else if (map[Xroad - 1][Yroad].type < 0 && map[Xroad - 1][Yroad].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad - 1][Yroad].type;
             BattleR(Xroad , Yroad,attacker, defender);
         } else if (map[Xroad][Yroad + 1].type < 0 && map[Xroad][Yroad + 1].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad][Yroad + 1].type;
             BattleR(Xroad , Yroad,attacker, defender);
         } else if (map[Xroad][Yroad - 1].type < 0 && map[Xroad][Yroad - 1].type != -currentkingdom) {
             attacker = -currentkingdom;
             defender = -map[Xroad][Yroad - 1].type;
             BattleR(Xroad , Yroad,attacker, defender);
         } else if (map[Xroad + 1][Yroad].type == 'v') {
             xv = Xroad + 1, yv = Yroad;
         } else if (map[Xroad - 1][Yroad].type == 'v') {
             xv = Xroad - 1, yv = Yroad;
         } else if (map[Xroad][Yroad - 1].type == 'v') {
             xv = Xroad, yv = Yroad - 1;
         } else if (map[Xroad][Yroad + 1].type == 'v') {
             xv = Xroad, yv = Yroad + 1;
         }
     }
    if( xv >= 0 && yv >= 0){
        for( int i = 0 ; i < villageCount; i++){
            if( villages[i].x == xv && villages[i] . y == yv && villages[i].ownerId != -1){
                if( villages[i] . ownerId != - currentkingdom ){
                    attacker = -currentkingdom;
                    defender = villages[i] . ownerId;
                    BattleV(attacker , defender , i , Xroad , Yroad );
                    return;
                }
            }
        }
    }
}