//
// Created by Aymerick on 15-12-18.
//

#ifndef CHALLENGE_GRASP_H
#define CHALLENGE_GRASP_H

#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <list>
#include "QAP.h"
//#include "Tabou.h"

using namespace std;

class GRASP : public QAP {
    float alpha;

public:
    // Constructors
    GRASP(std::string &dataName, float alpha);

    // Methods
    int *run(const float &maxTimeSec) override;
    int *greedyProbability(int *s);
    float *computeProbabilities(int *s, const int &nS, float *p);
    int choseProbability(float *p);
    int *localSearch(int *s);
    void updateBest(int *s);

    // Tabu functions
    vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals);
    vector<int> bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol);
    bool isInTabou(list<vector<int>> tabou, vector<int> sol);
    int computeObjectiveValue(vector<int> solution);

    void writeSolution(const std::string &method) override;
};


#endif //CHALLENGE_GRASP_H
