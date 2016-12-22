#include "bmacs.h"

int main(int argc, char **argv){
    if(argc < 2){ /*make sure that the user actually provided a file*/
        usage();
        return 1;
    }


    initscr();
    getch();
    char str[512];
    

    FILE *fp;
    fp = fopen(argv[1], "w");

    while(1){
        int ch = getch();

        if(strcmp(keyname(ch), "^R") == 0){ //ctrl+r exits the program and saves
            break;
        }

        printw("%s", keyname(ch));
        
    }
    fclose(fp);
    endwin();
    return 0;
}

void usage(void){
    printf("Error, usage: bmacs <filename> <options>\n");
    return;
}

/*
  bmacs version 0.1
  https://github.com/asonskii/bmacs

*/
