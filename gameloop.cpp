#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <algorithm>
#include <chrono>
#include <map>

using namespace std;
using namespace std::chrono;

// Game parameters
int l = 200, w = 50;

// Color codes
const string RESET = "\033[0m";
const string WHITE = "\033[37m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string PURPLE = "\033[35m";

// Game state
int playerHP = 3;
int energy = 0;
bool shieldActive = false;
int healCount = 1;
int bossHP = 10;
int bossX = w/2 - 1;

// Utility
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

vector<int> generateZeroList(int length) {
    // Now generates land (0) with some flowers (8)
    vector<int> list(length, 0);

    // Add some random flowers (about 10% chance per tile)
    for (int i = 0; i < length; ++i) {
        if (rand() % 10 == 0) {  // 10% chance for flower
            list[i] = 8;
        }
    }

    return list;
}

vector<int> generateRandomListWithOnes(int length, int minOnes, int maxOnes) {
    // Now generates walls (1) with paths (0)
    vector<int> list(length, 1);  // Start with all wall

    // Determine how many path openings to create
    int numPaths = minOnes + rand() % (maxOnes - minOnes + 1);
    numPaths = min(numPaths, length);  // Ensure we don't exceed length

    // Create paths (0) through the wall
    for (int i = 0; i < numPaths; ++i) {
        int pos = rand() % length;
        list[pos] = 0;  // Create path

        // Optional: make wider paths by clearing adjacent cells
        if (pos > 0) list[pos-1] = 0;
        if (pos < length-1) list[pos+1] = 0;
    }

    return list;
}

vector<vector<int>> generateRandomLists(int numLists, int listLength) {
    vector<vector<int>> lists;
    srand(time(0));  // Seed random number generator

    for (int i = 0; i < numLists; ++i) {
        // Add a wall row with paths (using generateRandomListWithOnes)
        lists.push_back(generateRandomListWithOnes(listLength, 2, 4));  // Between 2-4 path openings

        if (i < numLists - 1) {
            // Add 3 land rows with flowers (using generateZeroList)
            for (int j = 0; j < 3; ++j) {
                lists.push_back(generateZeroList(listLength));
            }
        }
    }

    return lists;
}


void displayLists(const vector<vector<int>>& lists, int start, int end) {
    for (int i = start; i < end; ++i) {
        for (int num : lists[i]) {
            switch (num) {
                case 0: cout <<"  "; break;
                case 1: cout <<"💣"; break;
                case 2: cout <<"😲"; break;
                case 8: cout <<"⚡"; break;
            }
        }
        cout << RESET << endl;
    }
}


int main() {
    srand(time(0));
    vector<vector<int>> lists = generateRandomLists(l, w);
    int cy = l - 1, cx = w / 2;
    int currentStart = l - 20;
    auto startTime = high_resolution_clock::now();
    lists[cy][cx] = 2;

    while (true) {
        clearScreen();

        // Show status
        cout << "HP: ";
        for (int i = 0; i < playerHP; ++i) cout << "\u2764 ";
        cout << " | [F]Fireball: 20e | [S]Sheild: 10e | [H]Heal: 15e |" << endl;
        cout << "Energy: " << energy<<endl;
        cout << "Boss HP: ";
        for (int i = 0; i < bossHP; ++i) cout << "\u2588" << "\u2588";
        cout << endl;

        cout << "                   \\   /    " << endl;
        cout << "                    | |     " << endl;
        cout << "                   (` ')    " << endl;
        cout << "                   (  v )   " << endl;
        cout << "                   /   \\    " << endl;
        cout << "                  /     \\   " << endl;
        cout << "                 /_______\\  " << endl;
        cout << "                  |     |   " << endl << endl;


        if (lists[cy][cx] == 1 || lists[cy][cx] == 3) {
            if (!shieldActive) {
                playerHP--;
                if (playerHP <= 0) {
                    cout << RED << "Game Over!" << RESET << endl;
                    break;
                }
            }
            shieldActive = false;
        }

        lists[cy][cx] = 2;
        displayLists(lists, currentStart, currentStart + 20);

        if (cy == 0) {
            auto endTime = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(endTime - startTime).count();
            if (bossHP == 0)
            cout << GREEN << "You reached the summit and defeated the boss!" << RESET << endl;
            else
            cout << "Level failed"<<endl;
            cout << "Time Taken: " << duration << " seconds." << endl;
            break;
        }

        if (rand() % 20 == 0) lists[rand() % l][rand() % w] = 8;

        char key = getch();
        lists[cy][cx] = 0;

        if (key == '\033') {
            key = getch();
            if (key == '[') {
                key = getch();
                if (key == 'A') { if (cy > 0) { cy--; currentStart = max(0, currentStart - 1); } }
                else if (key == 'C') { if (cx < w - 1) cx++; }
                else if (key == 'D') { if (cx > 0) cx--; }
            }
        }
        else if (key == 'q') break;
        else if (key == 'f' && energy>=20) {
                bossHP--;
                energy -= 20;
        }
        else if (key == 's' && energy>=10) {
            shieldActive = true;
            energy -= 10;
        }
        else if (key == 'h' && energy >= 15 && playerHP < 3) {
            playerHP++;
            energy -= 15;
        }


        if (lists[cy][cx] == 8) {
            if (energy < 100) energy++;
            lists[cy][cx] = 0;
        }

    }
    return 0;
}
