#include "buffer.h"
/*
  functions for use by the 'gap buffer' data type, implemented for the storage and manipulation of text in the bmacs editor
*/

/*MOVEMENT FUNCTIONS*/

//step the cursor forward one character
void stepForward(struct gapBuffer buffer){
    int y,x; //store the cursor pos here
    getyx(curscr, y, x);
    printw("%d,%d", x, y);
    move(y, x+1); //moves to the next position
}

//step the cursor back one character
void stepBackward(struct gapBuffer buffer){
    int y,x; //store the cursor pos her
    getyx(curscr, y, x);
    move(y, x-1);
}

//insert a character into the buffer
void insertChar(struct gapBuffer buffer, char insert){
    (*buffer.gapStart++) = insert; //set the next char to be the inserted char
    return;
};

char *getBuffer(struct gapBuffer buffer){
    return "";
}
