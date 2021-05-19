#ifndef __CONWAY_H__
#define __CONWAY_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// main conway algorithm (recursive)
void life(int **g, int size);

// place living cells in random places in a starting grid
void random_pattern(int **grid, int size);

#endif