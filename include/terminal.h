#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#define end_Program 17 // CTRL + Q
#define CTRL_KEY(k) ((k) & 0x1f)



void halt(const char *s);
void disableRawMode();
void startRawMode();
char read_Key();
void process_key();
void clear_Screen();

#endif
