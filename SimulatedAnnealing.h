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
#include <string>
#include "QAP.h"

class SimulatedAnnealing : public QAP {

    float t;
    float alpha;
    int iterByTemp;

public:
    /*
     * Constructor
     * */
    SimulatedAnnealing(std::string dataName, float t, float alpha, int iterByTemp);

    /*
     * Algorithm
     * */
    int *run(const float &maxTimeSec) override;
    void updateTemperature();
    float computeProb(int *v);
    int choseRandom(float *p);
    void updateBest(int *s);

};


#endif //CHALLENGE_SIMULATEDANNEALING_H
