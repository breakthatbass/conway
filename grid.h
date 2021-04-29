#ifndef __GRID_H__
#define __GRID_H__

#include <stdio.h>
#include <stdlib.h>


// get current height of terminal to use for grid sizing
int get_term_height();

// allocate space for a grid based on size
int **init_grid(int size);

void free_grid(int **grid, int size);

void print_grid(int **g, int size);

// compare two 2d arrays
int gridcmp(int **src1, int **src2, int size);

#endif
