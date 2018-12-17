//
// Created by arnaud on 11/12/18.
//

#ifndef CHALLENGE_TABOU_H
#define CHALLENGE_TABOU_H

using namespace std;
#include "QAP.h"
#include <vector>
#include <random>
#include <list>


class Tabou : public QAP {
/*
public:
    Tabou(const int &n, int F[][N_MAX], int D[][N_MAX]);
    int run(int bestSol[], int nbrIter, int tabouSize);


//private:
    int getBestNeighbor(int neighbors[][N_MAX], int neighbors_size);

    int getNeighbors(int neighbors[][N_MAX], int sol[]);

    void initSol(int sol[], int minValue, int maxValue);

    int* getBestNeighborNotInTabou(const list<int*> bazar, int sol[]);

    bool isInTabou(const list<int*> truc, int sol[]);

*/

public:
    Tabou(const int &n, int F[][N_MAX], int D[][N_MAX], int time, int tabouSize);
    int run(int startSol[]);
    vector<int> bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol);


private:
    int tabouSize;
    bool isInTabou(list<vector<int>> tabou, vector<int> sol);
    int computeObjectiveValue(vector<int> solution);
    bool continu();
    void printVector(vector<int> v);

    int time;
};


#endif //CHALLENGE_TABOU_H
