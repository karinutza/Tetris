#include <stdio.h>

#include "raylib.h"
#include "colors.h"
#include "constants.h"
#include "drawings.h"
#include "../tetrominos/tetrominos.h"

void Drawings(int grid[GRID_ROWS][GRID_COLS], int score, int highScore, int totalLines, int level, int nextTetromino, int currentTetromino, int playerX, int playerY, bool gameOver)
{
    BeginDrawing();
    ClearBackground(backgroundPINK);

    // PANEL
    int panelWidth = 320;
    int panelHeight = 500;
    int panelX = (OFFSET_X - panelWidth) / 2;
    int panelY = 220;

    DrawRectangleRounded(
        (Rectangle){panelX - 3, panelY - 3, panelWidth + 6, panelHeight + 6},
        0.1f, 8, DARK_PINK);

    DrawRectangleRounded(
        (Rectangle){panelX, panelY, panelWidth, panelHeight},
        0.1f, 8, scoreBackground);

    // PANEL INFO (HIGH SCORE, SCORE, LINES, LEVEL, NEXT)
    int spacing = 30;
    int sectionSpacing = 80;

    // HIGH SCORE
    DrawText("HIGH SCORE", panelX + 20, panelY + 20, 20, WHITE);
    DrawText(TextFormat("%d", highScore), panelX + 20, panelY + 20 + spacing, 30, DARK_PINK);

    // SCORE
    DrawText("SCORE", panelX + 20, panelY + 20 + sectionSpacing, 20, WHITE);
    DrawText(TextFormat("%d", score), panelX + 20, panelY + 20 + sectionSpacing + spacing, 30, DARK_PINK);

    // LINES
    DrawText("LINES", panelX + 20, panelY + 20 + 2 * sectionSpacing, 20, WHITE);
    DrawText(TextFormat("%d", totalLines), panelX + 20, panelY + 20 + 2 * sectionSpacing + spacing, 30, DARK_PINK);

    // LEVEL
    DrawText("LEVEL", panelX + 160, panelY + 20 + 2 * sectionSpacing, 20, WHITE);
    DrawText(TextFormat("%d", level), panelX + 160, panelY + 20 + 2 * sectionSpacing + spacing, 30, DARK_PINK);

    // NEXT PIECE
    int extraSpacing = 50;
    int nextTextY = panelY + 20 + 2 * sectionSpacing + spacing + extraSpacing;
    DrawText("NEXT", panelX + panelWidth / 2 - 30, nextTextY, 20, WHITE);

    int nextBoxWidth = 230;
    int nextBoxX = panelX + (panelWidth - nextBoxWidth) / 2;

    int nextBoxY = nextTextY + 25;
    int nextBoxHeight = panelY + panelHeight - nextBoxY - 10;

    DrawRectangleRounded(
        (Rectangle){nextBoxX, nextBoxY, nextBoxWidth, nextBoxHeight},
        0.2f, 8, nextBoxPink);

    int previewX = (nextBoxX + nextBoxWidth / 2) / CELL_SIZE - 1;
    int previewY = (nextBoxY + nextBoxHeight / 2) / CELL_SIZE - 1;
    DrawTetromino(nextTetromino, previewX, previewY, CELL_SIZE, 0, 0, neonPink);

    // TITLE
    DrawText("TETRIS", 50, 50, 100, DARK_PINK);
    DrawText("Made by Barbul Karina <3", 110, 150, 20, PINK);

    // GRID BORDER
    float border = 5.0f;

    DrawRectangleRounded(
        (Rectangle){OFFSET_X - border, OFFSET_Y - border, (GRID_COLS * CELL_SIZE) + (border * 2), (GRID_ROWS * CELL_SIZE) + (border * 2)},
        0.1f, 8, DARK_PINK);

    DrawRectangleRounded(
        (Rectangle){OFFSET_X, OFFSET_Y, GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE},
        0.1f, 8, SALMON);

    // GRID LINES (subtle background grid)
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            DrawRectangleRoundedLines(
                (Rectangle){OFFSET_X + j * CELL_SIZE, OFFSET_Y + i * CELL_SIZE, CELL_SIZE, CELL_SIZE}, 0.2f, 2, gridLine);
        }
    }

    // DRAW GRID BLOCKS
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLS; j++)
        {
            if (grid[i][j] > 0)
            {
                DrawRectangle(
                    OFFSET_X + j * CELL_SIZE,
                    OFFSET_Y + i * CELL_SIZE,
                    CELL_SIZE - 1,
                    CELL_SIZE - 1,
                    DARK_PINK);
            }
        }
    }

    // CURRENT BLOCK
    DrawTetromino(currentTetromino, playerX, playerY, CELL_SIZE, OFFSET_X, OFFSET_Y, neonPink);

    // GAME OVER SCREEN
    if (gameOver == true)
    {
        DrawRectangle(0, 0, 900, 800, Fade(BLACK, 0.6f));
        DrawText("GAME OVER", 230, 300, 80, DARK_PINK);
        DrawText(TextFormat("Score: %d", score), 330, 400, 40, WHITE);
        DrawText("Press R to restart", 290, 460, 30, WHITE);
        DrawText("Press Q to quit", 350, 460, 30, WHITE);
    }

    EndDrawing();
}