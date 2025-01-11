//
// Created by Asus on 12/27/2024.
//
#include "raylib.h"
#include "GRID2.h"
#include "meqdardehi.h"
#include "type.h"
#include "gameUpdate.h"
#include "stdbool.h"

extern int x, y;

void workers() {
    if (kingdoms[currentkingdom].Serve >= 3) {
        kingdoms[currentkingdom].WorkersCount++;
        kingdoms[currentkingdom].Serve -= 3;
        Upgrade();
    } else currentkingdom--;
}

void Upgrade() {
    kingdoms[currentkingdom].Gold += kingdoms[currentkingdom].GoldProduction;
    kingdoms[currentkingdom].Serve += kingdoms[currentkingdom].FoodProduction;
}

void Food() {
    if (kingdoms[currentkingdom].Gold >= 1) {
        kingdoms[currentkingdom].Serve++;
        kingdoms[currentkingdom].Gold--;
        Upgrade();
    } else currentkingdom--;
}

void soldier() {
    if (kingdoms[currentkingdom].Gold >= 2) {
        kingdoms[currentkingdom].soldierCount++;
        kingdoms[currentkingdom].Gold -= 2;
        Upgrade();
    } else currentkingdom--;
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
            } else if (i == 0 && j == y - 1) {
                if (map[i][j - 1].type == -currentkingdom || map[i + 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (i == x - 1 && j == 0) {
                if (map[i - 1][j].type == -currentkingdom || map[i][j + 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (i == x - 1 && j == y - 1) {
                if (map[i][j - 1].type == -currentkingdom || map[i - 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (i == 0) {
                if (map[i][j - 1].type == -currentkingdom || map[i][j + 1].type == -currentkingdom ||
                    map[i + 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (i == x - 1) {
                if (map[i][j - 1].type == -currentkingdom || map[i][j + 1].type == -currentkingdom ||
                    map[i - 1][j].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (j == 0) {
                if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                    map[i][j + 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (j == y - 1) {
                if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                    map[i][j - 1].type == -currentkingdom) {
                    villages[k].ownerId = currentkingdom;
                    kingdoms[currentkingdom].villagenumber++;
                    kingdoms[currentkingdom].FoodProduction += villages[k].FoodProduction;
                    kingdoms[currentkingdom].GoldProduction += villages[k].GoldProduction;
                }
            } else if (map[i - 1][j].type == -currentkingdom || map[i + 1][j].type == -currentkingdom ||
                       map[i][j - 1].type == -currentkingdom || map[i][j + 1].type == -currentkingdom) {
                villages[k].ownerId = currentkingdom;
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
void DestroyRoads(int loserKingdom, int startX, int startY, int villagecount) {
    if (startX < 0 || startX >= x || startY < 0 || startY >= y) {
        return;
    }

    bool visited[17][17] = {false};
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

#define QMAX 289
    int qx[QMAX], qy[QMAX];
    int front = 0, back = 0;

    // Only start removing roads if the starting cell is a road
    if (map[startX][startY].type == -loserKingdom) {
        map[startX][startY].type = map[startX][startY].dificulty;
    }
    visited[startX][startY] = true;

    qx[back] = startX;
    qy[back] = startY;
    back++;

    while (front < back) {
        int cx = qx[front];
        int cy = qy[front];
        front++;

        int roadNeighborCount = 0;

        // Count connected road neighbors
        for (int i = 0; i < 4; i++) {
            int nx = cx + dirs[i][0];
            int ny = cy + dirs[i][1];

            if (nx < 0 || nx >= x || ny < 0 || ny >= y || visited[nx][ny]) {
                continue;
            }

            if (map[nx][ny].type == -loserKingdom) {
                roadNeighborCount++;
            }
        }

        // If current tile is a road and is a crossroads (more than 1 neighbor)
        if (roadNeighborCount > 1) {
            // Mark as visited but don't delete
            visited[cx][cy] = true;
            continue;
        }

        // Process each neighbor
        for (int i = 0; i < 4; i++) {
            int nx = cx + dirs[i][0];
            int ny = cy + dirs[i][1];

            if (nx < 0 || nx >= x || ny < 0 || ny >= y || visited[nx][ny]) {
                continue;
            }

            // If it's a road of the loserKingdom
            if (map[nx][ny].type == -loserKingdom) {
                int neighborCount = 0;

                // Check if this neighbor is a crossroads
                for (int j = 0; j < 4; j++) {
                    int nnx = nx + dirs[j][0];
                    int nny = ny + dirs[j][1];
                    if (nnx >= 0 && nnx < x && nny >= 0 && nny < y &&
                        map[nnx][nny].type == -loserKingdom) {
                        neighborCount++;
                    }
                }

                // Skip deleting crossroads
                if (neighborCount > 1) {
                    visited[nx][ny] = true;
                    continue;
                }

                // Otherwise, delete the road
                map[nx][ny].type = map[nx][ny].dificulty;
                visited[nx][ny] = true;
                qx[back] = nx;
                qy[back] = ny;
                back++;
            } else if (map[nx][ny].type == 'v') {
                for (int v = 0; v < villagecount; v++) {
                    if (villages[v].x == nx && villages[v].y == ny && villages[v].ownerId == loserKingdom) {
                        villages[v].ownerId = -1;
                        visited[nx][ny] = true;
                        qx[back] = nx;
                        qy[back] = ny;
                        back++;
                        break;
                    }
                }
            } else if (map[nx][ny].type == 'c' &&
                       kingdoms[loserKingdom].x == nx &&
                       kingdoms[loserKingdom].y == ny) {
                visited[nx][ny] = true;
                continue;
            }
        }
    }
}

void BattleR(int Xroad, int Yroad, int attacker, int defender, int villagecount) {
    int loser = -1;
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {
        loser = defender;
        kingdoms[defender].soldierCount = 0;
        kingdoms[attacker].soldierCount -= kingdoms[defender].soldierCount;
        map[Xroad][Yroad].type = -attacker;
    } else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {
        loser = attacker;
        kingdoms[attacker].soldierCount = 0;
        kingdoms[defender].soldierCount -= kingdoms[attacker].soldierCount;
    } else if (kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount) {
        loser = attacker;  // In case of equal soldiers, we can assume attacker loses
        DestroyRoads(defender, Xroad, Yroad, villagecount);  // Remove roads for defender
        map[Xroad][Yroad].type = -attacker;  // Mark the road with the attacker's kingdom
        kingdoms[attacker].soldierCount = 0;
        kingdoms[defender].soldierCount = 0;
    }

    DestroyRoads(loser, Xroad, Yroad, villagecount); // Remove roads for the loser
}

void BattleV(int attacker, int defender, int i, int Xroad, int Yroad, int villagecount) {
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {
        villages[i].ownerId = attacker;
        kingdoms[attacker].GoldProduction += villages[i].GoldProduction;
        kingdoms[attacker].FoodProduction += villages[i].FoodProduction;
        kingdoms[attacker].villagenumber++;
        kingdoms[attacker].soldierCount -= kingdoms[defender].soldierCount;
        map[Xroad][Yroad].type = -attacker;

        kingdoms[defender].villagenumber--;
        kingdoms[defender].FoodProduction -= villages[i].FoodProduction;
        kingdoms[defender].GoldProduction -= villages[i].GoldProduction;
        kingdoms[defender].soldierCount = 0;
        DestroyRoads(defender, Xroad, Yroad, villagecount);
    } else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {
        DestroyRoads(attacker, Xroad, Yroad, villagecount);
        kingdoms[attacker].soldierCount = 0;
        kingdoms[defender].soldierCount -= kingdoms[attacker].soldierCount;
    } else if (kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount) {
        kingdoms[attacker].soldierCount = 0;
        kingdoms[defender].soldierCount = 0;
        DestroyRoads(attacker, Xroad, Yroad, villagecount);
        DestroyRoads(defender, Xroad, Yroad, villagecount);
    }
}

void BattleK(int Xroad, int Yroad, int attacker, int defender, int villagecount) {
    if (kingdoms[attacker].soldierCount > kingdoms[defender].soldierCount) {
        winner = attacker;
    } else if (kingdoms[attacker].soldierCount < kingdoms[defender].soldierCount) {
        winner = defender;
    } else if (kingdoms[attacker].soldierCount == kingdoms[defender].soldierCount) {
        kingdoms[attacker].soldierCount = 0;
        kingdoms[defender].soldierCount = 0;
        DestroyRoads(attacker, Xroad, Yroad, villagecount);
    }
}
void CheckForBattle(int Xroad, int Yroad, int villageCount) {
    int attacker, defender;
    if (currentkingdom == 0) {
        attacker = 1;
        defender = 0;
    } else {
        attacker = 0;
        defender = 1;
    }
    int xv = -1, yv = -1;
    int xk = -1, yk = -1;


    if (Xroad != x - 1) {
        if (map[Xroad + 1][Yroad].type == -attacker && map[Xroad + 1][Yroad].type != -defender) {
            BattleR(Xroad, Yroad, attacker, defender, villageCount);
            return;
        } else if (map[Xroad + 1][Yroad].type == 'v') {
            xv = Xroad + 1;
            yv = Yroad;
        } else if (map[Xroad + 1][Yroad].type == 'c') {
            xk = Xroad + 1;
            yk = Yroad;
        }
    }

    if (Xroad != 0) {
        if (map[Xroad - 1][Yroad].type == -attacker && map[Xroad - 1][Yroad].type != -defender) {
            BattleR(Xroad, Yroad, attacker, defender, villageCount);
            return;
        } else if (map[Xroad - 1][Yroad].type == 'v') {
            xv = Xroad - 1;
            yv = Yroad;
        } else if (map[Xroad - 1][Yroad].type == 'c') {
            xk = Xroad - 1;
            yk = Yroad;
        }
    }

    if (Yroad != y - 1) {
        if (map[Xroad][Yroad + 1].type == -attacker && map[Xroad][Yroad + 1].type != -defender) {
            BattleR(Xroad, Yroad, attacker, defender, villageCount);
            return;
        } else if (map[Xroad][Yroad + 1].type == 'v') {
            xv = Xroad;
            yv = Yroad + 1;
        } else if (map[Xroad][Yroad + 1].type == 'c') {
            xk = Xroad;
            yk = Yroad + 1;
        }
    }

    if (Yroad != 0) {
        if (map[Xroad][Yroad - 1].type == -attacker && map[Xroad][Yroad - 1].type != -defender) {
            BattleR(Xroad, Yroad, attacker, defender, villageCount);
            return;
        } else if (map[Xroad][Yroad - 1].type == 'v') {
            xv = Xroad;
            yv = Yroad - 1;
        } else if (map[Xroad][Yroad - 1].type == 'c') {
            xk = Xroad;
            yk = Yroad - 1;
        }
    }

    if (xk >= 0 && yk >= 0) {
        BattleK(Xroad, Yroad, attacker, defender, villageCount);
        return;
    }

    if (xv >= 0 && yv >= 0) {
        for (int i = 0; i < villageCount; i++) {
            if (villages[i].x == xv && villages[i].y == yv && villages[i].ownerId != -1) {
                if (villages[i].ownerId != defender) {
                    BattleV(attacker, defender, i, Xroad, Yroad, villageCount);
                    return;
                }
            }
        }
    }
}
