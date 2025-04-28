#include <iostream>
#include <termios.h>
#include "commonfunctions.h"
#include <unistd.h>
using namespace std;

char getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}
