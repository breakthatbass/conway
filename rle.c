#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "rle.h"
#include "grid.h"

#define BUF 4096

/*
* rle_parse:
* parse a string containing RLE pattern data and store info in the rle_file struct
*
* user must free the pattern string (f.rle) after
*/
void rle_parse(char *s, struct rle_file *f)
{
    int h, w;
    char buf[BUF];
    int IGNORE = 0;

    /*
    if (s[0] != '#' && s[1] != 'N') {
        fprintf(stderr, "conway: rle_parse: not a valid RLE pattern file\n");
        exit(EXIT_FAILURE);
    }
    */

    while (*s) {
        
        if (*s == '#') { // in a comment line
            IGNORE = 1;
        } else if (*s == '\n') {  // done with comment line
            IGNORE = 0;
        } else if (*s == 'x' && !IGNORE) {
			// get size
            strcpy(buf, strtok(s, "\n"));
            sscanf(buf, "x = %d, y = %d", &h, &w);
			// conway uses a square grid so we take the largest of h and w
            if (h > w) f->size = h;
            else f->size = w;
            memset(buf, 0, 1024);

			// copy the rle directions
            strcpy(buf, strtok(NULL, "!"));
            f->rle = malloc(sizeof(char)*strlen(buf)+1);
            if (f->rle == NULL) {
                fprintf(stderr, "rle_parse: malloc failed\n");
                exit(EXIT_FAILURE);
            }
            strcpy(f->rle, buf);
        }
        s++;
    }
}


/*
 * rle_decode:
 *
 * decpompress one line of an encoded string
 * returns the decompressed string
 * 
 * note: user must free returned string
 *
 * example: 2bo3ob
 * return: bboooob
 */
static char *rle_decode(char *s)
{
    int count, i, j;
    char prev;
    char *decode;

    decode = malloc(sizeof(char)*strlen(s)*10);
    if (decode == NULL) {
        fprintf(stderr, "rle_decode: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    count = 1;
    j = 0;
    while (*s) {
        if (*s == 'b') {
            for (i = 0; i < count; i++) 
                decode[j++] = 'b';
            count = 1;
        }
        else if (*s == 'o') {
            for (i = 0; i < count; i++)
                decode[j++] = 'o';
            count = 1;
        } 
        else if (isdigit(*s)) {
            if (isdigit(prev)) {
                count = (count*10)+(*s-'0');
            }
            else count = *s-'0';
        }
        prev = *s;
        s++;
    }
    decode[j] = '\0';
    return decode;
}


/*
 * load_grid:
 *
 * takes the grid and the entire pattern string containing multiple lines
 * it breaks the string into tokens based on '$', decompresses it, and loads it
 * into the grid.
 */
void load_grid(int **g, char *pattern, int size)
{
    char *line;
    char *p;
    int col = size/3; // add an edge buffer

    int row = size/3;

    line = strtok(pattern, "$");
    while (line != NULL) {
        col = size/3;
        p = rle_decode(line);
        for (int i = 0; i < strlen(p); i++) {
            if (p[i] == 'o') g[row][col++] = 1;
            else col++;
        }
        row++;
        free(p);
        line = strtok(NULL, "$");
    }
}




char *rle_string(FILE *fp)
{
    static char buf[BUF];
    char c;
    int i;

    i = 0;
    while ((c = fgetc(fp)) != EOF)
        buf[i++] = c;
    buf[i] = '\0';

    return buf;
}