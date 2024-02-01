#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h> 

#define end_Program 17 // CTRL + Q
#define CTRL_KEY(k) ((k) & 0x1f)

    struct editorConfig {
        int screen_height;
        int screen_width; 
        struct termios original_terminos;
    };

    extern struct editorConfig E;

    void halt(const char *s);
    void disableRawMode();
    void startRawMode();
    char read_Key();
    int getWindowSize(int *rows, int *cols);

#endif
