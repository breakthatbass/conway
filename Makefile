CC=gcc
CFLAGS=-fsanitize=address -Wall -g
FILES=main.c grid.c patterns.c conway.c rle.c
BIN=conway
# get the os
UNAME_S := $(shell uname)

all: $(BIN)

$(BIN): $(FILES)
	$(CC) $(FILES) $(CFLAGS) -o $(BIN)

install: $(BIN)
	mkdir -p /usr/local/bin
ifeq ($(UNAME_S), Linux)
	sudo cp $< /usr/local/bin/$(BIN)
else
	cp $< /usr/local/bin/$(BIN)
endif

uninstall: $(BIN)
	rm /usr/local/bin/$(BIN)
	rm -rf ~/.xmas

clean:
	rm $(BIN)
	rm -rf *.dSYM
