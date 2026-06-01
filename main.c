#include <stdio.h>
#include <string.h>

#include "raylib.h"

#include "drawings/colors.h"
#include "drawings/constants.h"
#include "drawings/drawings.h"
#include "tetrominos/tetrominos.h"
#include "clearRows/clearRows.h"



int main(void)
{
    int grid[GRID_ROWS][GRID_COLS] = {0};
    int playerX = 3, playerY = -2;
    int rotation = 0;

    bool isHardDropping = false;
    float hardDropSpeed = 0.01f;

    // SCORE VARIABLES
    int score = 0;
    int highScore = 0;

    int totalLines = 0;
    int level = 1;

    float timpScurs = 0;
    float intervalCadere = 0.5;

    bool gameOver = false;

    InitWindow(900, 800, "Tetris Game");
    SetTargetFPS(60);

    InitTetrominos();
    int currentTetromino = GetRandomTetromino();
    int nextTetromino = GetRandomTetromino();      

    while (!WindowShouldClose())
    {
        //GAME OVER TEST
        if (gameOver)
        {
            if (IsKeyPressed(KEY_R)){
                // resetare
                memset(grid, 0, sizeof(grid));
                playerX = 3;
                playerY = -2;
                rotation = 0;
                score = 0;
                totalLines = 0;
                level = 1;
                isHardDropping = false;
                timpScurs = 0;
                currentTetromino = GetRandomTetromino();
                nextTetromino = GetRandomTetromino();
                gameOver = false;
            }

            Drawings(grid, score, highScore, totalLines, level, nextTetromino, currentTetromino, playerX, playerY, rotation, gameOver);
            continue;
        }


        // MOVEMENT
        if (IsKeyPressed(KEY_LEFT))
        {
            bool canMoveLeft = true;
            for (int i = 0; i < BLOCK_SIZE; i++)
                for (int j = 0; j < BLOCK_SIZE; j++)
                    if (tetrominos[currentTetromino][rotation][i][j] == 1)
                    {
                        int newX = playerX + j - 1;
                        int newY = playerY + i;
                        if (newX < 0)
                            canMoveLeft = false;
                        if (newY >= 0 && newY < GRID_ROWS && newX >= 0 && grid[newY][newX] != 0)
                            canMoveLeft = false;
                    }
            if (canMoveLeft) playerX--;
        }

        // if (IsKeyPressed())
        // {
            
        // }

        if (IsKeyPressed(KEY_RIGHT))
        {
            bool canMoveRight = true;
            for (int i = 0; i < BLOCK_SIZE; i++)
                for (int j = 0; j < BLOCK_SIZE; j++)
                    if (tetrominos[currentTetromino][rotation][i][j] == 1)
                    {
                        int newX = playerX + j + 1;
                        int newY = playerY + i;
                        if (newX >= GRID_COLS)
                            canMoveRight = false;
                        if (newY >= 0 && newY < GRID_ROWS && newX < GRID_COLS && grid[newY][newX] != 0)
                            canMoveRight = false;
                    }
            if (canMoveRight) playerX++;
        }

        // ROTATION
        if (IsKeyPressed(KEY_UP))
        {
            // O piece (square) doesn't rotate visibly
            if (currentTetromino != 1) {
                int newRotation = (rotation + 1) % 4;
                bool canRotate = false;
                int finalX = playerX;

                // Check if rotation fits at given X position
                bool rotationFits = true;
                for (int i = 0; i < BLOCK_SIZE && rotationFits; i++) {
                    for (int j = 0; j < BLOCK_SIZE && rotationFits; j++) {
                        if (tetrominos[currentTetromino][newRotation][i][j] == 1) {
                            int testX = playerX + j;
                            int testY = playerY + i;
                            // Check horizontal boundaries
                            if (testX < 0 || testX >= GRID_COLS) {
                                rotationFits = false;
                            }
                            // Check bottom boundary
                            if (testY >= GRID_ROWS) {
                                rotationFits = false;
                            }
                            // Check grid collision only in valid area
                            if (testY >= 0 && testY < GRID_ROWS && grid[testY][testX] != 0) {
                                rotationFits = false;
                            }
                        }
                    }
                }

                // If rotation fits at current position, apply it
                if (rotationFits) {
                    canRotate = true;
                } else {
                    // Try wall kick - move 1 or 2 cells left/right
                    int kickOffsets[] = {-1, 1, -2, 2};
                    for (int k = 0; k < 4 && !canRotate; k++) {
                        rotationFits = true;
                        int kickX = playerX + kickOffsets[k];
                        for (int i = 0; i < BLOCK_SIZE && rotationFits; i++) {
                            for (int j = 0; j < BLOCK_SIZE && rotationFits; j++) {
                                if (tetrominos[currentTetromino][newRotation][i][j] == 1) {
                                    int testX = kickX + j;
                                    int testY = playerY + i;
                                    if (testX < 0 || testX >= GRID_COLS) {
                                        rotationFits = false;
                                    }
                                    if (testY >= GRID_ROWS) {
                                        rotationFits = false;
                                    }
                                    if (testY >= 0 && testY < GRID_ROWS && grid[testY][testX] != 0) {
                                        rotationFits = false;
                                    }
                                }
                            }
                        }
                        if (rotationFits) {
                            canRotate = true;
                            finalX = kickX;
                        }
                    }
                }

                if (canRotate) {
                    rotation = newRotation;
                    playerX = finalX;
                }
            }
        }

        // FALLING
        timpScurs += GetFrameTime();

        float baseInterval = 0.5f - (level - 1) * 0.05f;
        if (baseInterval < 0.1f) baseInterval = 0.1f;

        float currentSpeed = isHardDropping ? hardDropSpeed : baseInterval;
        if (IsKeyDown(KEY_DOWN)) currentSpeed = 0.05f;

        if (timpScurs >= currentSpeed)
        {
            bool canMoveDown = true;
            for (int i = 0; i < BLOCK_SIZE; i++) {
                for (int j = 0; j < BLOCK_SIZE; j++) {
                    if (tetrominos[currentTetromino][rotation][i][j] == 1) {
                        int newX = playerX + j;
                        int newY = playerY + i + 1;

                        if (newX < 0 || newX >= GRID_COLS || newY >= GRID_ROWS) {
                            canMoveDown = false;
                        }
                        if (newY >= 0 && newY < GRID_ROWS && grid[newY][newX] != 0) {
                            canMoveDown = false;
                        }
                    }
                }
            }

            if (canMoveDown) {
                playerY++;
            } else {
                // LOCK BLOCK
                for (int i = 0; i < BLOCK_SIZE; i++) {
                    for (int j = 0; j < BLOCK_SIZE; j++) {
                        if (tetrominos[currentTetromino][rotation][i][j] == 1) {
                            int gridX = playerX + j;
                            int gridY = playerY + i;

                            if (gridX >= 0 && gridX < GRID_COLS && gridY >= 0 && gridY < GRID_ROWS) {
                                grid[gridY][gridX] = currentTetromino + 1;
                            }
                        }
                    }
                }

                currentTetromino = nextTetromino;
                nextTetromino = GetRandomTetromino();

                playerX = 3;
                playerY = -2;
                rotation = 0;


                // DETECTARE GAME OVER
                bool spawnCollides = false;
                for (int i = 0; i < BLOCK_SIZE; i++)
                {
                    for (int j = 0; j < BLOCK_SIZE; j++)
                    {
                        if (tetrominos[currentTetromino][rotation][i][j] == 1)
                        {
                            int x = playerX + j;
                            int y = playerY + i;
                            if (y >= 0 && y < GRID_ROWS && x >= 0 && x < GRID_COLS && grid[y][x] != 0)
                            {
                                spawnCollides = true;
                            }
                        }
                    }
                }

                if (spawnCollides)
                    gameOver = true;

                // Check top border - game over if blocks reach above grid
                if (!gameOver) {
                    for (int j = 0; j < GRID_COLS; j++) {
                        if (grid[0][j] != 0) {
                            gameOver = true;
                            break;
                        }
                    }
                }

                if (!gameOver){
                    int cleared = ClearFullRows(grid);
                    totalLines += cleared;
                    score += cleared * 100;

                    level = totalLines / 5 + 1;
                    intervalCadere = 0.5f - (level - 1) * 0.05f;
                    if (intervalCadere < 0.1f) intervalCadere = 0.1f;

                    if (score > highScore) highScore = score;

                    isHardDropping = false;
                }
            }
            timpScurs = 0;
        }

        // SOFT DROP
        if (IsKeyDown(KEY_DOWN))
            currentSpeed = 0.05f;

        // HARD DROP
        if (IsKeyPressed(KEY_SPACE))
            isHardDropping = true;

        Drawings(grid, score, highScore, totalLines, level, nextTetromino, currentTetromino, playerX, playerY, rotation, gameOver);
    }

    CloseWindow();
    return 0;
}