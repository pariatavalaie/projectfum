//
// Created by ASUS on 11/30/2024.
//
#include "stdio.h"
#include "meqdardehi.h"
#include "raylib.h"

//defining map as an extern int to be known in all functions
extern int map[17][17];
extern int vProduction[20][2];
extern int KingdomPos[5][2];

//receiving number of kingdoms and each one's location
void Kingdom(int k, int j) {
    int KingdomNum;
    int x, y;
    printf("please inter Kingdom's number:");
    scanf("%d", &KingdomNum);
    KingdomPos[0][0] = KingdomNum;
    while (KingdomNum < 0 || KingdomNum > 4) {
        printf("please inter Kingdom's number:");
        scanf("%d", &KingdomNum);
        KingdomPos[0][0] = KingdomNum;
    }

    for (int i = 1; i <= KingdomNum; i++) {
        printf("please inter x , y Kingdom %d:", i);
        scanf("%d %d", &x, &y);
        KingdomPos[i][0] = x;
        KingdomPos[i][1] = y;

        // making sure that inputs are standard
        if (k <= x || j <= y || map[i][j] == 'c' || x < 0 || y < 0) i--;

            // placing the symbol c for each Kingdom in the map
        else map[x][y] = 'c';
    }
}

//receiving each village productions
void VillageProduction(int k, int array[20][2]) {
    for (int j = 0; j < 2; j++) {
        if (j == 0) {
            printf("please inter Village Gold production: ");
            scanf("%d", &array[k][j]);
            if (array[k][j] < 0) j--;
        }
        if (j == 1) {
            printf("please inter Vilage Food production:");
            scanf("%d", &array[k][j]);
            if (array[k][j] < 0) j--;
        }
    }
}

//receiving number of Village and each one's location
void Village(int k, int j, int VillageNum) {
    int x, y;
    for (int i = 0; i < VillageNum; ++i) {
        printf("please inter x , y Village %d : ", i + 1);
        scanf("%d %d", &x, &y);

        // making sure that inputs are standard and MAP[x][y] is empty
        if (map[x][y] != 'c' && k > x && j > y && map[x][y] != 'v' && x >= 0 && y >= 0) {

            // placing the symbol v for each Village in the map
            map[x][y] = 'v';
            //each village gold and food productions
            VillageProduction(i, vProduction);
        }
            // if the input is not standard do the if loop again
        else i--;
    }
}


//receiving number of ForceClosed and each one's location
void ForceClosed(int k, int j) {
    int x, y;
    //using blocked instead of ForceClosed to shorten
    int BlockedNum;
    printf("please inter ForceCloseds number:");
    scanf("%d", &BlockedNum);
    while (BlockedNum < 0) {
        printf("please inter ForceCloseds number:");
        scanf("%d", &BlockedNum);
    }

    for (int i = 0; i < BlockedNum; ++i) {
        printf("please inter x , y ForceClosed %d: ", i + 1);
        scanf("%d %d", &x, &y);

        // making sure that inputs are standard and MAP[x][y] is empty
        if (map[x][y] != 'c' && map[x][y] != 'v' && k > x && j > y && map[x][y] != 'x' && x >= 0 && y >= 0)

            // placing the symbol x for each ForceClosed in the map
            map[x][y] = 'x';

            // if the input is not standard do the if loop again
        else i--;
    }
}

//setting empty map[i][j] difficulty
void Empty(int k, int i) {
    for (int r = 0; r < 17; ++r) {
        for (int j = 0; j < 17; ++j) {
            //making sure that the MAP[x][y] is empty
            if (map[r][j] != 'c' && map[r][j] != 'v' && map[r][j] != 'x') {
                //setting difficulty
                map[r][j] = GetRandomValue(1, 9);
            }
        }
    }
}

void Road(int xq, int yq, int xv, int yv,int i,int j) {
    int x = xq, y = yq;
    int endy = yv, endx = xv;
    while (x != xv || y != yv) {
        if (map[x][y] != 'c' && map[x][y] != 'x' && map[x][y] != 'v') map[x][y] = 'r';

        if (y < yv && map[x][y + 1] != 'x' && map[x][y+1] != 'c') {
            y++;
        }
        else if (y > yv && map[x][y - 1] != 'x' && map[x][y - 1] != 'c') {
            y--;
        }
        else if (x < xv && map[x + 1][y] != 'x' && map[x + 1][y] != 'c') {
            x++;
        }
        else if (x > xv && map[x - 1][y] != 'x' && map[x - 1][y] != 'c') {
            x--;

        }
        else  if ((y == yv && x > xv &&y==j-1) && (map[x - 1][y] == 'x'|| map [x- 1][y] == 'c')){
            y--;
            yv--;
        }
        else if ((y == yv && x > xv ) && (map[x - 1][y] == 'x'|| map [x- 1][y] == 'c')) {
            y++;
            yv++;
        } else if ((y == yv && x < xv&&y==0) && (map[x + 1][y] == 'x' || map[x + 1][y] == 'c')){
          y++;
          yv++;
        }
        else if ((y == yv && x < xv) && (map[x + 1][y] == 'x' || map[x + 1][y] == 'c')) {
            y--;
            yv--;
        } else if ((x == xv && y < yv && x==i-1) &&( map [x][y+1] == 'x' || map[x][y+1] == 'c')){
            x--;
            xv--;
        }
        else if ((x == xv && y < yv) &&( map [x][y+1] == 'x' || map[x][y+1] == 'c')){
            x++;
            xv++;
        } else if ((x == xv && y > yv&&x==0) &&( map [x][y-1] == 'x' || map[x][y-1] == 'c')){
            x++;
            xv++;
        }
        else if ((x == xv && y > yv) &&( map [x][y-1] == 'x' || map[x][y-1] == 'c')){
            x--;
            xv--;
        }
        else{
            break;
        }
    }
    if (endy > yv) {
        map[x][y] = 'r';
    }
    else if (endy < yv) {
        map[x][y] = 'r';
    }
    if(endx > xv){
        map[x][y] = 'r';
    }
    else if( endx < xv){
        map[x][y] = 'r';
    }
}

