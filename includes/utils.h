#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
    #include <conio.h>

#elif __linux__
    #include <fstream>
    #include <unistd.h>
    #include <termios.h>
    
    inline int getch(void) {
        int ch;
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

#endif