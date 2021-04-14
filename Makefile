CC=gcc
CFLAGS=-fsanitize=address -Wall -g
FILES=main.c grid.c patterns.c conway.c
BIN=conway

all: $(BIN)

$(BIN): $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(BIN)

install: $(BIN)
	mkdir -p /usr/local/bin
	cp $< /usr/local/bin/$(BIN)

uninstall: $(BIN)
	rm /usr/local/bin/$(BIN)
	rm -rf ~/.xmas

clean:
	rm $(BIN)
	rm -rf *.dSYM