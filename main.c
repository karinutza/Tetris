#include <stdio.h>
#include "raylib.h"

int main(void) {
    InitWindow(1300, 800, "Tetris Game");
    #ifdef DARK_PINK
        printf("UIBFIUABFUBFUBWEF");
    #endif
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawText("TETRIS", 50, 50, 100, BLACK);
            DrawText("Made by Barbul Karina <3", 110, 150, 20, BLACK);
            DrawRectangle(500, 50, 700, 700, PINK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}