#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "colors.h"
#include "constants.h"
#include "drawings.h"
#include "animations.h"
#include "../tetrominos/tetrominos.h"

// Helper function to draw shadow effect
void DrawShadow(Rectangle rect, float offsetX, float offsetY, float blur)
{
    (void)blur; // Unused parameter - reserved for future enhancement
    DrawRectanglePro((Rectangle){rect.x + offsetX, rect.y + offsetY, rect.width, rect.height},
                     (Vector2){0, 0}, 0, Fade(SHADOW_COLOR, 0.3f));
}

// Helper function to draw gradient-like effect
void DrawGradientBackground(Rectangle rect, Color topColor, Color bottomColor)
{
    int steps = 20;
    float stepHeight = rect.height / steps;
    for (int i = 0; i < steps; i++) {
        float alpha = (float)i / steps;
        Color lerpColor = {
            (unsigned char)(topColor.r * (1 - alpha) + bottomColor.r * alpha),
            (unsigned char)(topColor.g * (1 - alpha) + bottomColor.g * alpha),
            (unsigned char)(topColor.b * (1 - alpha) + bottomColor.b * alpha),
            (unsigned char)(topColor.a * (1 - alpha) + bottomColor.a * alpha)
        };
        DrawRectangle(rect.x, rect.y + i * stepHeight, rect.width, stepHeight, lerpColor);
    }
}

