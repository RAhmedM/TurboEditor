#include "terminal.h"
#include "output.h"
#include "input.h"



using namespace std;

int main()
{
    startRawMode();
    while (1) {
        clear_Screen();
        process_key();
    }
    
    return 0;
}