#include "tetrominos.h"
#include <stdlib.h>
#include <time.h>

int tetrominos[NUM_TETROMINOS][BLOCK_SIZE][BLOCK_SIZE];

void InitTetrominos() {
    // I
    int I[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    };

    // O
    int O[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // T
    int T[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // S
    int S[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // Z
    int Z[BLOCK_SIZE][BLOCK_SIZE] = {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // J
    int J[BLOCK_SIZE][BLOCK_SIZE] = {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    //I V   
    int IV[BLOCK_SIZE][BLOCK_SIZE] = {
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0}
    };

    // L
    int L[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // Copiază formele în tetrominos
    for(int t=0; t<NUM_TETROMINOS; t++) {
        int (*src)[BLOCK_SIZE];
        switch(t) {
            case 0: src = I; break;
            case 1: src = O; break;
            case 2: src = T; break;
            case 3: src = S; break;
            case 4: src = Z; break;
            case 5: src = J; break;
            case 6: src = L; break;
            case 7: src = IV; break;
        }
        for(int i=0;i<BLOCK_SIZE;i++)
            for(int j=0;j<BLOCK_SIZE;j++)
                tetrominos[t][i][j] = src[i][j];
    }

    // Inițializează seed-ul random
    srand(time(NULL));
}

// Returnează un tetromino random
int GetRandomTetromino() {
    return rand() % NUM_TETROMINOS;
}

// Desenează un tetromino în grid
void DrawTetromino(int tetrominoIndex, int playerX, int playerY, int cellSize, int offsetX, int offsetY, Color color) {
    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            if(tetrominos[tetrominoIndex][i][j] == 1) {
                DrawRectangle(
                    offsetX + (playerX + j) * cellSize,
                    offsetY + (playerY + i) * cellSize,
                    cellSize - 1,
                    cellSize - 1,
                    color
                );
            }
        }
    }
}