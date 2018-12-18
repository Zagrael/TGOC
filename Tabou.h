//
// Created by arnaud on 17/12/18.
//

#ifndef CHALLENGE_TABOU_H
#define CHALLENGE_TABOU_H

using namespace std;
#include <vector>
#include <cstdio>
#include <list>
#include <limits>
//#include "main.h"
#include <ctime>
#include <pthread.h>
#include <random>
#include <algorithm>
#include <unistd.h>

//int run(int startSol[], int n, int tabouSize);
//int runWithThreads(int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads);
vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals);

#endif //CHALLENGE_TABOU_H
