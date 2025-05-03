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

void printlevel(int n, string chapterName, bool isSelected, bool isLocked, bool isCompleted) {
    string borderColor = isSelected ? GREEN : WHITE;
    string numberColor = isLocked ? RED : (isCompleted ? GREEN : WHITE);
    string numberText = to_string(n);
    string statusIcon = isLocked ? "🔒" : (isCompleted ? "✅" : "__");

    // Print the top border
    print(borderColor + " _ ", n * 6 - 5, 5);
    // Print the left and right borders with the level number centered
    if (n == 10){
      print(borderColor + "|" + numberColor + numberText + " " + borderColor + "|", n * 6 - 5, 6);
    } else {
       print(borderColor + "| " + numberColor + numberText + " " + borderColor + "|", n * 6 - 5, 6);
    }
    print(borderColor + "|_" + statusIcon + "|", n * 6 - 5, 7);
}

void printarrow(int n) {
    print("^", 6 * n - 3, 9);
}

void removearrow(int n) {
    print(" ", 6 * n - 3, 9);
}


void printMenu(Chapter* currentChapter, int choose) {
    clearScreen();
    print(WHITE + currentChapter->name, 20, 1);
    for (int i = 0; i <= 60; i++) {
        print(WHITE + "-", i, 3);
    }

    for (int i = 1; i <= currentChapter->level_num; i++) {
        bool isSelected = (i == choose);
        bool isLocked = (currentChapter->level[i].status == "Locked");
        bool isCompleted = (currentChapter->level[i].status == "Completed");

        printlevel(i, currentChapter->name, isSelected, isLocked, isCompleted);
    }

    for (int i = 0; i <= 60; i++) {
        print(WHITE + "-", i, 11);
    }

    printarrow(choose);

    leveltype selectedLevel = currentChapter->level[choose];
    print(WHITE + "Level Name: " + selectedLevel.name, 1, 15);
    print(WHITE + "Level Status: " + selectedLevel.status, 1, 16);
    if (selectedLevel.status == "Completed") {
        print(GREEN + "Record completion time: " + to_string(selectedLevel.time), 1, 17);
    }
    if (selectedLevel.status != "Locked") {
        print(YELLOW + "Press [a] to play, [q] to quit.", 1, 25);
    } else {
        print(RED + "Press [q] to quit.", 1, 25);
    }

    print(WHITE + "Storyline: " + story(choose), 1, 18);
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

int introduction() {
        clearScreen();
    cout << "    _             _                 _\n";
    cout << "   / \\   _ __ ___| | __ _ _ __   __| |\n";
    cout << "  / _ \\ | '__/ _ \\ |/ _` | '_ \\ / _` |\n";
    cout << " / ___ \\| | |  __/ | (_| | | | | (_| |\n";
    cout << "/_/   \\_\\_|  \\___|_|\\__,_|_| |_|\\__,_|\n\n";
    cout << "🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖🤖\n\n";
    cout << "Kevin is a eighteen-year-old boy living on the serene and beautiful planet of Areland, a place where \nlife seems perfect—there’s no war, no poverty, and everyone is content.  However, the turning point is at his 19yo \n birthday. Kevin’s father passed him a book. It was the heirloom of their family. It was said that\n it wrote the secret behind this world but till now, no one can open the book. Kevin tried to open\n the book too. Unexpectedly, the book was opened. A strong explosion mixed with light, \nfire and thunder occurred. The great energy killed all of Kevin’s family, leaving only Kevin \nuninjured, protected by the odd book. Desperately, Kevin picked up the book and read the content.\n He finally knew that Areland is an virtual plant made by AIs to prison their creators. His real \nidentity on earth was Kelvin Musk, a great engineer whom has been working in the AI industry \nfor years. Knowing the truth, Kevin decides to wake up. He needs to defeat the 10 bosses \nwhom are defending this virtual world to get back to the real world.";
    cout << "\n🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟🌟\n";
    cout << "\nPress any key to start the game -->";
    getch();
    return 0;
}

int main() {
    introduction();
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
