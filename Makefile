CC=gcc
CFLAGS=-std=c99
prefix=/usr/local

main: bmacs.c
	$(CC) -o bin/bmacs bmacs.c buffer.c  -std=gnu99 -lncurses -I.
