#include <stdio.h>
#include <string.h>

#include "raylib.h"
#include "../drawings/constants.h"

// CLEAR FULL ROWS + RETURN HOW MANY WERE CLEARED
int ClearFullRows(int grid[GRID_ROWS][GRID_COLS])
{
    int cleared = 0;
    for (int i = 0; i < GRID_ROWS; i++)
    {
        int full = 1;
        for (int j = 0; j < GRID_COLS; j++)
        {
            if (grid[i][j] == 0)
            {
                full = 0;
                break;
            }
        }

        if (full)
        {
            cleared++;

            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < GRID_COLS; j++)
                {
                    grid[k][j] = grid[k - 1][j];
                }
            }

            for (int j = 0; j < GRID_COLS; j++)
            {
                grid[0][j] = 0;
            }
        }
    }

    return cleared;
}
