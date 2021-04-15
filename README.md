# Conway's Game of Life
This is a visualization program of John Conway's [game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) algorithm. It's one of my favorite algorthms and it's super cool to watch it in action. I chose to do do mine recursively.

The algorithm is a [celluar automation](https://en.wikipedia.org/wiki/Cellular_automaton) where each cell in the grid either comes to "life" or "dies" or stays as it is based on the status of the eight surrounding cells. 

The rules:  
1. a living cell with 2 or 3 living neighbors stays alive.
2. a dead cell with three lving neighbors comes to life.
3. Everything else either dies or stays dead.

The rules are applied to every cell in the grid over and over. Watching a visualization makes it seem like things happen at random, however, things happen based on the original status of cells in the grid.  

It's a game that plays itself. The only thing you do is set the starting grid.



## Installation
```
git clone https://github.com/breakthatbass/conway.git
cd conway
make install
```

## Uninstall
```
cd conway
make uninstall
```

## Usage
```
conway [-s <size> -p <pattern>]
```
The default size is a grid of 20 cells high and 20 cells wide.  
The default pattern is just a random placement of living cells at the start.  
The default can be run simply with:
```
conway      # run with defaults
```
## Available start patterns
Right now there are only three available starting patterns built into this program:
- random
- glider
- blinker

[other pattern examples](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Examples_of_patterns) that i'll eventually add.


## Adding your more start patterns
The program is built to easily add more patterns and without having to change any existing code.  
Everything is done in the [`patterns.c`](https://github.com/breakthatbass/conway/blob/main/patterns.c) file.  

If you'd like to contribute your own patterns, that would be awesome.

#### **Step 1:**

Here's what the glider pattern function looks like and it can be used as a template:
```c
void glider(int **g, int size)
{
	/************
	 * . . . . . 
	 * . . . # .
	 * . # . # .
	 * . . # # .
	 * . . . . .
	 * *********/

	int mid = size/2;

	g[mid-1][mid+1] = 1;
	g[mid][mid+1] = 1;
	g[mid+1][mid+1] = 1;
	g[mid+1][mid] = 1;
	g[mid][mid-1] = 1;
}
```
All pattern function need to take two arguments: the grid and the size which are handled in the `main` function.  
Keep the `int mid = size/2` as that will place the pattern in the middle of the grid.  
Build your grid with 1s as the grid is filled with zeros denoting dead cells.  

#### **Step 2:**
Add to the list in the patterns struct.
```c
struct pattern patterns[] = {
    {"random", random_pattern},
    {"glider", glider},
    {"blinker", blinker},
};
```
Put the name of the pattern on the left and the function name on the right in a new set of brackets.

#### **Step 3:**
Add the function prototype to [`patterns.h`](https://github.com/breakthatbass/conway/blob/main/patterns.h)  

...And you're good to go. It will automatically be added to the usage display and it will be recognized when used as an argumant with the `-p` flag.

## Contributing
Contributions are very much welcomed.  
If you'd like to contribute a pattern follow the steps above for adding patterns. If you find bugs, you can raise an issue or fix it too.

## TODO
1. add more starting patterns