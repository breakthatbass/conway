#include <getopt.h>

#include "grid.h"
#include "patterns.h"
#include "conway.h"


void print_usage(void)
{
    size_t i, len;
    char **pattern_list;

    len = pattern_amt();
    pattern_list = get_pattern_list();

    printf("usage: conway [-s size, -p pattern]\n");
    printf("  available patterns:\n");

    for (i = 0; i < len; i++) {
        printf("\t- %s\n", pattern_list[i]);
        free(pattern_list[i]);
    }
    free(pattern_list);
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv)
{
    int opt;
    int **grid;
    char pattern[PBUF];
    int p = 0;      // flag to know if a pattern has been called
    int size = 20;  // default grid size 20x20

    // if no args, we default 20x20 grid with random pattern
    if (argc == 1) {
        grid = init_grid(size);
        random_pattern(grid, size);
        print_grid(grid, size);
        life(grid, size);
        exit(EXIT_SUCCESS);
    }

    
    while ((opt = getopt(argc, argv, "s:p:u")) != -1) {
        switch(opt) {
        case 's':
            size = atoi(optarg);
            break;
        case 'p':
            // a pattern has been selected
            p = 1;
            strcpy(pattern, optarg);
            break;
        case 'u':
            print_usage();
            break;
        default:
            print_usage();
            return 1;
        }
    }

    grid = init_grid(size);

    if (p) {
        if (pattern_check(pattern, grid, size) == 0) {
            fprintf(stderr, "%s: not a viable pattern\n\n", pattern);
            print_usage();
            exit(EXIT_FAILURE);
        }
    // if no pattern was selected we do random by default
    } else random_pattern(grid, size);

    print_grid(grid, size);
    life(grid, size);
    return 0;
}
