#include <ncurses.h>

 
typedef struct {
    char  *start;                                                                
    char  *gap;                                                             
    size_t size; //total size
    int bufSize;
    void (*insert)(char insert);
    void (*allocate)(void);
    void (*reallocate)(void);
} GapBuffer;   

//step the cursor forward one character
void stepForward(GapBuffer buffer);

//step the cursor back one character
void stepBackward(GapBuffer buffer);

//insert a character into the buffer
void insertChar(GapBuffer buffer, char insert);

//get the size of the buffer
size_t buffer_size(GapBuffer buffer);

//reallocate buffer 
void realocateBuffer(size_t size, GapBuffer buffer);

//get the buffer as a string
char *getBuffer(GapBuffer buffer);

//get the ammount of the buffer that is visible on the screen
char *getVisibleBuffer(GapBuffer buffer);

//initial allocation
void allocateBuffer(GapBuffer buffer, size_t filesize);

//moveGap
void moveGap(GapBuffer buffer, int point);

void buffer(GapBuffer buffer);
