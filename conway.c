#include "grid.h"
#include "conway.h"

#define MAX 900 	// max amount of recursion
static int counter = 0;

// examine the eight surrounding cells of a certain cell
// return the number of living cells found
static int find_neighbors(int **g, int i, int j)
{
	int count = 0;

	int x, y;
	for (x = -1; x < 2; x++) {
		for (y = -1; y < 2; y++) {
			count += g[i+x][j+y];
		}
	}
	count -= g[i][j];
	return count;
}


// main conway algorithm (recursive)
void life(int **g, int size)
{
	int i, j, n;
	int **tmp;

    if (counter == MAX) {
        free_grid(g, size);
        return;
    }

	tmp = init_grid(size);

	n = 0;
	for (i = 1; i < size-1; i++) {
		for (j = 1; j < size-1; j++) {
			n = 0;
			n = find_neighbors(g, i, j);

			if (g[i][j] == 0 && n == 3) tmp[i][j] = 1;
			else if (g[i][j] == 1 && (n == 2 || n == 3)) tmp[i][j] = 1;
			else tmp[i][j] = 0;
		}
	}
    counter++;
	if (gridcmp(tmp, g, size)) {
        free_grid(tmp, size);
        free_grid(g, size);
		return;
	}
	free_grid(g, size);
	usleep(100000);
	print_grid(tmp, size);
	life(tmp, size);
}


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
