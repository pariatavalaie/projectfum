#include <stdio.h>
#include "raylib.h"
#include "meqdardehi.h"
#include "GRID2.h"
#define IMAGE_PATH "C:/Users/Asus/CLionProjects/project/img.png"
//defining map
int map[17][17] = {0};

int main() {
    //receiving map Hight and Width
    int x, y;
    printf("please inter Height and Width:");
    scanf("%d %d", &x, &y);
    Kingdom(x, y);
    Village(x, y);
    ForceClosed(x, y);
    Empty(x, y);


    InitWindow(0, 0, "MAP");
    Texture2D Background = LoadTexture(IMAGE_PATH);
    Texture2D Kingdom = LoadTexture("C:/Users/Asus/CLionProjects/project/222   .png");
    Texture2D Village = LoadTexture("C:/Users/Asus/CLionProjects/project/vilage .png");
    Texture2D ForceClosed = LoadTexture("C:/Users/Asus/CLionProjects/project/Water_ruins2.png");
    SetTargetFPS(60);;
    while (!WindowShouldClose()) {

        BeginDrawing();
        DrawTexture(Background, 0, 0, WHITE);
        grid(x, y);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; ++j) {
                float offsetX = (WINDOW_WIDTH - x * 68) / 2.0;
                float offsetY = (WINDOW_HEIGHT - y * 68) / 2.0;
                if (map[i][j] == 'c') {
                    DrawTexture(Kingdom, offsetX + i * 68, offsetY + j * 68, WHITE);
                } else if (map[i][j] == 'v') {
                    DrawTexture(Village, offsetX + i * 68, offsetY + j * 68, WHITE);
                } else if (map[i][j] == 'x') {
                    DrawTexture(ForceClosed, offsetX + i * 68, offsetY + j * 68, WHITE);
                } else {
                    char *text = map[i][j];
                    DrawText(&text, offsetX + i * 68, offsetY + j * 68, 24, RED);
                }


            }


        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

