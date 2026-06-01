#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"
#include "constants.h"

// Animation states
typedef struct {
    bool isActive;
    float elapsedTime;
    float duration;
} Animation;

typedef struct {
    bool rowsClearing[GRID_ROWS];
    Animation animation;
    int clearCount;
} LineClearAnimation;

typedef struct {
    bool active;
    float elapsedTime;
    float duration;
    int type; // 0 = normal, 1 = dramatic (top border reached)
} GameOverAnimation;

// Function declarations
LineClearAnimation CreateLineClearAnimation(int clearedRows[GRID_ROWS], int clearCount, float duration);
void UpdateLineClearAnimation(LineClearAnimation *anim, float deltaTime);
bool IsLineClearAnimationFinished(LineClearAnimation *anim);

GameOverAnimation CreateGameOverAnimation(int type, float duration);
void UpdateGameOverAnimation(GameOverAnimation *anim, float deltaTime);
bool IsGameOverAnimationFinished(GameOverAnimation *anim);

float GetAnimationProgress(Animation anim);
Color GetFlashColor(float progress);

#endif
