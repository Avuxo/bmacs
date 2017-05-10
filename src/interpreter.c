/*
  Bmacs scripting language interpreter - designed to be used with the bmacs text editor
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "buffer.h"
#include "interpreter.h"

/*registers*/
int reg1 = 0; // $
int reg2 = 0; // &
char reg3 = '\0';// #


void loadScript(Buffer *buf, char *filename){
    printf("Loading %s...\n", filename);
    FILE *file = fopen(filename, "r");
    char *commands = malloc(sizeof(char) * MAXCMD);
    for(int i=0; i<MAXCMD; i++){
        fscanf(file, "%c", &commands[i]);
    }

    interpret(&(*buf), commands);
    free(commands);
}

/*interpret given command in given buffer*/
void interpret(Buffer *buf, char *commands){
    int commentFlag = 0; /*continue flag*/
    for(int i=0; i<strlen(commands); i++){
        /*check for comments - if comment start comment flag*/
        if(commands[i] == '~'){
            commentFlag = !commentFlag;
            continue;
        }
        /*if its a comment - keep going*/
        if(commentFlag){
            continue;
        }
        command(&(*buf), commands, i);

    }
}

/*execute command*/
void command(Buffer *buf, const char *cmd, int index){
    /*boolean -- does command have integer arguments?*/
    int hasInts = nextIsInt(cmd, index);
    /*check each char for command*/
    switch(cmd[index]){
    case '>': /*buffer move right x chars (where x is an integer)*/
        if(!hasInts){
            printf("Error, expected integer after '> (c:%d)\n", index);
            exit(1);
        }else{
            moveBufferRight(&(*buf), cmd[index+1] - '0');
            break;
        }
    case '<': /*buffer move left x chars (where x is an integer)*/
        if(!hasInts){
            printf("Error, expected integer after '<' (c: %d)\n", index);
            exit(1);
        }else{
            moveBufferLeft(&(*buf), cmd[index+1] -'0');
            break;
        }
    case '^': /*character insert*/
        /*using character register?*/
        if(cmd[index+1] == '#'){
            if(reg3 == '\0'){ /*terminator used in place of NULL*/
                printf("ERROR: Character register not set. (c: %d)", index);
                exit(1);
            }
            insert(&(*buf), reg3);
            break;
        }
        /*insert next character*/
        insert(&(*buf), cmd[index+1]);
        break;
    /*loop start*/
    case '[':{
        if(!hasInts){
            printf("Expected integer after '[ (c: %d)\n'", index);
            exit(1);
        }else{
            /*actual integer*/

            int numLoop = cmd[index+1] - '0';
            for(int i=1; i<numLoop; i++){
                int j=1;
                /*go until loop close*/
                while(cmd[index+j] != ']'){
                    command(&(*buf), cmd, index+j+1);
                    j++;
                }
            }
               
 
            break;
        }
    }
    /*log current buffer*/
    case '.':
        logBuffer(&(*buf));
        break;
    /*add to register (first arg)*/
    case '+':
        incrementReg(cmd[index+1]);
        break;
    /*subtract from register (first arg)*/
    case '-':
        decrementReg(cmd[index+1]);
        break;
    default:
        return;
    }
}


/*check how many integers are after given index*/
int nextIsInt(const char *cmd, int index){
    int offset = 0;
    /*0-9 + integer registers*/
    const char *integers = "0123456789$&";
    for(int i=0; i<strlen(integers); i++){
        if(cmd[index] == integers[i]){
            return 1; //TODO: recur to find number of integers after (for more than 1 digit)
        }
    }
    return 0;
}

/*check if the given index is a character*/
int nextIsChar(const char *cmd, int index){
    const char *alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i=0; i<strlen(alphabet); i++){
        if(cmd[index] == alphabet[i]){
            return 1;
        }
    }
    return 0;
}

/*increment register*/
void incrementReg(char reg){
    switch(reg){
    /*reg1*/
    case '$':
        if(reg1 < MAXREG) reg1++;
        return;
    /*reg 2*/
    case '&':
        if(reg2 < MAXREG) reg2++;
        return;
    default:
        return;
    }
}

/*decrement register*/
void decrementReg(char reg){
    switch(reg){
    /*reg1*/
    case '$':
        if(reg1 > 0) reg1--;
        return;
    /*reg2*/
    case '&':
        if(reg2 > 0) reg2--;
        return;
    default:
        return;
    }
}
