#ifndef __RLE_H__
#define __RLE_H__

#include <assert.h>
#include <string.h>

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

#endif