#include "buffer.h"
#include <strings.h>
#include <stdlib.h>

/*
  functions for use by the 'gap buffer' data type, implemented for the storage and manipulation of text in the bmacs editor
*/

/*MOVEMENT FUNCTIONS*/

//step the cursor forward one character
void stepForward(GapBuffer buffer){
    int y,x; //store the cursor pos here
    getyx(curscr, y, x); //get current curosr pos
    move(y, x+1); //moves to the next position
}

//step the cursor back one character
void stepBackward(GapBuffer buffer){
    int y,x; //store the cursor pos her
    getyx(curscr, y, x);
    move(y, x-1);//move back
}

//insert a character into the buffer
void insertChar(GapBuffer buffer, char insert){ 
    buffer.gap++;
    buffer.gap = insert;
}

void allocateBuffer(GapBuffer buffer, size_t filesize){
    size_t size = (sizeof(char) * (filesize + 1)) +
        (sizeof(char) * 10000);
    buffer.start = malloc(size);
}


void reallocateBuffer(size_t size, GapBuffer buffer){
    buffer.gap = malloc(sizeof(char) * size);
}


//get the size of the buffer
size_t buffer_size(GapBuffer buffer){
    size_t buffer_size =
        (sizeof(buffer.start))+
        (sizeof(buffer.gap));
    return buffer_size;
}

char *getBuffer(GapBuffer buffer){
    return buffer.start;
}

void buffer(GapBuffer buffer){
    return;
}
