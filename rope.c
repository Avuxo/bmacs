#include "rope.h"

struct Rope{
    char *data;
    struct Rope *left;
    struct Rope *right;
};

//get the string that the buffer is holding
char *getString(struct Rope *start){
    return "test";
}

