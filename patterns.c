#include "patterns.h"

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

