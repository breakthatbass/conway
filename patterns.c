#include "patterns.h"


struct pattern patterns[] = {
    {"random", random_pattern},
    {"glider", glider},
	{"blinker", blinker}
};
size_t pattern_amt() {return sizeof (patterns)/sizeof (struct pattern);}

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