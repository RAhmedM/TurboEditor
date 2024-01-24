
#include "terminal.h"


//pre-defined Structure to store Raw terminal input
struct termios original_terminos;

//prints an error message and stops the execution
void halt(const char *s) 
{
    perror(s);
    exit(1);
}

void disableRawMode()
{
    if(tcsetattr(STDIN_FILENO,TCSAFLUSH ,&original_terminos) == -1)
        halt("tcsetattr");
    
}

void startRawMode()
{
    struct termios modified_terminos;
    
    //gets terminal Attributes
    if(tcgetattr(STDIN_FILENO, &original_terminos) == -1)
        halt("tcgetattr");

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


    // Adding timeout
    // Vmin is the minimum number of bytes of input needed before read happens
    // VTime sets the maximum amount of time to wait before read() returns.
    modified_terminos.c_cc[VMIN] = 0;
    modified_terminos.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO,TCSAFLUSH ,&modified_terminos) == -1)
        halt("tcsetattr");
}

char read_Key()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
    {
        if (nread == -1 && errno != EAGAIN) halt("read");
    }
    return c;
}

void process_key()
{
    char c = read_Key();
    switch (c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}