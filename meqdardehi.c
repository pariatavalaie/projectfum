//
// Created by ASUS on 11/30/2024.
//
#include "stdio.h"
#include "meqdardehi.h"
extern int map[17][17];
void maqar(){
    int maqarnum;
    printf("inter maqar's number please:");
    scanf("%d",&maqarnum);
    int x,y;
    for(int i = 1;i <= maqarnum;i++){
        printf("x,y %d ra vard konid",i);
        scanf("%d %d",&x,&y);
       map[x][y]='c';
    }
}
void rosta(){
    int RoostaNum;
    printf("inter Roosta's number please:");
    scanf("%d",&RoostaNum);
    int x,y;
    for (int i = 0; i < RoostaNum ; ++i) {
        printf("x,y%d ra vard konid",i+1);
        scanf("%d %d",&x,&y);
        if(map[x][y]!='c')
        map[x][y]='v';
        else i--;
    }}
void masdod(){
    int x,y;
    int MasdodNum;
    printf("tedadmasdod ra vard konid");
    scanf("%d",&MasdodNum);
    for (int i = 0; i < MasdodNum ; ++i) {
        printf("x,y%d ra vard konid",i+1);
        scanf("%d %d",&x,&y);
        if(map[x][y]!='c'&&map[x][y]!='v')
        map[x][y]='x';
    else i--;}}

    void khali(){
        for (int r = 0; r < 17; ++r) {
            for (int j = 0; j <17 ; ++j) {
                if(map[r][j]!='c'&&map[r][j]!='v'&&map[r][j]!='x'){
                map[r][j]='1';}
            }
        }
    }
