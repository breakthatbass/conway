#include <getopt.h>
#include <assert.h>

#include "grid.h"
#include "conway.h"
#include "rle.h"

#define BUF 4096

void print_usage(void)
{
    printf("usage: conway [FILE]\n");
    printf("Perform a visualization of Conway's game of life algorithm.\n");
    printf("\nConway takes one or no arguments.\n");
    printf("Allowed arguments:\n");
    printf("\tfile.rle\tread a pattern in from a pattern file\n");
    printf("\t--random\trun the algorithm with a random placement of cells\n");
    printf("\t--help\toutput this message\n");
    printf("if argument is not supplied, read from standard input\n");
}


int main(int argc, char **argv)
{
    struct rle_file f;
    FILE *fp;
    char buf[BUF];
    int **grid;
    int size = get_term_height();  // get current terminal height to use for grid

    // if no args, go with default  grid size with random pattern
    if (argc == 1) {
        fp = stdin;
        strcpy(buf, rle_string(fp));

    } else if (argc == 2) {
        printf("%s\n", argv[1]);

        if (strcmp(argv[1], "--help") == 0) {
            print_usage();
            exit(EXIT_SUCCESS);

        /* RLE FILE */
        } else if (strstr(argv[1], ".rle")) {
            fp = fopen(argv[1], "r");
            if (fp == NULL) {
                fprintf(stderr, "conway: not a valid RLE pattern file\n");
                exit(EXIT_FAILURE);
            }
            strcpy(buf, rle_string(fp));
            fclose(fp);

        /* RANDOM PATTERN */
        } else if (strcmp(argv[1], "--random") == 0) {
            grid = init_grid(size);
            random_pattern(grid, size);
            print_grid(grid, size);
            life(grid, size);
            exit(EXIT_SUCCESS);
        } else {
            print_usage();
            exit(EXIT_FAILURE);
        }
    
    } else {
        fprintf(stderr, "Illegal option %s\n", argv[2]);
        print_usage();
        exit(EXIT_FAILURE);
    }

    // parse what we need into f: grid size and encoded rle string
    rle_parse(buf, &f);
    if ((f.size+10) > size) size = f.size+10;

    grid = init_grid(size);
    load_grid(grid, f.rle, size);
    free(f.rle);

    /* run the algorithm */
    print_grid(grid, size);
    life(grid, size);

    return 0;
}
