#ifndef LISTF_H
#define LISTF_H

#include <vector>
#include <string>

using namespace std;

vector<vector<int>> generateRandomLists(int numLists, int listLength);
void displayLists(const vector<vector<int>>& lists, int start, int end, vector<string>emojis);

#endif // LISTF_H
