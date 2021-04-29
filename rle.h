#ifndef __RLE_H__
#define __RLE_H__

#include <assert.h>
#include <string.h>
#include <ctype.h>

struct rle_file {
    int size;
    char *rle;
};

/*
* rle_parse:
* parse a string containing RLE pattern data and store info in the rle_file struct
*
* user must free the pattern string (f.rle) after
*/
void rle_parse(char *s, struct rle_file *f);


/*
 * load_grid:
 *
 * takes the grid and the entire pattern string containing multiple lines
 * it breaks the string into tokens based on '$', decompresses it, and loads it
 * into the grid.
 */
void load_grid(int **g, char *pattern)

#endif
