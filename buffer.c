#include "buffer.h"

/*
  Declaration of the Gap Buffer structure, this is the primary data structure
  used by bmacs.
*/

struct gapBuffer{
    char *buf;
    int   size;
    
};

/*MOVEMENT FUNCTIONS*/
void stepForward(void){
    int y,x; //store the cursor pos here
    getyx(curscr, y, x);
    move(y, x+1);
}
