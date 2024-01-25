#include "../include/output.h"
#include "../include/terminal.h"
//-------------OUTPUT-----------

//print ~ at the sart of every line
void draw_Arrows()
{
    int y;
    for (y = 0; y < 24; y++) {
        write(STDOUT_FILENO, "~\r\n", 3);
    }
}

void clear_Screen() {
    // The first byte is \x1b, which is the escape character, or 27 in decimal.
    //Escape sequences always start with an escape character (27) followed by a [ character. 

    /*
        We are using the J command to clear the screen. 
        Escape sequence commands take arguments, which come before the command. 
        In this case the argument is 2, which says to clear the entire screen.
        <esc>[1J would clear the screen up to where the cursor is,
        and <esc>[0J would clear the screen from the cursor up to the end of the screen.
    */

    // the last argument is tells how many bytes are we are writing to the terminal
    // in this case 4
    write(STDOUT_FILENO, "\x1b[2J", 4);

    // 3 byte escape sequence to reposition the cursor to the top of the screen
    write(STDOUT_FILENO, "\x1b[H", 3);

    draw_Arrows();
    write(STDOUT_FILENO, "\x1b[H", 3);
}

