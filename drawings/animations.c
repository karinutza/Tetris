#include "animations.h"
#include <string.h>

LineClearAnimation CreateLineClearAnimation(int clearedRows[GRID_ROWS], int clearCount, float duration)
{
    LineClearAnimation anim = {0};
    anim.animation.isActive = true;
    anim.animation.duration = duration;
    anim.animation.elapsedTime = 0;
    anim.clearCount = clearCount;

    memcpy(anim.rowsClearing, clearedRows, sizeof(anim.rowsClearing));
    return anim;
}

void UpdateLineClearAnimation(LineClearAnimation *anim, float deltaTime)
{
    if (!anim->animation.isActive) return;

    anim->animation.elapsedTime += deltaTime;
    if (anim->animation.elapsedTime >= anim->animation.duration) {
        anim->animation.elapsedTime = anim->animation.duration;
    }
}

bool IsLineClearAnimationFinished(LineClearAnimation *anim)
{
    return anim->animation.elapsedTime >= anim->animation.duration;
}

GameOverAnimation CreateGameOverAnimation(int type, float duration)
{
    GameOverAnimation anim = {0};
    anim.active = true;
    anim.type = type;
    anim.duration = duration;
    anim.elapsedTime = 0;
    return anim;
}

void UpdateGameOverAnimation(GameOverAnimation *anim, float deltaTime)
{
    if (!anim->active) return;

    anim->elapsedTime += deltaTime;
    if (anim->elapsedTime >= anim->duration) {
        anim->elapsedTime = anim->duration;
    }
}

bool IsGameOverAnimationFinished(GameOverAnimation *anim)
{
    return anim->elapsedTime >= anim->duration;
}

float GetAnimationProgress(Animation anim)
{
    if (anim.duration <= 0) return 1.0f;
    return anim.elapsedTime / anim.duration;
}

// Returns color based on animation progress for flashing effect
Color GetFlashColor(float progress)
{
    // Create a blink effect: 0-0.5 = white flash, 0.5-1 = fade to original
    if (progress < 0.5f) {
        float blinkProgress = progress * 2; // 0 to 1
        return Fade(WHITE, blinkProgress);
    } else {
        float fadeProgress = (progress - 0.5f) * 2; // 0 to 1
        return Fade(WHITE, 1.0f - fadeProgress);
    }
}
