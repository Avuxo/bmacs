CC=gcc
CFLAGS=-std=c99

main: bmacs.c
	$(CC) -o bmacs bmacs.c -std=gnu99 -lncurses -I.
