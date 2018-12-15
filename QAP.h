//
// Created by Aymerick on 11-12-18.
//

#ifndef CHALLENGE_QAP_H
#define CHALLENGE_QAP_H

#include <iostream>
#include <fstream>
#include <string>

const int N_MAX = 1000;

class QAP {

    std::string dataName;

protected:
    int n;
    int **F;
    int **D;
    int *solution;
    int objectiveValue;

    int computeObjectiveValue(const int &n, const int *solution);

public:

    // Constructors
    explicit QAP(const std::string &dataName);

    // Destructor
    virtual ~QAP();

    // Getters
    int *getSolution() const;
    int getObjectiveValue() const;
    int getN() const;
    int **getFlowMatrix() const;
    int **getDistanceMatrix() const;

    // Methods
    virtual int *run(const float &maxTimeSec) = 0; // Start an algorithm
    void displayOptimalSolution() const;
    static bool isAdmissible(const int &n, const int *s);
};


#endif //CHALLENGE_QAP_H
