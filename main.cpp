#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <termios.h>
#include <chrono>
#include <map>
#include "game.h"
#include "commonfunctions.h"

using namespace std;
using namespace std::chrono;

const string RESET = "\033[0m";
const string WHITE = "\033[37m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string PURPLE = "\033[35m";

struct leveltype {
    string name;
    string status;
};

class Chapter {
public:
    string name;
    int level_num;
    leveltype level[99];
    Chapter(string s, int a);
};

Chapter::Chapter(string s, int a) {
    name = s;
    level_num = a;
    for (int i = 1; i <= a; i++) {
        level[i].name = s + " Level " + to_string(i);
        if (i == 1){
            level[i].status = "Unlocked";
        } else {
            level[i].status = "Locked";
        }
    }
}


Chapter Game("GAME",10);

void print( const string& text, int x, int y) {
    cout << "\033[" << y << ";" << x << "H" << text;
    cout.flush();
}

void printlevel(int n, string chapterName) {
    print("/-\\", n * 4 - 3, 5);
    print("| |", n * 4 - 3, 6);
    print("\\_/", n * 4 - 3, 7);
    print(to_string(n), n * 4 - 2, 6);
}

void printarrow(int n) {
    print("^", 4 * n - 2, 8);
}

void removearrow(int n) {
    print(" ", 4 * n - 2, 8);
}

void printLevelInfo(leveltype level, int yPosition) {
    print("Level Name: " + level.name, 2, yPosition);
 print("Level Status: " + level.status, 2, yPosition + 1);
}

int main() {
    Chapter* currentChapter = &Game;
    int choose = 1;
    int maxLevel = currentChapter->level_num;
    clearScreen();
    print(currentChapter->name, 20, 1);
    for (int i = 0; i <= 50; i++) {
        print("-", i, 3);
    }
    for (int i = 1; i <= maxLevel; i++) {
        printlevel(i, currentChapter->name);
    }
    for (int i = 0; i <= 50; i++) {
        print("-", i, 10);
    }

    printarrow(choose);
    printLevelInfo(currentChapter->level[choose], 15);
        cout <<endl<< "[a] Play Level | [q] Quit";
while (true) {
    char ch = getch();
    if (ch == '\033'){
        ch = getch();
        if (ch == '[') {
          ch = getch();
          if (ch == 'D') {
              if (choose > 1) {
                  removearrow(choose);
                  choose -= 1;
                  printarrow(choose);
                  clearScreen();
                  for (int i = 1; i <= maxLevel; i++) {
                    printlevel(i, currentChapter->name);

                 print(currentChapter->name, 20, 1);
                for (int i = 0; i <= 50; i++) {
                     print("-", i, 3);
                 }
                 for (int i = 1; i <= maxLevel; i++) {
                     printlevel(i, currentChapter->name);
                 }
                 for (int i = 0; i <= 50; i++) {
                     print("-", i, 10);
                 }
                }
                printarrow(choose);
                printLevelInfo(currentChapter->level[choose], 15);
                cout <<endl<< "[a] Play Level | [q] Quit";
}
          } else if (ch == 'C'){
            if (choose < maxLevel) {
                removearrow(choose);
                choose += 1;
                printarrow(choose);
                clearScreen();
                for (int i = 1; i <= maxLevel; i++) {
                    printlevel(i, currentChapter->name);
                }
                 print(currentChapter->name, 20, 1);
            for (int i = 0; i <= 50; i++) {
              print("-", i, 3);
            }
           for (int i = 1; i <= maxLevel; i++) {
              printlevel(i, currentChapter->name);
           }
          for (int i = 0; i <= 50; i++) {
              print("-", i, 10);
           }
                printarrow(choose);
                printLevelInfo(currentChapter->level[choose], 15);
                cout <<endl<< "[a] Play Level | [q] Quit";
            }
          }
        }
      }  else if (ch == 'a'){
           game(choose);  // current level is the variable 'choose'
                Chapter* currentChapter = &Game;
    int maxLevel = currentChapter->level_num;
    clearScreen();
    print(currentChapter->name, 20, 1);
    for (int i = 0; i <= 50; i++) {
        print("-", i, 3);
    }
    for (int i = 1; i <= maxLevel; i++) {
        printlevel(i, currentChapter->name);
    }
    for (int i = 0; i <= 50; i++) {
        print("-", i, 10);
    }

    printarrow(choose);
    printLevelInfo(currentChapter->level[choose], 15);
        cout <<endl<< "[a] Play Level | [q] Quit";
      }
    else if (ch == 'q') {clearScreen(); break;}
  }
  return 0;
}