void Drawings(int grid[GRID_ROWS][GRID_COLS], int score, int highScore, int totalLines, int level,
              int nextTetromino, int currentTetromino, int playerX, int playerY, int rotation,
              bool gameOver, LineClearAnimation *lineClearAnim, GameOverAnimation *gameOverAnim)
{
    BeginDrawing();
    ClearBackground(backgroundPINK);

    // ========== PANEL INFO (RIGHT SIDE) ==========
    int panelWidth = 320;
    int panelHeight = 500;
    int panelX = (OFFSET_X - panelWidth) / 2;
    int panelY = 220;

    // Panel shadow
    DrawShadow((Rectangle){panelX, panelY, panelWidth, panelHeight}, 3, 3, 5);

    // Panel background with rounded corners
    DrawRectangleRounded(
        (Rectangle){panelX - 3, panelY - 3, panelWidth + 6, panelHeight + 6},
        0.1f, 8, DARK_PINK);

    DrawRectangleRounded(
        (Rectangle){panelX, panelY, panelWidth, panelHeight},
        0.1f, 8, scoreBackground);

    // Panel info text styling
    int spacing = 30;
    int sectionSpacing = 80;

    // HIGH SCORE
    DrawText("HIGH SCORE", panelX + 20, panelY + 20, 20, TEXT_PRIMARY);
    DrawText(TextFormat("%d", highScore), panelX + 20, panelY + 20 + spacing, 30, TEXT_PRIMARY);

    // SCORE
    DrawText("SCORE", panelX + 20, panelY + 20 + sectionSpacing, 20, TEXT_PRIMARY);
    DrawText(TextFormat("%d", score), panelX + 20, panelY + 20 + sectionSpacing + spacing, 30, TEXT_ACCENT);

    // LINES
    DrawText("LINES", panelX + 20, panelY + 20 + 2 * sectionSpacing, 20, TEXT_PRIMARY);
    DrawText(TextFormat("%d", totalLines), panelX + 20, panelY + 20 + 2 * sectionSpacing + spacing, 30, TEXT_PRIMARY);

    // LEVEL
    DrawText("LEVEL", panelX + 160, panelY + 20 + 2 * sectionSpacing, 20, TEXT_PRIMARY);
    DrawText(TextFormat("%d", level), panelX + 160, panelY + 20 + 2 * sectionSpacing + spacing, 30, ACCENT_CYAN);

    // NEXT PIECE
    int extraSpacing = 50;
    int nextTextY = panelY + 20 + 2 * sectionSpacing + spacing + extraSpacing;
    DrawText("NEXT", panelX + panelWidth / 2 - 30, nextTextY, 20, TEXT_PRIMARY);

    int nextBoxWidth = 230;
    int nextBoxX = panelX + (panelWidth - nextBoxWidth) / 2;
    int nextBoxY = nextTextY + 25;
    int nextBoxHeight = panelY + panelHeight - nextBoxY - 10;

    // Next box with shadow and highlight
    DrawShadow((Rectangle){nextBoxX, nextBoxY, nextBoxWidth, nextBoxHeight}, 2, 2, 3);
    DrawRectangleRounded(
        (Rectangle){nextBoxX, nextBoxY, nextBoxWidth, nextBoxHeight},
        0.2f, 8, nextBoxPink);
    DrawRectangleRoundedLines(
        (Rectangle){nextBoxX, nextBoxY, nextBoxWidth, nextBoxHeight},
        0.2f, 8, HIGHLIGHT_COLOR);

    int previewX = (nextBoxX + nextBoxWidth / 2) / CELL_SIZE - 1;
    int previewY = (nextBoxY + nextBoxHeight / 2) / CELL_SIZE - 1;
    DrawTetromino(nextTetromino, 0, previewX, previewY, CELL_SIZE, 0, 0, neonPink);

    // ========== TITLE ==========
    DrawText("TETRIS", 50, 50, 100, TEXT_PRIMARY);
    DrawText("Made by Barbul Karina <3", 110, 150, 20, TEXT_ACCENT);

    // ========== GAME GRID ==========
    float border = 5.0f;

    // Grid shadow effect
    DrawShadow((Rectangle){OFFSET_X - border, OFFSET_Y - border, (GRID_COLS * CELL_SIZE) + (border * 2),
                          (GRID_ROWS * CELL_SIZE) + (border * 2)}, 4, 4, 6);

    // Grid border
    DrawRectangleRounded(
        (Rectangle){OFFSET_X - border, OFFSET_Y - border, (GRID_COLS * CELL_SIZE) + (border * 2),
                   (GRID_ROWS * CELL_SIZE) + (border * 2)},
        0.1f, 8, DARK_PINK);

    // Grid background
    DrawRectangleRounded(
        (Rectangle){OFFSET_X, OFFSET_Y, GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE},
        0.1f, 8, SALMON);

    // GRID LINES
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            DrawRectangleRoundedLines(
                (Rectangle){OFFSET_X + j * CELL_SIZE, OFFSET_Y + i * CELL_SIZE, CELL_SIZE, CELL_SIZE},
                0.2f, 2, gridLine);
        }
    }

    // ========== DRAW GRID BLOCKS ==========
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (grid[i][j] > 0) {
                Color blockColor = DARK_PINK;

                // Line clear animation - flashing effect
                if (lineClearAnim && lineClearAnim->rowsClearing[i] && lineClearAnim->animation.isActive) {
                    float progress = GetAnimationProgress(lineClearAnim->animation);
                    // Create blink effect
                    float blink = sinf(progress * 3.14159f * 4) * 0.5f + 0.5f;
                    blockColor = Fade(blockColor, 0.3f + blink * 0.7f);
                    // Add white flash
                    if (blink > 0.5f) {
                        blockColor = (Color){
                            (unsigned char)(blockColor.r * 0.5f + 255 * 0.5f),
                            (unsigned char)(blockColor.g * 0.5f + 255 * 0.5f),
                            (unsigned char)(blockColor.b * 0.5f + 255 * 0.5f),
                            255
                        };
                    }
                }

                DrawRectangle(
                    OFFSET_X + j * CELL_SIZE,
                    OFFSET_Y + i * CELL_SIZE,
                    CELL_SIZE - 1,
                    CELL_SIZE - 1,
                    blockColor);

                // Add shine effect to blocks
                DrawRectangle(
                    OFFSET_X + j * CELL_SIZE + 1,
                    OFFSET_Y + i * CELL_SIZE + 1,
                    CELL_SIZE - 3,
                    2,
                    HIGHLIGHT_COLOR);
            }
        }
    }

    // ========== CURRENT BLOCK (with glow effect) ==========
    DrawTetromino(currentTetromino, rotation, playerX, playerY, CELL_SIZE, OFFSET_X, OFFSET_Y, neonPink);

    // ========== GAME OVER ANIMATION & SCREEN ==========
    if (gameOver) {
        if (gameOverAnim && gameOverAnim->active) {
            float progress = gameOverAnim->elapsedTime / gameOverAnim->duration;

            // Dramatic effect for game over
            if (gameOverAnim->type == 1) {
                // Flash effect - fill grid with red and fade
                float flashAlpha = sinf(progress * 3.14159f) * 0.6f;
                DrawRectangle(OFFSET_X, OFFSET_Y, GRID_COLS * CELL_SIZE, GRID_ROWS * CELL_SIZE,
                             Fade(GAME_OVER_RED, flashAlpha));
            }

            // Fade out the grid as game over progresses
            Color fadeOut = Fade(BLACK, progress * 0.4f);
            DrawRectangle(0, 0, 900, 800, fadeOut);
        }

        // Game over screen with improved styling
        DrawRectangle(0, 0, 900, 800, Fade(BLACK, 0.5f));

        // Game over panel
        int goWidth = 500;
        int goHeight = 300;
        int goX = (900 - goWidth) / 2;
        int goY = (800 - goHeight) / 2;

        // Background panel with shadow
        DrawShadow((Rectangle){goX, goY, goWidth, goHeight}, 5, 5, 8);
        DrawRectangleRounded((Rectangle){goX - 2, goY - 2, goWidth + 4, goHeight + 4}, 0.15f, 8,
                            VIBRANT_PINK);
        DrawRectangleRounded((Rectangle){goX, goY, goWidth, goHeight}, 0.15f, 8, scoreBackground);

        // Game over text with styling
        DrawText("GAME OVER", goX + 50, goY + 30, 80, GAME_OVER_RED);

        // Score display
        DrawText(TextFormat("Score: %d", score), goX + 80, goY + 120, 40, TEXT_PRIMARY);
        DrawText(TextFormat("High Score: %d", highScore), goX + 70, goY + 170, 35, TEXT_ACCENT);

        // Instructions
        DrawText("Press R to restart", goX + 100, goY + 240, 25, TEXT_SECONDARY);
        DrawText("Press Q to quit", goX + 140, goY + 270, 25, TEXT_SECONDARY);
    }

    EndDrawing();
}
