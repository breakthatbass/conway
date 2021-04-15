#ifndef __PATTERNS_H__
#define __PATTERNS_H__


#define PBUF 45

// struct to associate a name with a function
// for easier calling of different patterns
struct pattern {
	char *pattern_name;
	void (*f)(int **grid, int size);
};


// check if a pattern is in the list of patterns
int pattern_check(char *pattern, int **grid, int size);

// return the number of patterns in the struct. for use with looping through the list
size_t pattern_amt(void);

// get the current list of pattern names and place them in an array
// user must free
char **get_pattern_list(void);


/*******************************************************/
/*	PATTERN PROTOTYPES								   */
/*******************************************************/

// fills the grid randomly with 1s for a random pattern to start with
void random_pattern(int **grid, int size);

void glider(int **g, int size);

void blinker(int **g, int size);

void pulsar(int **g, int size);

#endif