#include <ncurses.h>

 
typedef struct {
    char  *start;                                                                
    char  *gapStart;                                                             
    char  *end;
    size_t size; //total size
    char *point;
    
} GapBuffer;   

//step the cursor forward one character
void stepForward(GapBuffer buffer);

//step the cursor back one character
void stepBackward(GapBuffer buffer);

//insert a character into the buffer
void insertChar(GapBuffer buffer, char insert);

//get the size of the buffer
size_t buffer_size(GapBuffer buffer);

//get the full buffer as a string
char *getBuffer(GapBuffer buffer);

void moveGap(GapBuffer buffer, int point);

int copyBytes(char *dest, char *src, unsigned int len);
