#include "terminal.h"
#include "output.h"
#include "input.h"


void initialize_editor() {
  if (getWindowSize(&E.screen_height, &E.screen_width) == -1) halt("getWindowSize");
}


int main()
{
    startRawMode();

    initialize_editor();
    while (1) {
        clear_Screen();
        process_key();
    }
    
    return 0;
}