//
// Created by ASUS on 11/30/2024.
//
#include "stdio.h"
#include "meqdardehi.h"
extern int map[17][17];
void maqar(int k,int j){
    int maqarnum;
    int x,y;
    printf("inter maqar's number please:");
    scanf("%d",&maqarnum);
    for(int i = 1;i <= maqarnum;i++){
        printf("x,y %d ra vard konid",i);
        scanf("%d %d",&x,&y);
        if(k<x||j<y) i--;
       else map[x][y]='c';
    }
}
void rosta(int k,int j){
    int RoostaNum;
    printf("inter Roosta's number please:");
    scanf("%d",&RoostaNum);
    int x,y;
    for (int i = 0; i < RoostaNum ; ++i) {
        printf("x,y%d ra vard konid",i+1);
        scanf("%d %d",&x,&y);
        if(map[x][y]!='c'&& k>x && j>y)
        map[x][y]='v';
        else i--;
    }}
void masdod(int k,int j){
    int x,y;
    int MasdodNum;
    printf("tedadmasdod ra vard konid");
    scanf("%d",&MasdodNum);
    for (int i = 0; i < MasdodNum ; ++i) {
        printf("x,y%d ra vard konid",i+1);
        scanf("%d %d",&x,&y);
        if(map[x][y]!='c'&&map[x][y]!='v'&&k>x&&j>y)
        map[x][y]='x';
    else i--;}}

    void khali(int k , int i){
        for (int r = 0; r < 17; ++r) {
            for (int j = 0; j <17 ; ++j) {
                if(map[r][j]!='c'&&map[r][j]!='v'&&map[r][j]!='x'){
                map[r][j]='1';}
            }
        }
    }
