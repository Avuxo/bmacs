#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "buffer.h"
#include "interpreter.h"

void insert(Buffer *buf, char insert){
    /*ensure there is space for insertion*/
    if(buf->insert == buf->b2){
        reallocate(&(*buf));
    }
    *buf->insert++ = insert; /*next char after pointer is inserted*/
}

/*:angery:*/
void moveBufferRight(Buffer *buf, unsigned int pos){
    /*move pre-existing chars*/
    memmove((buf->b2), (buf->b2+pos), (pos));
    /*move chars to the left of the buffer*/
    memmove((buf->b1 + strlen(buf->b1)),
            (buf->b2),
            (pos));
    
    buf->insert = (buf->b1+strlen(buf->b1));
}

/*if insert > pos -> left; if insert < pos -> right(or the other way, im tired)*/
void moveBufferLeft(Buffer *buf, unsigned int pos){
    /*move preexisting characters to make space*/
    memmove((buf->b2 + pos), (buf->b2), (pos));
    /*move chars to the right of the buffer*/
    memmove((buf->b2),
            (buf->b1 + pos),
            (strlen(buf->b1) + pos));
    /*move insertion pointer*/
    buf->insert = (buf->b1+pos);
}

/*return the buffer (without invisible portion)*/
char *getBuffer(Buffer *buf){
    /*return string*/
    char *ret = malloc(sizeof(buf->b1) + sizeof(buf->b2) + 1);
    /*to the right -- I dont think this case is ever actually reached...*/
    if(buf->insert < buf->b2){
        /*Temporary buffer*/
        char *temp = malloc(sizeof(char) * sizeof(buf->b1));
        /*size of the gap*/
        int gapSize = buf->insert - buf->b1;

        printf("size: %d\n", gapSize);
        /*copy the visible array into the temporary buffer*/
        memcpy(temp, (buf->b1), gapSize);
        
        sprintf(ret, "%s%s\0", temp, buf->b2); /*write return value*/
        free(temp);
        return ret;
    /*Unknown Error case*/
    }else{
        /*temporary*/
        printf("unknown buffer error\n");
        exit(1);
        return "UNKWN BUFFER ERROR";
    }
}

/*log the buffer*/
void logBuffer(Buffer *buf){
    /*split up string*/
    char *b1_tmp = malloc(sizeof(buf->b1));
    char *gap_tmp = malloc(sizeof(buf->b1));
    memcpy(b1_tmp, (buf->b1), buf->insert - buf->b1);
    memcpy(gap_tmp, (buf->b1 + (buf->insert-buf->b1)), 4);
    
    printf("\nAddress: b1:%d b2:%d", &(buf->b1), &(buf->b2));
    printf("\n--Gap--\n%s[%s]%s\n-------\n", b1_tmp, gap_tmp, buf->b2);
    
    //free(b1_tmp);
    //free(gap_tmp);
}

/*reallocate buffer once space runs out*/
void reallocate(Buffer *buf){
    printf("Out of memory\n TODO: reallocate memory.\n");
    exit(1);
}


/*allocate the buffer and configure the pointers*/
void allocate(Buffer *buf){
    buf->b1Len = 0;
    buf->b2Len = 0;
    /*allocate first buffer fragment*/
    buf->b1 = malloc(sizeof(char) * 64);
    buf->insert = (buf->b1 + buf->b1Len);
    buf->b2 = malloc(sizeof(char) * 64);
}

