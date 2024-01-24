
#include "terminal.h"


//pre-defined Structure to store Raw terminal input
struct termios original_terminos;

//prints an error message and stops the execution
void halt(const char *s) 
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
    
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

//-------------OUTPUT-----------



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
}

//-------------INPUT------------
void process_key()
{
    char c = read_Key();
    //  std::cout << c << " : " << static_cast<int>(c) << "\r\n";
    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;
    }
}