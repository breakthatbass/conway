#ifndef __RLE_H__
#define __RLE_H__


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
void load_grid(int **g, char *pattern, int size);

/*
* rle_string:
*
* read an RLE file into a string and return it
*/
char *rle_string(char *file);

#endif
