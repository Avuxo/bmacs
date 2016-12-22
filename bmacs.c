#include "bmacs.h"

int main(int argc, char **argv){
    if(argc < 2){ /*make sure that the user actually provided a file*/
        usage();
        return 1;
    }


    initscr(); /*start ncurses*/
    
    FILE *file;
    file = fopen(argv[1], "w"); /*open up the file in the first command line argument*/

    //main program loop
    int exitFlag = 0;
    do{
        //get the user inputed character
        int input = getch();
        
        if(strcmp(keyname(input), "^R") == 0){ //ctrl+r exits the program and saves
            exitFlag = 1;
        }
        
    }while(exitFlag == 0);

    fprintf(file,"test"); /*write to the file specified in argv[1]*/
    fclose(file);         /*close the file output stream*/
    endwin();           /*exit ncurses*/
    return 0;
}

void usage(void){
    printf("Error, usage: bmacs <filename> <options>\n");
    return;
}

/*
  bmacs version 0.1
  https://github.com/asonskii/bmacs.git
*/
