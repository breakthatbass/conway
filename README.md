# Conway's Game of Life
This is a visualization program of John Conway's [game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) algorithm that reads from [RLE pattern files](https://www.conwaylife.com/wiki/Run_Length_Encoded).

[![asciicast](https://asciinema.org/a/P2yzKujJdGBl7elAVQzrjDI1T.svg)](https://asciinema.org/a/P2yzKujJdGBl7elAVQzrjDI1T)

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


## Usage

```
usage: conway [ARG]

Conway takes one or no arguments.

Allowed arguments:
	file.rle	read a pattern in from a pattern file
	--random	run the algorithm with a random placement of cells
	--help	    output this message

if argument is not supplied, read from standard input

```

For quick usage simply run  
```
conway --random     # sets a starting grid with randomly places living cells
```
To use a pattern file, just include the `path/to/file.rle` as the argument
```
conway pattern_sheets/gun.rle   # there are a couple RLE files supplied in the repo
```
However, there are [thousands of RLE files out there](https://copy.sh/life/examples/) to use. You don't need to download them, you can just `curl` and pipe the files into `conway`. 
```
curl -s https://copy.sh/life/examples/rats.rle | conway
```
### note:
I haven't tested every available pattern so I can't guarantee they all work correctly. If you try out a pattern that causes a problem, open an issue. Or if you find an issue and want to contribute, I encourage you to open a pull request.