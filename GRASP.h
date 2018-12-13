//
// Created by Aymerick on 11-12-18.
//

#ifndef CHALLENGE_GRASP_H
#define CHALLENGE_GRASP_H

#include <time.h>
#include "common.h"
#include "QAP.h"
#include <cstdlib>

class GRASP {

    float alpha;
    int n;
    int F[N_MAX][N_MAX];
    int D[N_MAX][N_MAX];
    int solution[N_MAX];
    int objectiveValue;

public:
    /*
     * Constructor
     * */
    GRASP(const float&, const int&, const int[][N_MAX], const int[][N_MAX]);

    /*
     * Getters
     * */
    const int *getSolution() const;
    int getObjectiveValue() const;

    /*
     * Algorithm
     * */
    int *run(const float &);
    const int *greedyProbability(int*);
    const int *localSearch(const int*);
    void updateBest(const int*);
};


#endif //CHALLENGE_GRASP_H
