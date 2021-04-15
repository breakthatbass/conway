#include <getopt.h>

#include "grid.h"
#include "patterns.h"
#include "conway.h"

#define PBUF 45

int main(int argc, char **argv)
{
    int opt;
    int **grid;
    char pattern[PBUF];
    int p = 0; // flag to know if a pattern has been called
    int size = 20;

    // if no args, we default 20x20 grid with random pattern
    if (argc == 1) {
        grid = init_grid(size);
        random_pattern(grid, size);
        print_grid(grid, size);
        life(grid, size);
        exit(EXIT_SUCCESS);
    }

    
    while ((opt = getopt(argc, argv, "s:p:")) != -1) {
        switch(opt) {
        case 's':
            size = atoi(optarg);
            break;
        case 'p':
            // a pattern has been selected
            p = 1;
            strcpy(pattern, optarg);
            break;
        default:
            // print_usage();
            return 1;
        }
    }

    grid = init_grid(size);

    if (p) {
        if (pattern_check(pattern, grid, size) == 0) {
            fprintf(stderr, "%s: not a viable pattern\n", pattern);
            exit(EXIT_FAILURE);
        }
    // if no pattern was selected we do random by default
    } else random_pattern(grid, size);

    print_grid(grid, size);
    life(grid, size);
    return 0;
}
