#include <stdio.h>
#include "raylib.h"
#include "meqdardehi.h"
#include "GRID2.h"

#define IMAGE_PATH "C:/Users/Asus/CLionProjects/projectfum/map.png"
//defining map
int map[17][17] = {0};

int main() {
    //receiving map Height and Width
    int x ,y;
    struct Kingdom kingdoms[4];
    struct Village villages[20];
    int kingdomCount = 0;
    int villageCount = 0;
    printf("please inter Height and Width:");
    scanf("%d %d", &x, &y);
    while (x <= 0 || y <= 0 || x > 17 || y > 17) {
        printf("please inter Height and Width:");
        scanf("%d %d", &x, &y);
    }

    // Mark special points on the map
    Kingdoms(x, y, kingdoms, &kingdomCount);
    Villages(x, y, villages, &villageCount);
    ForceClosed(x, y);
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

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(Background, 0, 0, WHITE);
        grid(x, y);
        float offsetX = (WINDOW_WIDTH - x * 68) / 2.0;
        float offsetY = (WINDOW_HEIGHT - y * 68) / 2.0;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; ++j) {
                if (map[i][j] == 'c') {
                    DrawTexture(Kingdom, offsetX + j * 68, offsetY + i * 68, WHITE);
                }
                else if (map[i][j] == 'v') {
                    DrawTexture(Village, offsetX + j * 68, offsetY + i * 68, WHITE);

                }
                else if (map[i][j] == 'x') {
                    DrawTexture(ForceClosed, offsetX + j * 68, offsetY + i * 68, WHITE);
                }
                else {
                    char text = map[i][j];
                    DrawText(TextFormat("%d", text), offsetX + j * 68, offsetY + i * 68, 24, RED);
                }


            }

        }

        for (int k = 1; k <= kingdomCount; k++) {
            int xq = kingdoms[k -1].x;
            int yq = kingdoms[k -1].y ;
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    if (map[i][j] == 'v') {
                        // Generate the road from (xq, yq) to the village (i, j)
                        Road(xq, yq, i, j);
                    }
                }
            }
        }

// Next, draw the entire map, marking all paths ('r') in WHITE
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                if (map[i][j] == 'r') {
                    DrawRectangle(offsetX + j * 68, offsetY + i * 68, 68, 68, WHITE);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

