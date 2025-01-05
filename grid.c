//
// Created by Asus on 12/3/2024.
//
#include "raylib.h"
#include "GRID2.h"

#include "raylib.h"
#include "GRID2.h"

int grid(int i, int j) {
    // Calculate spacing between lines
    float vertical_spacing = 68;
    float horizontal_spacing = 68;

    // Calculate the actual grid width and height
    float grid_width = (j) * vertical_spacing;
    float grid_height = (i) * horizontal_spacing;

    // Calculate the offset for centering the grid
    float offset_x = (WINDOW_WIDTH - grid_width) / 2.0;
    float offset_y = (WINDOW_HEIGHT - grid_height) / 2.0;

    // Draw vertical lines
    for (int y = 0; y <= i; y++) {
        float posY = offset_y+ y * vertical_spacing;
        DrawLine(offset_x, posY, offset_x+grid_width, posY, BLACK);
    }

    // Draw horizontal lines
    for (int x = 0; x <= j; x++) {
        float posx = offset_x + x * horizontal_spacing;
        DrawLine(posx, offset_y, posx, offset_y + grid_height,BLACK);
    }
}