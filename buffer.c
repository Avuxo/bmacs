#include "buffer.h"
#include <strings.h>
/*
  functions for use by the 'gap buffer' data type, implemented for the storage and manipulation of text in the bmacs editor
*/

/*MOVEMENT FUNCTIONS*/

//step the cursor forward one character
void stepForward(struct gapBuffer buffer){
    int y,x; //store the cursor pos here
    getyx(curscr, y, x); //get current curosr pos
    move(y, x+1); //moves to the next position
}

//step the cursor back one character
void stepBackward(struct gapBuffer buffer){
    int y,x; //store the cursor pos her
    getyx(curscr, y, x);
    move(y, x-1);//move back
}

//insert a character into the buffer
void insertChar(struct gapBuffer buffer, char insert){
    *(buffer.gapStart+1) = insert; //set the next char to be the inserted char
    return;
};

//get the size of the buffer
size_t buffer_size(struct gapBuffer buffer){
    return  ((sizeof(buffer.start))    +
             (sizeof(buffer.gapStart)) +
             (sizeof(buffer.gapEnd))   +
             (sizeof(buffer.end)));
}


//get the full buffer as a string
char *getBuffer(struct gapBuffer buffer){
    char fullBuffer[buffer_size(buffer) + 1]; //string sized for the file
    
    strcpy(fullBuffer, buffer.start);
    strcpy(fullBuffer, buffer.gapStart);
    strcpy(fullBuffer, buffer.gapEnd);
    strcpy(fullBuffer, buffer.end);
    
    return fullBuffer;
}
