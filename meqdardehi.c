//
// Created by ASUS on 11/30/2024.
//
#include "stdio.h"
#include "meqdardehi.h"
#include "raylib.h"
#include "type.h"

//defining map as an extern int to be known in all functions
extern int map[17][17];

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

        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y] != 0) i--;

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

            map[x][y] = 'c';
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
        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y] != 0) i--;
        else {
            villages[i].VillageId = i + 1;
            villages[i].x = x;
            villages[i].y = y;
            villages[i].ownerId = -1;

            printf("Please enter Gold production for Village %d: ", i + 1);
            scanf("%d", &villages[i].GoldProduction);

            printf("Please enter Food production for Village %d: ", i + 1);
            scanf("%d", &villages[i].FoodProduction);

            map[x][y] = 'v';

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


        if (x < 0 || y < 0 || x >= k || y >= j || map[x][y] != 0) {
            i--;
        } else {
            map[x][y] = 'x';
        }
    }
}


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


void DrawButtons(int screenWidth, int screenHeight, const char *buttonLabels[5], void (*buttonActions[5])()) {
    const int buttonWidth = 150;
    const int buttonHeight = 50;
    const int buttonSpacing = 20;
    const int startX = (1350 - (5 * buttonWidth + 4 * buttonSpacing)) / 2;
    const int startY = 350;

    for (int i = 0; i < 5; i++) {
        Rectangle buttonRect = {
                startX , startY+ i * (buttonWidth + buttonSpacing), buttonWidth, buttonHeight};

        // Check if the mouse is over the button
        Vector2 mousePosition = GetMousePosition();
        bool isHovered = CheckCollisionPointRec(mousePosition, buttonRect);
        bool isClicked = isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Draw button
        Color buttonColor = isHovered ? LIGHTGRAY : GRAY;
        DrawRectangleRec(buttonRect, buttonColor);
        DrawRectangleLinesEx(buttonRect, 2, BLACK);

        // Draw button label
        DrawText(buttonLabels[i], buttonRect.x + 10, buttonRect.y + 15, 20, BLACK);

        // Execute action if clicked
        if (isClicked && buttonActions[i] != NULL) {
            buttonActions[i]();
        }
    }
}
void Attack(){
    printf("Attack");
}
void workers(){
    if(kingdoms[currentkingdom].Serve >= 3) {
        kingdoms[currentkingdom].WorkersCount++;
        kingdoms[currentkingdom].Serve -=3;
        DrawText("Increased Kingdom's Workers Count!", 10, 40, 20, GREEN);
    }
}
void Upgrade( Kingdom * kingdoms, int count){
    kingdoms[count].Gold += kingdoms[count].GoldProduction;
    kingdoms[count].Serve += kingdoms[count].FoodProduction;
}
void Food(){
    if(kingdoms[currentkingdom].Gold >= 1){
        kingdoms[currentkingdom].Serve ++;
        kingdoms[currentkingdom].Gold --;
    }
}
void soldier(){
    if(kingdoms[currentkingdom] .Gold >= 2) {
        kingdoms[currentkingdom].soldierCount++;
        kingdoms[currentkingdom] .Gold -= 2;
        DrawText("Increased Kingdom's Soldier Count!", 10, 40, 20, GREEN);
    }
}

void Road(){
    printf("Road");
}