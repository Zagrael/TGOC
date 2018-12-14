//
// Created by Aymerick on 14-12-18.
//

#ifndef CHALLENGE_SIMULATEDANNEALING_H
#define CHALLENGE_SIMULATEDANNEALING_H

#include <time.h>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "common.h"
#include "QAP.h"

class SimulatedAnnealing {

    float t;
    float alpha;
    int iterByTemp;
    int n;
    int F[N_MAX][N_MAX];
    int D[N_MAX][N_MAX];
    int solution[N_MAX];
    int objectiveValue;

public:
    /*
     * Constructor
     * */
    SimulatedAnnealing(float t, float alpha, int n, int (*F)[N_MAX], int (*D)[N_MAX], int iterByTemp);

    /*
     * Getters
     * */
    void setSolution(int s[]);
    int getObjectiveValue() const;

    /*
     * Algorithm
     * */
    int *run(const float &maxSec);
    void updateTemperature();
    void findNeighbors(int s[], int v[][N_MAX]);
    float computeProb(int v[]);
    int choseRandom(float p[]);
    void updateBest(int s[]);

};


#endif //CHALLENGE_SIMULATEDANNEALING_H
