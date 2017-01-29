#include "buffer.h"
#include <strings.h>
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
    *(buffer.gapStart+1) = insert; //set the next char to be the inserted char
    return;
};

//get the size of the buffer
size_t buffer_size(GapBuffer buffer){
    return  ((sizeof(buffer.start))    +
             (sizeof(buffer.gapStart)) +
             (sizeof(buffer.end)));
}

