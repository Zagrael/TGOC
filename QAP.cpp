//
// Created by Aymerick on 12-12-18.
//

#include "QAP.h"

int QAP::computeObjectiveValue(const int &n, const int solution[], int F[][N_MAX], int D[][N_MAX]) {
    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];
        }
    }
    return value;
}

bool QAP::isAdmissibleSolution(const int &n, const int *solution) {
    for(int i = 0; i < n; i++) {
        if (solution[i] < 1)
            return false;
        for (int j = 0; j < i; j++)
            if (solution[i] == solution[j])
                return false;
    }
    return true;
}
