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
    int cellDifficulty ;
    int z,k;
    if(currentkingdom==0){z=0;
        k=1;
        cellDifficulty= map[xroad][yroad].remain0;}
    else {z=1;
        k=0;
        cellDifficulty= map[xroad][yroad].remain1;}

    if (cellDifficulty > kingdoms[z].WorkersCount&&map[xroad][yroad].type!=-k) {
        if(currentkingdom==0)
        map[xroad][yroad].remain0 = cellDifficulty - kingdoms[z].WorkersCount;
        else if(currentkingdom==1){
            map[xroad][yroad].remain1 = cellDifficulty - kingdoms[z].WorkersCount;
        }
    }
    else if(map[xroad][yroad].type!=-k){
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
    int dificult=-1;
    if(currentkingdom==0) dificult = map[xroad][yroad].remain0;
    else if(currentkingdom==1) dificult=map[xroad][yroad].remain1;
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

    if (map[xroad][yroad].remain0 == dificult&&currentkingdom==0&&map[xroad][yroad].type!=0) currentkingdom--;
    else if (map[xroad][yroad].remain1 == dificult&&currentkingdom==1&&map[xroad][yroad].type!=-1) currentkingdom--;
}
//phase 4;
void destroy(int loserkingdom,int xr,int yr){
    if(map[xr][yr].type==-loserkingdom){if (loserkingdom == 0) map[xr][yr].remain0 = map[xr][yr].dificulty;
        else map[xr][yr].remain1 = map[xr][yr].dificulty;
     map[xr][yr].type=map[xr][yr].dificulty;}

    if(map[xr-1][yr].type==-loserkingdom&&xr!=0){if (loserkingdom == 0) map[xr-1][yr].remain0 = map[xr-1][yr].dificulty;
        else map[xr-1][yr].remain1 = map[xr-1][yr].dificulty;
        map[xr-1][yr].type=map[xr-1][yr].dificulty;}

    if(map[xr+1][yr].type==-loserkingdom&&xr!=x-1){if (loserkingdom == 0) map[xr+1][yr].remain0 = map[xr+1][yr].dificulty;
        else map[xr+1][yr].remain1 = map[xr+1][yr].dificulty;
        map[xr+1][yr].type=map[xr+1][yr].dificulty;}

    if(map[xr][yr-1].type==-loserkingdom&&yr!=0){if (loserkingdom == 0) map[xr][yr-1].remain0 = map[xr][yr-1].dificulty;
        else map[xr][yr-1].remain1 = map[xr][yr-1].dificulty;
        map[xr][yr-1].type=map[xr][yr-1].dificulty;}

    if(map[xr][yr+1].type==-loserkingdom&&yr!=y-1){if (loserkingdom == 0) map[xr][yr+1].remain0 = map[xr][yr+1].dificulty;
        else map[xr][yr+1].remain1 = map[xr][yr+1].dificulty;
        map[xr][yr+1].type=map[xr][yr].dificulty;}
}

void DestroyRoads(int loserKingdom, int xRoad, int yRoad,int villagecount) {
 int xk=kingdoms[loserKingdom].x;
 int yk=kingdoms[loserKingdom].y;
    // Validate battlefield coordinates
    if (xRoad < 0 || xRoad >= x|| yRoad < 0 || yRoad >= y) {
        return;
    }

    // Array to represent directions for adjacent tiles
    int directionsx[4] = {0,0,1,-1};
    int directionsy[4]={1,-1,0,0};
   if(map[xRoad][yRoad].type==-loserKingdom) {
       if (loserKingdom == 0) map[xRoad][yRoad].remain0 = map[xRoad][yRoad].dificulty;
       else map[xRoad][yRoad].remain1 = map[xRoad][yRoad].dificulty;
       map[xRoad][yRoad].type=map[xRoad][yRoad].dificulty;}

   while (1){
      int  found=0;
     // Loop through adjacent tiles and destroy roads related to the loser
       for (int i = 0; i < 4; i++) {
           int nx = xk + directionsx[i];
           int ny = yk+ directionsy[i];

           // Check if the adjacent tile is within bounds
           if (nx >= 0 && nx < x && ny >= 0 && ny < y) {
               // Remove the road if it belongs to the losing kingdom
               for (int j = 0; j <villagecount ; ++j) {
                   if(villages[j].x==nx&&villages[j].y==ny&&villages[j].ownerId==loserKingdom) {
                       villages[i].ownerId=-1;
                   }
               }
               if (map[nx][ny].type == -loserKingdom) {
                   xk=nx;
                   yk=ny;
                   found = 1;
                  if(loserKingdom==0) map[nx][ny].remain0= map[nx][ny].dificulty;// Reset road state to initial (destroyed)
                  else map[nx][ny].remain1 = map[nx][ny].dificulty;
                  map[nx][ny].type=map[xRoad][yRoad].dificulty;
                   i=0;
               }

               else  for (int j = 0; j <villagecount ; ++j) {
                     if(villages[j].x==nx&&villages[j].y==ny&&villages[j].ownerId==loserKingdom) {
                         if(map[nx-1][ny].type==-loserKingdom&&nx!=0) nx=nx-1;
                         if(map[nx+1][ny].type==-loserKingdom&&nx!=x-1) nx=nx+1;
                         if(map[nx][ny+1].type==-loserKingdom&&ny!=y-1) ny=ny+1;
                         if(map[nx][ny-1].type==-loserKingdom&&ny!=0) ny=ny-1;
                         found = 1;
                         i=0;
                         villages[i].ownerId=-1;
                     }
                   }


               if () {
                   return;}

           }
       }
       if(!found) return;
    }

 }


