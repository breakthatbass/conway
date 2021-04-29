#include <getopt.h>
#include <assert.h>

#include "grid.h"
#include "patterns.h"
#include "conway.h"
#include "rle.h"


void print_usage(void)
{
    size_t i, len;
    char **pattern_list;

    len = pattern_amt();
    pattern_list = get_pattern_list();

    printf("usage: conway [ -u, -f <file.rle> -p <pattern> ]\n");
    printf("  available built in patterns:\n");

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
    int f = 0;      // flag to know if a RLE file format pattern has been provided
    int size = get_term_height();  // get current terminal height to use for grid

    // if no args, go with default  grid size with random pattern
    if (argc == 1) {
        grid = init_grid(size);
        random_pattern(grid, size);
        print_grid(grid, size);
        life(grid, size);
        exit(EXIT_SUCCESS);
    }

    
    while ((opt = getopt(argc, argv, "p:f:u")) != -1) {
        switch(opt) {
        case 'p':
            // a pattern has been selected
            p = 1;
            strcpy(pattern, optarg);
            break;
        case 'f':
            // rle file selected
            f = 1;
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
        // pattern has been supplied. check if it is in the list of available patterns
        if (pattern_check(pattern, grid, size) == 0) {
            fprintf(stderr, "%s: not a viable pattern\n\n", pattern);
            print_usage();
            exit(EXIT_FAILURE);
        }
    }
    else if (f) {
        // file
        struct rle_file f;
        char buf[1024];

        // read file into buf...if file is an an rle file
        strcpy(buf, rle_string(pattern));

        // parse what we need into f: grid size and encoded rle string
        rle_parse(buf, &f);
        if ((f.size+10) > size) size = f.size+10;

        grid = init_grid(size);
        load_grid(grid, f.rle, size);
        free(f.rle);
    } 
    // if no pattern was selected we do random by default
    else random_pattern(grid, size);

    print_grid(grid, size);
    life(grid, size);
    return 0;
}
