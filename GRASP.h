//
// Created by Aymerick on 15-12-18.
//

#ifndef CHALLENGE_GRASP_H
#define CHALLENGE_GRASP_H

#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include "QAP.h"

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

private:
    // For tabu search
    bool isInTabou(list<vector<int>> tabou, vector<int> sol);
    vector<int> bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol);
    vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals);
    int computeObjectiveValue(vector<int> solution);
    void printVector(vector<int> v);
};


#endif //CHALLENGE_GRASP_H
