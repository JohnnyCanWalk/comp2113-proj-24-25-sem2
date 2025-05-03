#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <algorithm>
#include <chrono>
#include <map>
#include <fstream>
#include "game.h"
#include "listf.h"
#include "commonfunctions.h"

using namespace std;
using namespace std::chrono;


//input level parameters from txt files
// multiple take negative value for harder
int loadpara(int level, string &art, vector<string> &emojis, int &multiple) {
    string path = "lv_info/lv" + to_string(level) + ".txt";
    ifstream file(path);
    string line;
    if (file){
    string m;
    getline(file, m);
    multiple = stoi(m);
        for (int i = 0; i < 3; i++) {
        string em;
        getline(file, em);
        emojis.push_back(em);
        }
        while (getline(file, line)) {
            art += line + "\n";
        }
    } else {
        art = "                 =^v^=";
        emojis.push_back("🐶");
        emojis.push_back("🐱");
        emojis.push_back("🐟");
        multiple = 1;
    }
    return 0;
}

// Input values for difficulty l for how long the game takes, w for how wide is the map
int l = 160, w = 40;

// Color codes for draw boss if want
const string RESET = "\033[0m";
const string WHITE = "\033[37m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string PURPLE = "\033[35m";


int game(int level, int &result) {
        int playerHP = 3;
        int energy = 0;
        bool survive = true;
        bool shieldActive = false;
        int healCount = 1;
        int bossHP = 10;
        int bossX = w/2 - 1;
        string art = "";
        vector<string> emojis;
        int multiple = 1;
        loadpara(level, art, emojis, multiple);
    srand(time(0));
    vector<vector<int>> lists = generateRandomLists(l-multiple*20, w);
    int cy = l - 1, cx = w / 2;
    int currentStart = l - 20;
    auto startTime = high_resolution_clock::now();
    lists[cy][cx] = 2;

    while (true) {
        clearScreen();

        // Show status
        cout << "HP: ";
        for (int i = 0; i < playerHP; ++i) cout << "\u2764 ";
        cout << " | [f]Fight: " << 20-multiple <<"e | [s]Sheild: " << 10-multiple
        <<"e | [h]Heal: "<< 15-multiple <<"e |" << endl;
        cout << "Energy: " << energy<<endl;
        cout << "Boss HP: ";
        for (int i = 0; i < bossHP; ++i) {for (int j = 0; j<8; j++) cout << "\u2588";}
        for (int i = 0; i < 10- bossHP; ++i) {for (int j = 0; j<8; j++) cout <<RED << "\u2588";}
        cout << endl;
        cout << WHITE <<art <<endl;

        if (lists[cy][cx] == 1 || lists[cy][cx] == 3) {
            if (!shieldActive) {
                playerHP--;
                if (playerHP <= 0) {
                survive = false;
                }
            }
            shieldActive = false;
        }

        lists[cy][cx] = 2;
        displayLists(lists, currentStart, currentStart + 20, emojis);

        if (survive == false) {
                clearScreen();
                     cout << RED << "Game Over!" << endl;
                     cout <<WHITE<< "[q] Quit" << endl;
        }

        if (cy == 0) {
            auto endTime = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(endTime - startTime).count();
            if (bossHP == 0)
            cout << GREEN << "You reached the summit and defeated the bot!" << RESET << endl;
            else
            cout << "You failed to defeat the bot :("<<endl;
            cout << "Time Taken: " << duration << " seconds." << endl;
                result = duration;

            cout << "[q] Quit" << endl;

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
        else if (key == 'q') return 0;
        else if (key == 'f' && energy>=(20-multiple)) {
                bossHP--;
                energy -= 20-multiple;
        }
        else if (key == 's' && energy>=10-multiple) {
            shieldActive = true;
            energy -= 10-multiple;
        }
        else if (key == 'h' && energy >= 15-multiple && playerHP < 3) {
            playerHP++;
            energy -= 15-multiple;
        }


        if (lists[cy][cx] == 8) {
            if (energy < 100) energy++;
            lists[cy][cx] = 0;
        }

    }
    return 0;
}
