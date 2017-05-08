CC=gcc
CFLAGS=-std=c99
prefix=/usr/local

main: src/bmacs.c src/buffer.c src/interpreter.c
	$(CC) -o bin/bmacs src/bmacs.c src/buffer.c src/interpreter.c -std=gnu99 -lncurses -I.
