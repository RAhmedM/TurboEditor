#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

using namespace std;


//pre-defined Structure to store Raw terminal input
struct termios original_terminos;

void disableRawMode()
{
    tcsetattr(STDIN_FILENO,TCSAFLUSH ,&original_terminos);
}

void startRawMode()
{
    struct termios modified_terminos;
    //gets terminal Attributes
    tcgetattr(STDIN_FILENO, &original_terminos);
    atexit(disableRawMode);

    modified_terminos = original_terminos;

    //we turn off the echo flag on each keypress
    //turning of canonical mode
    //turning of ctrl + z and ctrl + c

    modified_terminos.c_lflag &= ~(ECHO | ICANON | ISIG);
    
    //Disable Ctrl-S and Ctrl-Q
    modified_terminos.c_iflag &= ~(IXON);

    tcsetattr(STDIN_FILENO,TCSAFLUSH ,&modified_terminos);
}

int main()
{
    startRawMode();
    char c;
    while (read(STDIN_FILENO, &c, 1 && c != 'q') == 1)
    {
        if (iscntrl(c))
        {
            cout << static_cast<int>(c) << endl;
        } 
        else{
            cout << c << " :: " << static_cast<int>(c) << endl;
        }
    

    }
    
    return 0;
}
