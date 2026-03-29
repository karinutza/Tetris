#ifndef TETROMINOS_H
#define TETROMINOS_H

#include "raylib.h"
#include "../drawings/constants.h"
#include <stdlib.h>
#include <time.h>

extern int tetrominos[NUM_TETROMINOS][BLOCK_SIZE][BLOCK_SIZE];

void InitTetrominos();                  
int GetRandomTetromino();                
void DrawTetromino(int tetrominoIndex, int playerX, int playerY, int cellSize, int offsetX, int offsetY, Color color);

#endif