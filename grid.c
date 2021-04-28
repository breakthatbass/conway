#include <sys/ioctl.h>
#include <unistd.h>

#include "grid.h"


// get current height of terminal to use for grid sizing
int get_term_height()
{
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_row;
}


// allocate space for a grid based on size
int **init_grid(int size)
{
    int i;
    int **grid;
    grid = calloc(size, sizeof(int*));
	if (grid == NULL) {
		fprintf(stderr, "init_grid: calloc problem\n");
		exit(EXIT_FAILURE);
	}

    for (i = 0; i < size; i++) {
        grid[i] = calloc(size, sizeof(int));
        if (grid[i] == NULL) {
			fprintf(stderr, "init_grid: calloc problem\n");
			exit(EXIT_FAILURE);
		}
    }
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


// compare two 2d arrays
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
