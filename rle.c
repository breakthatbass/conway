#include "rle.h"

/*
* rle_parse:
* parse a string containing RLE pattern data and store info in the rle_file struct
*
* user must free the pattern string (f.rle) after
*/
void rle_parse(char *s, struct rle_file *f)
{
    int h, w;
    char buf[1024];
    int IGNORE = 0;

    while (*s) {
        
        if (*s == '#') { // in a comment line
            IGNORE = 1;
        } else if (*s == '\n') {  // done with comment line
            IGNORE = 0;
        } else if (*s == 'x' && !IGNORE) {
            strcpy(buf, strtok(s, "\n"));
            sscanf(buf, "x = %d, y = %d", &h, &w);
            if (h > w) f->size = h;
            else f->size = w;
            memset(buf, 0, 1024);
            strcpy(buf, strtok(NULL, "!"));
            f->rle = malloc(sizeof(char)*strlen(buf)+1);
            assert(f->rle);
            strcpy(f->rle, buf);
        }
        s++;
    }
}
