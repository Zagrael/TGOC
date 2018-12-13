//
// Created by Sabrine Riahi on 2018-12-13.
//

#include <vector>
#include "QAP.h"
#include "iostream"

using namespace std ;


int QAP::computeObjectiveValue(const int &n, int solution[], int F[][N_MAX], int D[][N_MAX]) {
    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];
        }
    }
    return value;
}

int QAP::computeObjectiveValueVector(int n, vector<int> solution, int F[][N_MAX], int D[][N_MAX]) {
    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];
        }
    }
    return value;
}