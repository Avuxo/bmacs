typedef struct{
    /*first buffer fragment*/
    char *b1;
    int b1Len;
    char *insert;
    /*second buffer fragment*/
    char *b2;
    int b2Len;
} Buffer;



void allocate(Buffer *buf);
void insert(Buffer *buf, char ins);
char *getBuffer(Buffer *buf);
void reallocate(Buffer *buf);
void moveBufferLeft(Buffer *buf, unsigned int position);
void moveBufferRight(Buffer *buf, unsigned int position);
void logBuffer(Buffer *buf);
