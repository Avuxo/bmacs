#include "bmacs.h"
#include "buffer.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
  bmacs text editor, written to be a lightweight gap buffer-based text editor for use on UNIX/BSD based operating system, with the only main library used being ncurses.
*/


int main(int argc, char **argv){
    if(argc < 2){ /*make sure that the user actually provided a file*/
        usage();
        return 1;
    }
    
    initscr(); /*start ncurses*/
    
    FILE *write;
    FILE *read;
    write = fopen(argv[1], "w");
    read = fopen(argv[1], "r"); //open the first command line argument
    
    GapBuffer buffer;
    
    //initialiation of the buffer (temporary)
    struct stat *thing = malloc(sizeof(struct stat));
    stat(argv[1], thing);
    size_t size = thing->st_size;

    //allocate the buffer
    allocateBuffer(buffer,size);

    //GUI stuff
    drawLine(argv[1]);

    /*main program loop*/
    int exitFlag = 0;
    do{
        //get the user inputed character
        noecho();
        int input = getch();
        
        if(strcmp(keyname(input), "^R") == 0){ //ctrl+r exits program(save)
            exitFlag = 1;
        }else if(strcmp(keyname(input), "^?") == 0){ //backspc pressed
            stepBackward(buffer);
        }else{ //write key input out
            stepForward(buffer);
            printw(keyname(input));
            insertChar(buffer, input + '0');
        }
        
        
        
    }while(exitFlag == 0);
    fprintf(write, "%s", getBuffer(buffer));
    fclose(read);       /*close the read output stream*/
    fclose(write);
    endwin();           /*exit ncurses*/
    return 0;
}
/*Explains the usage of the program*/
void usage(void){
    printf("Error, usage: bmacs <readname> <options>\n");
    return;
}



/*---------------------------------------------------------------------
  Draw Line of asterisks at the bottom of the screen with the readname
 ----------------------------------------------------------------------*/
void drawLine(char *readname){
    int termH = 50; // terminal height
    int termW = 95; // terminal width
    int row, col;
    getyx(curscr,col, row); // get current cursor
    for(int i=0; i<((termW/2) - strlen(readname)); i++)
        mvprintw(termH-5, i, "*"); // draw asterisk line
    printw("%s", readname); // print the readname
    for(int i=0; i<(termW/2); i++)
        mvprintw(termH-5, (termW/2) + i,  "*"); // finish the line
    move(col,row); //move back to the original place of cursor
    
    
}


/*
  bmacs version 0.1
*/
