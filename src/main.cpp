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

    //we turn off the echo flag
    //turning of canonical mode
    //turning of ctrl + z and ctrl + c
    //turning of ctrl + v

    modified_terminos.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    
    //Disable Ctrl-S and Ctrl-Q
    //Fix control M
    //sends SIGINT signal
    //disabling parity chechking
    //turning off 8 bit stripping

    modified_terminos.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);

    //Dont need Output Prceesing for now
    // //Turning off all output processing
    modified_terminos.c_oflag &= ~(OPOST);

    //Sets charachter size to 8 bits per byte
    modified_terminos.c_cflag |= (CS8);

    modified_terminos.c_cc[VMIN] = 0;
    modified_terminos.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO,TCSAFLUSH ,&modified_terminos);
}

int main()
{
    cout << "--------------TurboEditor--------------" << "\r\n";
    startRawMode();
    while (1) {
        char c = '\0';
        
        //read(STDIN_FILENO, &c, 1);
        if(!read(STDIN_FILENO, &c, 1)) continue;
        
        if (iscntrl(c))
        {
            cout << static_cast<int>(c) << "\r\n";
        } 
        else{
            cout << c << " :: " << static_cast<int>(c) << "\r\n";
        }
        if (c == 'q') break;

    }
    
    return 0;
}