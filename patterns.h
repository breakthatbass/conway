#ifndef __PATTERNS_H__
#define __PATTERNS_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct to associate a name with a function
// for easier calling of different patterns
struct pattern {
	char *pattern_name;
	void (*f)(int **grid, int size);
};

// fills the grid randomly with 1s for a random pattern to start with
void random_pattern(int **grid, int size);

void glider(int **g, int size);

void blinker(int **g, int size);

int pattern_check(char *pattern, int **grid, int size);

#endif