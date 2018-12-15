//
// Created by Aymerick on 11-12-18.
//

#include "QAP.h"

/*
 * Constructors
 * */
QAP::QAP(const std::string &dataName): dataName(dataName) {

    std::string fileName = "../instances/" + dataName + ".dat";
    std::ifstream in(fileName);

    if(!in)
        throw "Error in QAP::QAP(fileName) : Could not open file !";

    // Number of data
    in >> this->n;
    this->F = new int*[n];
    this->D = new int*[n];
    this->solution = new int[n];

    // Distances matrix
    for(int i = 0; i < n; i++) {
        this->D[i] = new int[n];
        for(int j = 0; j < n; j++) {
            in >> this->D[i][j];
        }
    }

    // Flow matrix
    for(int i = 0; i < n; i++) {
        this->F[i] = new int[n];
        for(int j = 0; j < n; j++) {
            in >> this->F[i][j];
        }
    }

    in.close();

    // Initialize the solution
    solution = new int[n];
    for(int i = 0; i < n; i++) {
        solution[i] = i + 1;
    }
    objectiveValue = computeObjectiveValue(n, solution);
}

/*
 * Destructor
 * */
QAP::~QAP() {
    // Liberate memory
    for(int i = 0; i < n; i++) {
        delete[] F[i];
        delete[] D[i];
    }
    delete[] F;
    delete[] D;
    delete[] solution;
}

int QAP::computeObjectiveValue(const int &n, const int *solution) {
    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];
        }
    }
    return value;
}

bool QAP::isAdmissible(const int &n, const int *s) {
    for(int i = 0; i < n; i++) {
        if (s[i] < 1 || s[i] > n)
            return false;
        for (int j = 0; j < i; j++)
            if (s[i] == s[j])
                return false;
    }
    return true;
}

void QAP::displayOptimalSolution() const {

    std::string fileName = "../instances/" + dataName + ".sln";
    std::ifstream in(fileName);

    if(!in) {
        throw "Error in QAP::displayOptimalSolution() : Could not open file !";
    }

    // Number of data
    int n;
    in >> n;

    // Objective value
    int optimalValue;
    in >> optimalValue;
    std::cout << "Optimal value : " << optimalValue << std::endl;

    // Solution vector
    int elem;
    std::cout << "Optimal solution :";
    for(int i = 0; i < n; i++) {
        in >> elem;
        std::cout << " " << elem;
    }
    std::cout << std::endl;

    in.close();
}

/*
 * Getters
 * */
int *QAP::getSolution() const {
    return solution;
}

int QAP::getObjectiveValue() const {
    return objectiveValue;
}

int QAP::getN() const {
    return n;
}

int **QAP::getFlowMatrix() const {
    return F;
}

int **QAP::getDistanceMatrix() const {
    return D;
}
