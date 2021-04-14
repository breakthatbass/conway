#ifndef __GRID_H__
#define __GRID_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int **init_grid(int size);

void free_grid(int **grid, int size);

void print_grid(int **g, int size);

int gridcmp(int **src1, int **src2, int size);

#endif