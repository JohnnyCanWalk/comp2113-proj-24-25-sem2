#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <algorithm>
#include <termios.h>
#include <chrono>
#include <map>
#include "game.h"
#include "story.h"
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
    int time;
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
        level[i].time = 0;
    }
}

Chapter Game("GAME", 10);

void print(const string& text, int x, int y) {
    cout << "\033[" << y << ";" << x << "H" << text;
    cout.flush();
}

void printlevel(int n, string chapterName) {
    print(" ___", n * 6 - 5, 5);
    print("|   |", n * 6 - 5, 6);
    print("|   |", n * 6 - 5, 7);
    print("|___|", n * 6 - 5, 8);
    print(to_string(n), n * 6 - 3, 7);
}

void printarrow(int n) {
    print("^", 6 * n - 3, 9);
}

void removearrow(int n) {
    print(" ", 6 * n - 3, 9);
}


void printLevelInfo(leveltype level, int yPosition) {
    print("Level Name: " + level.name, 1, yPosition);
    print("Level Status: " + level.status, 1, yPosition + 1);
    if (level.status == "Completed") {
        print("Record completion time: " + to_string(level.time), 1, yPosition + 2);
    }
    if (level.status != "Locked"){
        print("Press [a] to play, [q] to quit.", 1, 25);
    } else {
        print("Press [q] to quit.", 1, 25);
    }
}

void printMenu(Chapter* currentChapter, int choose) {
    clearScreen();
    print(currentChapter->name, 20, 1);
    for (int i = 0; i <= 60; i++) {
        print("-", i, 3);
    }
    for (int i = 1; i <= currentChapter->level_num; i++) {
        printlevel(i, currentChapter->name);
    }
    for (int i = 0; i <= 60; i++) {
        print("-", i, 11);
    }
    printarrow(choose);
    printLevelInfo(currentChapter->level[choose], 15);
    print("Storyline: " + story(choose), 1, 18);
}

void saveProgress(const Chapter& chapter) {
    ofstream file("progress.txt");
    if (file.is_open()) {
        file << chapter.name << endl;
        file << chapter.level_num << endl;
        for (int i = 1; i <= chapter.level_num; i++) {
            file << chapter.level[i].name << ","
                 << chapter.level[i].status << ","
                 << chapter.level[i].time << endl;
        }
        file.close();
    } else {
        cout << "Unable to open progress.txt for writing." << endl;
    }
}

int loadProgress(Chapter& chapter) {
    ifstream file("progress.txt");
    if (file.is_open()) {
        string chapterName;
        int levelNum;
        file >> chapterName >> levelNum;
        chapter.name = chapterName;
        chapter.level_num = levelNum;

        int firstUnlockedLevel = 1; // Default to the first level
        for (int i = 1; i <= levelNum; i++) {
            string levelName, status;
            int time;
            getline(file, levelName, ',');
            getline(file, status, ',');
            file >> time;
            chapter.level[i].status = status;
            chapter.level[i].time = time;

            // Check if this is the first unlocked level
            if (status == "Unlocked") {
                firstUnlockedLevel = i;
                break;
            }
        }
        file.close();
        return firstUnlockedLevel; // Return the index of the first unlocked level
    } else {
        // Initialize progress.txt with default values
        ofstream outFile("progress.txt");
        if (outFile.is_open()) {
            outFile << chapter.name << endl;
            outFile << chapter.level_num << endl;
            for (int i = 1; i <= chapter.level_num; i++) {
                outFile << chapter.level[i].name << ","
                        << chapter.level[i].status << ","
                        << chapter.level[i].time << endl;
            }
            outFile.close();
        } else {
            cout << "Unable to create progress.txt for writing." << endl;
            return 1; // Default to the first level if initialization fails
        }
        return 1; // Default to the first level after initialization
    }
}

int main() {
    Chapter* currentChapter = &Game;
    int maxLevel = currentChapter->level_num;
    int choose = loadProgress(*currentChapter);
    printMenu(currentChapter, choose);

    while (true) {
        char ch = getch();
        if (ch == '\033') {
            ch = getch();
            if (ch == '[') {
                ch = getch();
                if (ch == 'D') {
                    if (choose > 1) {
                        removearrow(choose);
                        choose -= 1;
                        printMenu(currentChapter, choose);
                    }
                } else if (ch == 'C') {
                    if (choose < maxLevel) {
                        removearrow(choose);
                        choose += 1;
                        printMenu(currentChapter, choose);
                    }
                }
            }
        } else if ((ch == 'A' || ch == 'a') && currentChapter->level[choose].status != "Locked") {
            int result;
            game(choose, result);
            if (result > 0 && result <= 200){
                if (choose < maxLevel && currentChapter->level[choose + 1].status == "Locked") {
                    currentChapter->level[choose + 1].status = "Unlocked";
                }
                if (currentChapter->level[choose].time > result || currentChapter->level[choose].status != "Completed"){
                    currentChapter->level[choose].time = result;
                }
                currentChapter->level[choose].status = "Completed";
                choose += 1;
                saveProgress(*currentChapter);
            }
            printMenu(currentChapter, choose);
        } else if (ch == 'q' || ch == 'Q') {
            clearScreen();
            break;
        }
    }
    return 0;
}
