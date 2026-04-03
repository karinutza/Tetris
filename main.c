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
                score = 0;
                totalLines = 0;
                level = 1;
                isHardDropping = false;
                timpScurs = 0;
                currentTetromino = GetRandomTetromino();
                nextTetromino = GetRandomTetromino();
                gameOver = false;
            }
            
            Drawings(grid, score, highScore, totalLines, level, nextTetromino, currentTetromino, playerX, playerY, gameOver);
            continue;
        }


        // MOVEMENT
        if (IsKeyPressed(KEY_LEFT))
        {
            bool canMoveLeft = true;
            for (int i = 0; i < BLOCK_SIZE; i++)
                for (int j = 0; j < BLOCK_SIZE; j++)
                    if (tetrominos[currentTetromino][i][j] == 1)
                    {
                        int newX = playerX + j - 1;
                        int newY = playerY + i;
                        if (newX < 0)
                            canMoveLeft = false;
                        if (newY >= 0 && newY < GRID_ROWS && newX >= 0 && grid[newY][newX] == 1)
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
                    if (tetrominos[currentTetromino][i][j] == 1)
                    {
                        int newX = playerX + j + 1;
                        int newY = playerY + i;
                        if (newX >= GRID_COLS)
                            canMoveRight = false;
                        if (newY >= 0 && newY < GRID_ROWS && newX < GRID_COLS && grid[newY][newX] == 1)
                            canMoveRight = false;
                    }
            if (canMoveRight) playerX++;
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
                    if (tetrominos[currentTetromino][i][j] == 1) {
                        int newX = playerX + j;
                        int newY = playerY + i + 1;

                        if (newX < 0 || newX >= GRID_COLS || newY >= GRID_ROWS || grid[newY][newX] == 1) {
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
                        if (tetrominos[currentTetromino][i][j] == 1) {
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


                // DETECTARE GAME OVER
                bool spawnCollides = false;
                for (int i = 0; i < BLOCK_SIZE; i++)
                {
                    for (int j = 0; j < BLOCK_SIZE; j++)
                    {
                        if (tetrominos[currentTetromino][i][j] == 1)
                        {
                            int x = playerX + j;
                            int y = playerY + i;
                            if (y >= 0 && y < GRID_ROWS && grid[y][x] == 1)
                            {
                                spawnCollides = true;
                            }
                        }
                    }
                }

                if (spawnCollides)
                    gameOver = true;

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

        Drawings(grid, score, highScore, totalLines, level, nextTetromino, currentTetromino, playerX, playerY, gameOver);
    }

    CloseWindow();
    return 0;
}