#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "meqdardehi.h"
#include "GRID2.h"

#define IMAGE_PATH "C:/Users/Asus/CLionProjects/projectfum/map.png"
//defining map
int map[17][17] = {0};
int vProduction[20][2] = {0};
const char *labels[5] = {"Attack", "Defend", "Trade", "Upgrade", "Pass"};
void (*actions[5])() = {Attack, soldier, workers, Upgrade, Road};
int currentkingdom = 0;

Kingdom kingdoms[4];
Village villages[20];

int main() {

    //receiving map Height and Width
    int x, y;

    int kingdomCount = 0;
    int villageCount = 0;
    printf("please enter Height and Width:");
    scanf("%d %d", &x, &y);
    while (x <= 0 || y <= 0 ||  x > 17 || y > 17) {
        printf("please enter Height and Width:");
        scanf("%d %d", &x, &y);
    }

    // Mark special points on the map
    Kingdoms(x, y, kingdoms, &kingdomCount);
    Villages(x, y, villages, &villageCount);
    ForceClosed(x, y);

    // setting difficulty for empty map[i][j]
    Empty(x, y);

    InitWindow(0, 0, "MAP");

    // defining each  special point texture
    Texture2D Background = LoadTexture(IMAGE_PATH);
    Texture2D Kingdom = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/kingdom.png");
    Texture2D Village = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/1.png");
    Texture2D ForceClosed = LoadTexture("C:/Users/Asus/CLionProjects/projectfum/Water_ruins2.png");
    Texture2D guide= LoadTexture("C:/Users/ASUS/CLionProjects/projectfum/1000020318-new.jpg.png");
    // Set the target frame rate to 60 frames per second for smooth rendering
    SetTargetFPS(60);

    // drawing Map
    while (!WindowShouldClose() && kingdoms[currentkingdom].villagenumber!=villageCount) {
        Vector2 mouseposition = GetMousePosition();
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
                } else if(map[i][j]==0){
                    DrawRectangle( offsetX + j * 68, offsetY + i * 68,68,68,RED);
                }else if(map[i][j]==-1){
                    DrawRectangle(offsetX + j * 68, offsetY + i * 68,68,68,WHITE);
                }else if(map[i][j]==-2){
                    DrawRectangle(offsetX + j * 68, offsetY + i * 68,68,68,GREEN);
                }else if(map[i][j]==-3) {
                    DrawRectangle(offsetX + j * 68, offsetY + i * 68, 68, 68, BLUE);
                }else {
                    char text = map[i][j];
                    DrawText(TextFormat("%d", text), offsetX + j * 68, offsetY + i * 68, 24, RED);
                }
                if (CheckCollisionPointRec(mouseposition, cellrect)) {
                    char infotext[50];
                    DrawRectangle(cellrect.x, cellrect.y, 68, 68, GRAY);
                if (map[i][j] == 'v') {
                    for (int v = 0; v < villageCount; v++) {
                        if (villages[v].x == i && villages[v].y == j) {
                            sprintf(infotext, "gold: %d\nfood: %d\nowner: %d",
                                    villages[v].GoldProduction,
                                    villages[v].FoodProduction,
                                    villages[v].ownerId);
                            DrawText(infotext, cellrect.x, cellrect.y, 10, BLACK);
                            break;
                        }
                    }
                } else if (map[i][j] == 'c') {
                    for (int c = 0; c < kingdomCount; c++) {
                        if (kingdoms[c].x == i && kingdoms[c].y == j) {
                            sprintf(infotext, "Coins: %d\nServes:%d\nGold:%d\nFood:%d\nWorkers:%d\nSoldier:%d",
                                    kingdoms[c].Gold,
                                    kingdoms[c].Serve,
                                    kingdoms[c].GoldProduction,
                                    kingdoms[c].FoodProduction,
                                    kingdoms[c].WorkersCount,
                                    kingdoms[c].soldierCount);
                            DrawText(infotext, cellrect.x, cellrect.y, 10, BLACK);
                            break;
                        }
                    }
                }
            }

        }
    }
        int showguide;
        if(IsKeyPressed(KEY_ENTER)){
             showguide=!showguide;
        }
        if(!showguide) DrawTexture(guide,500,0,WHITE);

   /* for (int k = 1; k <= kingdomCount; k++) {
        int xq = kingdoms[k - 1].x;
        int yq = kingdoms[k - 1].y;
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                if (map[i][j] == 'v') {
                    // Generate the road from (xq, yq) to the village (i, j)
                    SuggestedRoad(xq, yq, i, j);
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
    }*/




        if (IsKeyPressed(KEY_ONE)) {
            Upgrade(kingdoms, currentkingdom);
            soldier();
            currentkingdom++;

        } else if (IsKeyPressed(KEY_TWO)) {
            Upgrade( kingdoms, currentkingdom);
            workers();
            currentkingdom++;
        }
        else if(IsKeyPressed(KEY_THREE)){
            Upgrade( kingdoms, currentkingdom);
            Food();
            currentkingdom++;
        }
        else if(IsKeyPressed(KEY_FOUR)){
            int xroad,yroad;
            yroad=((mouseposition.x-offsetX)/68);
            xroad=((mouseposition.y-offsetY))/68;
            Upgrade( kingdoms, currentkingdom);
            Road(xroad,yroad,villageCount);
            currentkingdom++;
        }
        else if(IsKeyPressed(KEY_FIVE)){
            Upgrade( kingdoms, currentkingdom);
            currentkingdom++;
        }

        if (currentkingdom >= kingdomCount) {
            currentkingdom = 0; // Loop back to the first kingdom
        }




    EndDrawing();
}
    CloseWindow();
return 0;
}