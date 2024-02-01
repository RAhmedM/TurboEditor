#include "../include/terminal.h"
#include "../include/input.h"

//-------------INPUT------------
void process_key()
{
    char c = read_Key();
    // std::cout << c << " : " << static_cast<int>(c) << "\r\n";
    switch (c) {
        case CTRL_KEY('q'):
            write(STDOUT_FILENO, "\x1b[2J", 4);
            write(STDOUT_FILENO, "\x1b[H", 3);
            exit(0);
            break;
    }
}
