#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patterns.h"

struct pattern patterns[] = {
    {"random", random_pattern},
    {"glider", glider},
	{"blinker", blinker},
	{"pulsar", pulsar},
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


void pulsar(int **g, int size)
{
	/******************************
	*-7-6-5-4-3-2-1 0+1+2+3+4+5+6+7 
	* . . . . . . . . . . . . . . . -7
	* . . . # # # . . . # # # . . . -6
	* . . . . . . . . . . . . . . . -5
	* . # . . . . # . # . . . . # . -4
	* . # . . . . # . # . . . . # . -3
	* . # . . . . # . # . . . . # . -2
	* . . . # # # . . . # # # . . . -1
	* . . . . . . . 0 . . . . . . .  0
	* . . . # # # . . . # # # . . . +1
	* . # . . . . # . # . . . . # . +2
	* . # . . . . # . # . . . . # . +3
	* . # . . . . # . # . . . . # . +4
	* . . . . . . . . . . . . . . . +5
	* . . . # # # . . . # # # . . . +6
	* . . . . . . . . . . . . . . . +7
	*-7-6-5-4-3-2-1 0+1+2+3+4+5+6+7  
	*******************************/

	int mid = size/2;

	// top half
	g[mid-6][mid-4] = 1;
	g[mid-6][mid-3] = 1;
	g[mid-6][mid-2] = 1;

	g[mid-6][mid+4] = 1;
	g[mid-6][mid+3] = 1;
	g[mid-6][mid+2] = 1;

	g[mid-4][mid-6] = 1;
	g[mid-4][mid-1] = 1;
	g[mid-4][mid+6] = 1;
	g[mid-4][mid+1] = 1;
	
	g[mid-3][mid-6] = 1;
	g[mid-3][mid-1] = 1;
	g[mid-3][mid+6] = 1;
	g[mid-3][mid+1] = 1;

	g[mid-2][mid-6] = 1;
	g[mid-2][mid-1] = 1;
	g[mid-2][mid+6] = 1;
	g[mid-2][mid+1] = 1;

	g[mid-1][mid-4] = 1;
	g[mid-1][mid-3] = 1;
	g[mid-1][mid-2] = 1;

	g[mid-1][mid+4] = 1;
	g[mid-1][mid+3] = 1;
	g[mid-1][mid+2] = 1;

	// bottom half
	g[mid+6][mid-4] = 1;
	g[mid+6][mid-3] = 1;
	g[mid+6][mid-2] = 1;

	g[mid+6][mid+4] = 1;
	g[mid+6][mid+3] = 1;
	g[mid+6][mid+2] = 1;

	g[mid+4][mid-6] = 1;
	g[mid+4][mid-1] = 1;
	g[mid+4][mid+6] = 1;
	g[mid+4][mid+1] = 1;
	
	g[mid+3][mid-6] = 1;
	g[mid+3][mid-1] = 1;
	g[mid+3][mid+6] = 1;
	g[mid+3][mid+1] = 1;

	g[mid+2][mid-6] = 1;
	g[mid+2][mid-1] = 1;
	g[mid+2][mid+6] = 1;
	g[mid+2][mid+1] = 1;

	g[mid+1][mid-4] = 1;
	g[mid+1][mid-3] = 1;
	g[mid+1][mid-2] = 1;

	g[mid+1][mid+4] = 1;
	g[mid+1][mid+3] = 1;
	g[mid+1][mid+2] = 1;
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
	if (pattern_list == NULL) {
		fprintf(stderr, "get_pattern_list: calloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < len; i++) {
		pattern_list[i] = calloc(PBUF, sizeof(char));
		if (pattern_list[i] == NULL) {
			fprintf(stderr, "get_pattern_list: calloc failed\n");
			exit(EXIT_FAILURE);
		}
		strcpy(pattern_list[i], patterns[i].pattern_name);
	}
	return pattern_list;
}