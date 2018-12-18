//
// Created by arnaud on 17/12/18.
//

#ifndef CHALLENGE_TABOU_H
#define CHALLENGE_TABOU_H

int run(int startSol[], int n, int tabouSize);
int runWithThreads(int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads);
#endif //CHALLENGE_TABOU_H
