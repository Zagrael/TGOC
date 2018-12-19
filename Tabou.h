//
// Created by arnaud on 17/12/18.
//

#ifndef CHALLENGE_TABOU_H
#define CHALLENGE_TABOU_H
using namespace std;

#include <vector>
#include <string>


vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals, int type);
vector<int> runWithThreads(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads, int type);
string printVector(vector<int> v);
#endif //CHALLENGE_TABOU_H
