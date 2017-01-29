#include "bmacs.h"
#include "buffer.h"

/*
  bmacs text editor, written to be a lightweight gap buffer-based text editor for use on UNIX/BSD based operating system, with the only main library used being ncurses.
*/


int main(int argc, char **argv){
    if(argc < 2){ /*make sure that the user actually provided a file*/
        usage();
        return 1;
    }


    initscr(); /*start ncurses*/
    
    FILE *file;
    file = fopen(argv[1], "w+"); //open the first command line argument
   

    GapBuffer buffer;

    //initialiation of the buffer (temporary)
    size_t bufSize = 256;
    buffer.size = bufSize;
    char start[buffer.size];
    buffer.start = start;
    buffer.gapStart = buffer.start;
    buffer.end = buffer.start + buffer.size; 
     
        
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
            printw("%c", keyname(input));
            //            insertChar(buffer, keyname(input));
        }
        
        
        
    }while(exitFlag == 0);

    fprintf(file, "%s", "file writing is not yet finished");
    fclose(file);       /*close the file output stream*/
    endwin();           /*exit ncurses*/
    return 0;
}

void usage(void){
    printf("Error, usage: bmacs <filename> <options>\n");
    return;
}



/*---------------------------------------------------------------------
  Draw Line of asterisks at the bottom of the screen with the filename
 ----------------------------------------------------------------------*/
void drawLine(char *filename){
    int termH = 50; // terminal height
    int termW = 95; // terminal width
    int row, col;
    getyx(curscr,col, row); // get current cursor
    for(int i=0; i<((termW/2) - strlen(filename)); i++)
        mvprintw(termH-5, i, "*"); // draw asterisk line
    printw("%s", filename); // print the filename
    for(int i=0; i<(termW/2); i++)
        mvprintw(termH-5, (termW/2) + i,  "*"); // finish the line
    move(col,row); //move back to the original place of cursor
    
    
}


/*
  bmacs version 0.1
*/
