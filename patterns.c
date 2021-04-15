#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "patterns.h"

struct pattern patterns[] = {
    {"random", random_pattern},
    {"glider", glider},
	{"blinker", blinker},
};

// return the number of patterns in the struct. for use with looping through the list
size_t pattern_amt() {return sizeof (patterns)/sizeof (struct pattern);}

/*******************************************************/
/*	PATTERNS START									   */
/*******************************************************/

// place living cells in random places in a starting grid
void random_pattern(int **grid, int size)
{
    int hits, n1, n2;

    hits = (int)(size*size)*0.6;
    srand(time(0));
    for (int i = 0; i < hits; i++) {
        n1 = rand() % ((size-1) - 0 + 1);
        n2 = rand() % ((size-1) - 0 + 1);

        grid[n1][n2] = 1;
    }
}

void glider(int **g, int size)
{
	/************
	 * . . . . . 
	 * . . . # .
	 * . # . # .
	 * . . # # .
	 * . . . . .
	 * *********/

	int mid = size/2;

	g[mid-1][mid+1] = 1;
	g[mid][mid+1] = 1;
	g[mid+1][mid+1] = 1;
	g[mid+1][mid] = 1;
	g[mid][mid-1] = 1;
}

void blinker(int **g, int size)
{
	/************
	 * . . . . . 
	 * . . . . .
	 * . # # # .
	 * . . . . .
	 * . . . . .
	 * *********/

	int mid = size/2;

	g[mid][mid] = 1;
	g[mid][mid-1] = 1;
	g[mid][mid+1] = 1;
}

/*******************************************************/
/*	PATTERNS END									   */
/*******************************************************/



// check if a pattern is in the list of patterns
int pattern_check(char *pattern, int **grid, int size)
{
	size_t i, len;

	len = pattern_amt();
	for (i = 0; i < len; i++) {
		if (strcmp(pattern, patterns[i].pattern_name) == 0) {
            patterns[i].f(grid, size);
            return 1;
        }
	}
	return 0;
}


// get the current list of pattern names and place them in an array
// user must free
char **get_pattern_list(void)
{
	size_t i, len;
	char **pattern_list;

	len = pattern_amt();
	pattern_list = calloc(len+1, sizeof(char*));
	for (i = 0; i < len; i++) {
		pattern_list[i] = calloc(PBUF, sizeof(char));
		assert(pattern_list[i]);
	}
	assert(pattern_list);

	for (i = 0; i < len; i++) {
		strcpy(pattern_list[i], patterns[i].pattern_name);
	}
	return pattern_list;
}