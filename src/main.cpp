#include "terminal.h"




using namespace std;

int main()
{
    cout << "--------------TurboEditor--------------" << "\r\n";
    startRawMode();
    while (1) {
        process_key();
    }
    
    return 0;
}