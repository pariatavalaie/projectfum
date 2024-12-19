#include <stdio.h>
#include "raylib.h"
#include "meqdardehi.h"
#include "GRID2.h"
#define IMAGE_PATH "C:/Users/Asus/CLionProjects/projectfum/map.png"
//defining map
int map[17][17] = {0};
int vProduction[20][2] = {0};

int main() {
    //receiving map Height and Width
    int x, y;
    int VillageNum;
    printf("please inter Height and Width:");
    scanf("%d %d", &x, &y);
    while(x <= 0 || y <= 0 || x > 17 || y > 17){
        printf("please inter Height and Width:");
        scanf("%d %d", &x, &y);
    }

    //marking special points (map[i][j]) on the map
    Kingdom(x, y);
    printf("inter Village's number please:");
    scanf("%d", &VillageNum);
    while (VillageNum<0){
        printf("inter Village's number please:");
        scanf("%d", &VillageNum);
    }

    Village(x, y,VillageNum);
    ForceClosed(x, y);

    // setting difficulty for empty map[i][j]
    Empty(x, y);

    InitWindow(0, 0, "MAP");

    // defining each  special point texture
    Texture2D Background = LoadTexture(IMAGE_PATH);
    Texture2D Kingdom = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/kingdom.png");
    Texture2D Village = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/1.png");
    Texture2D ForceClosed = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/Water_ruins2.png");

    // Set the target frame rate to 60 frames per second for smooth rendering
    SetTargetFPS(60);

    // drawing Map
    while (!WindowShouldClose()) {
        Vector2 mouseposition=GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(Background, 0, 0, WHITE);
        grid(x, y);
        float offsetX = (WINDOW_WIDTH - x * 68) / 2.0;
        float offsetY = (WINDOW_HEIGHT - y * 68) / 2.0;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; ++j) {
                Rectangle cellrect = {offsetX + j * 68, offsetY + i * 68, 68, 68
                };
                if (map[i][j] == 'c') {
                    DrawTexture(Kingdom, offsetX + j * 68, offsetY + i * 68, WHITE);
                } else if (map[i][j] == 'v') {
                    DrawTexture(Village, offsetX + j * 68, offsetY + i * 68, WHITE);

                } else if (map[i][j] == 'x') {
                    DrawTexture(ForceClosed, offsetX + j * 68, offsetY + i * 68, WHITE);
                } else {
                    char text = map[i][j];
                    DrawText(TextFormat("%d", text), offsetX + j * 68, offsetY + i * 68, 24, RED);
                }
                if (CheckCollisionPointRec(mouseposition, cellrect)) {
                    char infotext[50];
                    DrawRectangle(cellrect.x, cellrect.y, 68, 68, GRAY);
                    if (map[i][j] == 'v') {
                        sprintf(infotext, "gold:%d\nfood:%d", vProduction[i][1], vProduction[i][2]);
                        DrawText(infotext, cellrect.x, cellrect.y, 10, BLACK);
                    }
                }


            }
        }
        int showguide;
        if(IsKeyPressed(KEY_SPACE)) showguide=!showguide;
        if(!showguide){
            DrawRectangle(0,0,300,300,BLUE);
            DrawText("GAME GUIDE",50,20,20,BLACK);
        }int xroad,yroad;
        if(IsKeyPressed(KEY_ENTER)){
             yroad=((mouseposition.x-offsetX)/68);
         xroad=((mouseposition.y-offsetY))/68;}
        int posx=offsetX+yroad*68;
        int posy=offsetY+xroad*68;
       DrawRectangle(posx,posy,68,68,RED);





        EndDrawing();
    }
    CloseWindow();
    return 0;
}

