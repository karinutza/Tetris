#ifndef DRAWINGS_H
#define DRAWINGS_H

#include "raylib.h"
#include "constants.h"

void Drawings(int grid[GRID_ROWS][GRID_COLS],
              int score, int highScore,
              int totalLines, int level,
              int currentTetromino,
              int playerX, int playerY,
              bool gameOver);

#endif