void BattleV( int attacker , int defender , int i  , int Xroad , int Yroad,int villagecount){
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
        DestroyRoads(defender , Xroad ,Yroad,villagecount);
    }
    else if(kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount){
        kingdoms[attacker] .soldierCount = 0;
        kingdoms[defender] .soldierCount = 0;
        DestroyRoads(attacker , Xroad , Yroad,villagecount );
        DestroyRoads(defender , Xroad ,Yroad,villagecount );
    }
}
void BattleR(int Xroad , int Yroad , int attacker , int defender,int villagecount  ){
    int loser=-1;
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {
        loser = defender;
    }
    else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {
        loser = attacker;

    }
    else if(kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount){
        loser = attacker;
        DestroyRoads(defender,Xroad,Yroad,villagecount);
        map[Xroad][Yroad].type=-loser;
    }
    DestroyRoads( loser, Xroad , Yroad,villagecount );
}

void BattleK(int Xroad , int Yroad , int attacker ,int defender,int villagecount ){
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {

    }
    else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {

    }
    else if(kingdoms[attacker] . soldierCount == kingdoms[defender].soldierCount){
        DestroyRoads(attacker , Xroad ,Yroad,villagecount);
        DestroyRoads(defender , Xroad ,Yroad,villagecount );
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
     int xv = -1 , yv = -1;

         if (map[Xroad + 1][Yroad].type ==-attacker && map[Xroad + 1][Yroad].type != -defender &&Xroad!=x-1) {
             BattleR(Xroad , Yroad,attacker, defender,villageCount);
         } else if (map[Xroad - 1][Yroad].type==-attacker && map[Xroad - 1][Yroad].type != -defender&&Xroad!=0) {
             BattleR(Xroad , Yroad,attacker, defender,villageCount);
         } else if (map[Xroad][Yroad + 1].type==-attacker&& map[Xroad][Yroad + 1].type != -defender&&Yroad!=y-1) {
             BattleR(Xroad , Yroad,attacker, defender,villageCount);
         } else if (map[Xroad][Yroad - 1].type==-attacker && map[Xroad][Yroad - 1].type != -defender&&Yroad!=y-1) {
             BattleR(Xroad , Yroad,attacker, defender,villageCount);
         } else if (map[Xroad + 1][Yroad].type == 'v'&&Xroad!=x-1) {
             xv = Xroad + 1, yv = Yroad;
         } else if (map[Xroad - 1][Yroad].type == 'v'&&Xroad!=0) {
             xv = Xroad - 1, yv = Yroad;
         } else if (map[Xroad][Yroad - 1].type == 'v'&&Yroad!=0) {
             xv = Xroad, yv = Yroad - 1;
         } else if (map[Xroad][Yroad + 1].type == 'v'&&Yroad!=y-1) {
             xv = Xroad, yv = Yroad + 1;
         }

    if( xv >= 0 && yv >= 0){
        for( int i = 0 ; i < villageCount; i++){
            if( villages[i].x == xv && villages[i] . y == yv && villages[i].ownerId != -1){
                if( villages[i] . ownerId != defender){
                    BattleV(attacker , defender , i , Xroad , Yroad ,villageCount);
                    return;
                }
            }
        }
    }
}