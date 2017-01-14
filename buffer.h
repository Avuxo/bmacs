#include <ncurses.h>

 
struct gapBuffer{
    char  *start;                                                                
    char  *gapStart;                                                             
    char  *gapEnd;
    char  *end;
    size_t size; //total size
    
};   

//step the cursor forward one character
void stepForward(struct gapBuffer buffer);

//step the cursor back one character
void stepBackward(struct gapBuffer buffer);

//insert a character into the buffer
void insertChar(struct gapBuffer buffer, char insert);


char *getBuffer(struct gapBuffer buffer);
