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
char reg4 = '\0';

/*current index*/
int currentCommand = 0;

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
    for(currentCommand=0; currentCommand<strlen(commands); currentCommand++){
        /*check for comments - if comment start comment flag*/
        if(commands[currentCommand] == '~'){
            commentFlag = !commentFlag;
            continue;
        }
        /*if its a comment - keep going*/
        if(commentFlag){
            continue;
        }
        command(&(*buf), commands, currentCommand);

    }
}

/*execute command*/
void command(Buffer *buf, const char *cmd, int index){
    /*boolean -- does command have integer arguments?*/
    int hasInts = nextIsInt(cmd, index);
    /*check each char for command*/
    switch(cmd[index]){
    case '>': /*buffer move right x chars (where x is an integer)*/
        if(!nextIsInt(cmd, index+1)){
            printf("Error, expected integer after '> (c:%d)\n", index);
            exit(1);
        }else{
            if(!nextIsRegister(cmd, index)){
                moveBufferRight(&(*buf), cmd[index+1] - '0');
                break;
            }else if(cmd[index+1] == '$'){
                moveBufferLeft(&(*buf), reg1);
                break;
            }else if(cmd[index+1] == '&'){
                moveBufferLeft(&(*buf), reg2);
                break;
            }
        }
    case '<': /*buffer move left x chars (where x is an integer)*/
        if(!nextIsInt(cmd, index+1)){
            printf("Error, expected integer after '<' (c: %d)\n", index);
            exit(1);
        }else{
            if(nextIsRegister(cmd, index) == 0){
                moveBufferLeft(&(*buf), cmd[index+1] -'0');
                break;
            }else if(cmd[index+1] == '$'){
                moveBufferLeft(&(*buf), reg1);
                break;
            } else if(cmd[index+1] == '&'){
                moveBufferLeft(&(*buf), reg2);
                break;
            }else{
                printf("unknown error\n");
                break;
            }
        }
    case '!':
        printf("TODO: deleting characters\n");
        break;
    case '^': /*character insert*/
        /*using character register?*/
        if(cmd[index+1] == 0x5c && cmd[index+2] == '#'){
            printf("%c\n", reg3);
            if(reg3 == '\0'){ /*terminator used in place of NULL*/
                printf("ERROR: Character register not set. (c: %d)\n", index);
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
        if(!nextIsInt(cmd,index+1)){
            printf("Expected integer or register after '[' (c: %d)\n", index);
            exit(1);
        }else{
            int numLoop;
            /*actual integer*/
            if(nextIsInt(cmd, index+1) && cmd[index+1] != '$' && cmd[index+1] != '&')
                numLoop = cmd[index+1] - '0';
            else if(nextIsRegister(cmd, index) == 1){
                if(cmd[index+1] == '$') numLoop = reg1;
                else if(cmd[index+1] == '&') numLoop = reg2;
            }
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
    case '=':
        /*integer register?*/
        if(nextIsRegister(cmd, index) == 1){
            /*is the next character after the register an integer?*/
            if(nextIsInt(cmd, index+1)){
                setIntRegister(cmd[index+1], cmd[index+2] - '0');
                break;
            }else{
                break;
            }
        /*char register?*/
        }else if(nextIsRegister(cmd, index) == 2){
            /*is the next character after the register a character*/
            if(nextIsChar(cmd, index)){
                printf("point 1\n");
                setCharRegister(cmd[index+1], cmd[index+2]);
                break;
            }else{
                break;
            }
        }else{
            break;
        }
    /*conditionals*/
    case '{':
        
        /*integer register*/
        if(nextIsRegister(cmd, index) == 1){
            /*the two conditional values*/
            int compareTo;
            int comparison;
            
            if(cmd[index+1] == '$') compareTo = reg1;
            else if(cmd[index+1] == '&') compareTo = reg2;
            if(nextIsRegister(cmd, index+1) == 1){                
                if(cmd[index+2] == '$') comparison = reg1;
                else if(cmd[index+2] == '&') comparison = reg2;
            }else if(nextIsInt(cmd, index+1)){
                /*convert to int*/
                comparison = cmd[index+2] - '0';
            }else break;
            /*actual comparison*/
            if(comparison == compareTo){
                break;
            }else{
                currentCommand = findExitBrace(1, cmd, index);
            }
        /*char register*/    
        }else if(nextIsRegister(cmd, index) == 2){
            char compareTo;
            char comparison;
            if(cmd[index+1] == '#') compareTo = reg3;
            if(cmd[index+1] == '%') compareTo = reg4;
            if(nextIsRegister(cmd, index+1) == 2){
                if(cmd[index+1] == '#') comparison = reg3;
                if(cmd[index+1] == '%') comparison = reg4;
            }else if(nextIsChar(cmd, index)){
                comparison = cmd[index+2];
            }else break;

            /*actual comparison*/
            if(compareTo == comparison){
                break;
            }else{
                currentCommand = findExitBrace(1, cmd, index);
            }
        }else{
            printf("Expected integer or register after '{' (c: %d)\n", index);
            exit(1);
        }
    default:
        return;
    }
}

/*
  1 for curly 0 for square
  Find the exit brace given an open brace
  TODO: implement nesting
*/
int findExitBrace(unsigned int type, const char *cmd, int index){
    if(type){
        for(int i=1; i<strlen(cmd); i++){
            if(cmd[index+i] == '}'){
                return index+i;
            }
        }
        return 0;
    }else if(!type){
        for(int i=1; i<strlen(cmd); i++){
            if(cmd[index+i] == ']'){
                return index+i;
            }
        }
        return 0;
    }else{
        return 0;
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
    /*all ascii characters*/
    const char *alphabet = "abcdefghijklmnopqrstuvwxyz 123456789`!@#$%^&*()_+-={}[];':]\",.<>/?";
    for(int i=0; i<strlen(alphabet); i++){
        if(cmd[index+2] == alphabet[i]){
            return 1;
        }
    }
    return 0;
}

/*returns 1 for integer register, 2 for char register, and 0 for not register*/
int nextIsRegister(const char *cmd, int index){
    const char *intRegisters = "$&";
    const char *charRegisters = "#";
    for(int i=0; i<strlen(intRegisters); i++){
        if(cmd[index+1] == intRegisters[i]){
            return 1;
        }
    }
    for(int i=0; i<strlen(charRegisters); i++){
        if(cmd[index+1] == charRegisters[i]){
            return 2;
        }
    }
    return 0;
}

/*set given register to the given value (integer type)*/
void setIntRegister(char reg, int value){
    printf("reg: %c, val: %d\n", reg, value);
    if(reg != '$' && reg != '&') return;
    else if(reg == '$') reg1 = value;
    else if(reg == '&') reg2 = value;
}
/*set given register to the given value (char type)*/
void setCharRegister(char reg, char value){
    if(reg != '#') return;
    reg3 = value;
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
