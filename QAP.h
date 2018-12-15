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
    int *solution;
    int objectiveValue;

protected:
    int n;
    int **F;
    int **D;

    int computeObjectiveValue(const int &n, int solution[]);

public:

    // Constructors
    explicit QAP(const std::string &fileName);

    // Destructor
    virtual ~QAP();

//    virtual void run() = 0;

    // Getters
    int *getSolution() const;
    int getObjectiveValue() const;
    int getN() const;
    int **getFlowMatrix() const;
    int **getDistanceMatrix() const;

    // Methods
    void displayOptimalSolution() const;
};


#endif //CHALLENGE_QAP_H
