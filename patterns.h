#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// fills the grid randomly with 1s for a random pattern to start with
void random_pattern(int **grid, int size);

/* the following are not in program yet */
void glider(int **g, int size);

void blinker(int **g, int size);

#endif