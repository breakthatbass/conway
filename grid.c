#include "grid.h"

//void init_grid(int *grid, int size)
int **init_grid(int size)
{
    int i;
    int **grid;
    grid = calloc(size, sizeof(int*));
    for (i = 0; i < size; i++) {
        grid[i] = calloc(size, sizeof(int));
        assert(grid[i]);
    }
    assert(grid);
    return grid;
}


void free_grid(int **grid, int size)
{
    int i;
    for (i = 0; i < size; i++)
        free(grid[i]);
    free(grid);
}


void print_grid(int **g, int size)
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (g[i][j] == 1) printf("# ");
            else printf("  ");
		}
		printf("\n");
	}
}

// compare towo 2d arrays
int gridcmp(int **src1, int **src2, int size)
{
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (src1[i][j] != src2[i][j])
				return 0;
		}
	}
	return 1;
}