#include "bmacs.h"

int main(int argc, char **argv){
    if(argc < 2){ /*make sure that the user actually provided a file*/
        usage();
        return 1;
    }


    initscr(); /*start ncurses*/
    
    FILE *file;
    file = fopen(argv[1], "w+"); /*open up the file in the first command line argument*/

    //main program loop
    int exitFlag = 0;
    char buffer[512];
    do{
        //get the user inputed character
        noecho();
        int input = getch();
        
        if(strcmp(keyname(input), "^R") == 0){ //ctrl+r exits the program and saves
            //getstr(buffer);
            exitFlag = 1;
        }else if(strcmp(keyname(input), "^J") == 0){
            printw("\n");
            fputs("\n", file);
        }else if(strcmp(keyname(input), "^I") == 0){
            printw("\t");
            fputs("\t", file);
        }else if(strcmp(keyname(input), "^?") == 0){

        }else{
            //write key input to file 
            printw(keyname(input));
            fputs(keyname(input),file);
        }

        
    }while(exitFlag == 0);

    //fprintf(file, "%s", buffer);
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
