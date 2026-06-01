#ifndef CLEAR_ROWS_H
#define CLEAR_ROWS_H

#define GRID_ROWS 20
#define GRID_COLS 10

int ClearFullRows(int grid[GRID_ROWS][GRID_COLS]);
int ClearFullRowsWithTracking(int grid[GRID_ROWS][GRID_COLS], int clearedRows[GRID_ROWS]);

#endif