//
// Created by ASUS on 11/30/2024.
//
#include "stdio.h"
#include "meqdardehi.h"
#include "raylib.h"
#include "type.h"

//defining map as an extern int to be known in all functions
extern Map map[17][17];

//receiving number of kingdoms and each one's location
void Kingdoms(int k, int j, struct Kingdom kingdoms[], int *kingdomCount) {
    int KingdomNum;
    printf("Please enter the number of Kingdoms: ");
    scanf("%d", &KingdomNum);

    while (KingdomNum < 0 || KingdomNum > 5) {
        printf("Please enter a valid number of Kingdoms (1-4): ");
        scanf("%d", &KingdomNum);
    }

    *kingdomCount = KingdomNum;

    for (int i = 0; i < KingdomNum; i++) {
        int x, y;
        printf("Please enter x, y for Kingdom %d: ", i + 1);
        scanf("%d %d", &x, &y);

        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y].type != 10) i--;

        else {
            kingdoms[i].id = i + 1;
            kingdoms[i].x = x;
            kingdoms[i].y = y;
            kingdoms[i].WorkersCount = 1;
            kingdoms[i].soldierCount = 1;
            kingdoms[i].GoldProduction = 1;
            kingdoms[i].FoodProduction = 0;
            kingdoms[i].Serve = 0;
            kingdoms[i].Gold = 0;

            map[x][y].type = 'c';
        }
    }
}

void Villages(int k, int j, struct Village villages[], int *villageCount) {
    int VillageNum;
    printf("Please enter the number of Villages: ");
    scanf("%d", &VillageNum);

    while (VillageNum < 0 || VillageNum > 20) {
        printf("Please enter a valid number of Villages: ");
        scanf("%d", &VillageNum);
    }

    *villageCount = VillageNum;

    for (int i = 0; i < VillageNum; i++) {
        int x, y;
        printf("Please enter x, y for Village %d: ", i + 1);
        scanf("%d %d", &x, &y);

        // Validate the position
        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y].type != 10) i--;
        else {
            villages[i].VillageId = i + 1;
            villages[i].x = x;
            villages[i].y = y;
            villages[i].ownerId = -1;

            printf("Please enter Gold production for Village %d: ", i + 1);
            scanf("%d", &villages[i].GoldProduction);

            printf("Please enter Food production for Village %d: ", i + 1);
            scanf("%d", &villages[i].FoodProduction);

            map[x][y].type = 'v';

        }
    }
}


//receiving number of ForceClosed and each one's location
void ForceClosed(int k, int j) {
    int x, y;
    //using blocked instead of ForceClosed to shorten
    int BlockedNum;
    printf("Please enter the number of ForceClosed cells: ");
    scanf("%d", &BlockedNum);

    while (BlockedNum < 0) {
        printf("Please enter a valid number of ForceClosed cells: ");
        scanf("%d", &BlockedNum);
    }

    for (int i = 0; i < BlockedNum; i++) {
        int x, y;
        printf("Please enter x, y for ForceClosed cells %d: ", i + 1);
        scanf("%d %d", &x, &y);


        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y].type != 10) {
            i--;
        } else {
            map[x][y].type = 'x';
        }
    }
}


void Empty(int k, int i) {
    for (int r = 0; r < 17; ++r) {
        for (int j = 0; j < 17; ++j) {
            //making sure that the MAP[x][y] is empty
            if (map[r][j].type!= 'c' && map[r][j].type != 'v' && map[r][j] .type!= 'x') {
                //setting difficulty
                map[r][j].type = GetRandomValue(1, 5);
                map[r][j].dificulty=map[r][j].type;
            }
        }
    }
}
void SuggestedRoad(int xq, int yq,int i,int k,int j) {
    int x = xq, y = yq;
    int endy = villages[i].y, endx = villages[i].x;
    int xv=villages[i].x,yv=villages[i].y;
    while (x != xv || y != yv) {
        if (map[x][y].type!= 'c' && map[x][y].type != 'x' && map[x][y].type != 'v') map[x][y].road = i;

        if (y < yv && map[x][y + 1].type != 'x' && map[x][y+1].type != 'c') {
            y++;
        }
        else if (y > yv && map[x][y - 1] .type!= 'x' && map[x][y - 1] .type!= 'c') {
            y--;
        }
        else if (x < xv && map[x + 1][y] .type!= 'x' && map[x + 1][y].type != 'c') {
            x++;
        }
        else if (x > xv && map[x - 1][y].type != 'x' && map[x - 1][y].type != 'c') {
            x--;

        }else if ((y == yv && x > xv &&y==j-1) && (map[x - 1][y].type == 'x'|| map [x- 1][y].type == 'c')) {
            y--;
            yv--;
        }
        else if ((y == yv && x > xv ) && (map[x - 1][y].type == 'x'|| map [x- 1][y].type == 'c')) {
            y++;
            yv++;
        } else if ((y == yv && x < xv&&y==0) && (map[x + 1][y].type == 'x' || map[x + 1][y].type == 'c')) {
            y++;
            yv++;
        }
        else if ((y == yv && x < xv) && (map[x + 1][y].type == 'x' || map[x + 1][y].type == 'c')) {
            y--;
            yv--;
        }else if ((x == xv && y < yv&&x==k-1) &&( map [x][y+1].type == 'x' || map[x][y+1].type == 'c')){
            x--;
            xv--;
        }
        else if ((x == xv && y < yv) &&( map [x][y+1].type == 'x' || map[x][y+1].type == 'c')){
            x++;
            xv++;
        }else if ((x == xv && y > yv&&x==0) &&( map [x][y-1].type == 'x' || map[x][y-1].type == 'c')){
            x++;
            xv++;
        }
        else if ((x == xv && y > yv) &&( map [x][y-1].type == 'x' || map[x][y-1].type == 'c')){
            x--;
            xv--;
        }
        else{
            break;
        }
    }
    if (endy > yv) {
        map[x][y].road = i;
    }
    else if (endy < yv) {
        map[x][y].road = i;
    }
    if(endx > xv){
        map[x][y].road = i;
    }
    else if( endx < xv){
        map[x][y].road = i;
    }
}
