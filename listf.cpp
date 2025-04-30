#include <iostream>
#include <vector>
#include "listf.h"

using namespace std;

vector<int> generateZeroList(int length) {
    vector<int> list(length, 0);

    // Change the num behind % if want change the density of the energy
    for (int i = 0; i < length; ++i) {
        if (rand() % 10 == 0) {
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
        lists.push_back(generateRandomListWithOnes(listLength, 2, 4));
        if (i < numLists - 1) {
            for (int j = 0; j < 3; ++j) {
                lists.push_back(generateZeroList(listLength));
            }
        }
    }

    return lists;
}


void displayLists(const vector<vector<int>>& lists, int start, int end, vector<string>emojis) {
    for (int i = start; i < end; ++i) {
        for (int num : lists[i]) {
            switch (num) {
                case 0: cout <<"  "; break;
                case 1: cout <<emojis[0]; break;
                case 2: cout <<emojis[1]; break;
                case 8: cout <<emojis[2]; break;
            }
        }
        cout << "\033[0m" << endl;
    }
}
