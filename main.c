#include "grid.h"
#include "patterns.h"
#include "conway.h"

int main(int argc, char **argv)
{
    int size;
    int **grid;

    if (argc != 2) {
        size = 20;
    } else {
        size = atoi(argv[1]);
    }

    grid = init_grid(size);
    random_pattern(grid, size);
    print_grid(grid, size);
    life(grid, size);
    return 0;
}
