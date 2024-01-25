#include "terminal.h"
#include "output.h"
#include "input.h"



using namespace std;

int main()
{
    cout << "--------------TurboEditor--------------" << "\r\n";
    startRawMode();
    while (1) {
        clear_Screen();
        process_key();
    }
    
    return 0;
}