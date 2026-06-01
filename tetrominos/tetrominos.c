#include "tetrominos.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

int tetrominos[NUM_TETROMINOS][4][BLOCK_SIZE][BLOCK_SIZE];

void RotateClockwise(int src[BLOCK_SIZE][BLOCK_SIZE], int dst[BLOCK_SIZE][BLOCK_SIZE]) {
    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            dst[j][BLOCK_SIZE - 1 - i] = src[i][j];
        }
    }
}

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

    // L
    int L[BLOCK_SIZE][BLOCK_SIZE] = {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    // I vertical
    int IV[BLOCK_SIZE][BLOCK_SIZE] = {
        {1,0,0,0},
        {1,0,0,0},
        {1,0,0,0},
        {1,0,0,0}
    };

    int (*shapes[NUM_TETROMINOS])[BLOCK_SIZE][BLOCK_SIZE] = {
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])I,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])O,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])T,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])S,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])Z,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])J,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])L,
        (int (*)[BLOCK_SIZE][BLOCK_SIZE])IV
    };

    for(int t = 0; t < NUM_TETROMINOS; t++) {
        int temp[BLOCK_SIZE][BLOCK_SIZE];
        memcpy(tetrominos[t][0], shapes[t], sizeof(int) * BLOCK_SIZE * BLOCK_SIZE);

        for(int rot = 1; rot < 4; rot++) {
            RotateClockwise(tetrominos[t][rot - 1], temp);
            memcpy(tetrominos[t][rot], temp, sizeof(int) * BLOCK_SIZE * BLOCK_SIZE);
        }
    }

    srand(time(NULL));
}

int GetRandomTetromino() {
    return rand() % NUM_TETROMINOS;
}

void DrawTetromino(int tetrominoIndex, int rotation, int playerX, int playerY, int cellSize, int offsetX, int offsetY, Color color) {
    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            if(tetrominos[tetrominoIndex][rotation][i][j] == 1) {
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