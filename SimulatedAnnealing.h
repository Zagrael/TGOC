//
// Created by Aymerick on 14-12-18.
//

#ifndef CHALLENGE_SIMULATEDANNEALING_H
#define CHALLENGE_SIMULATEDANNEALING_H

#include <time.h>
#include "common.h"
#include "QAP.h"

class SimulatedAnnealing {

    float t;
    float alpha;
    int n;
    int F[N_MAX][N_MAX];
    int D[N_MAX][N_MAX];
    int solution[N_MAX];
    int objectiveValue;

public:
    SimulatedAnnealing(float t, float alpha, int n, int (*F)[N_MAX], int (*D)[N_MAX]);

};


#endif //CHALLENGE_SIMULATEDANNEALING_H
