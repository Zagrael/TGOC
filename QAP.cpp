#include <random>

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

int *QAP::solveRandomly(const int &n, int F[][N_MAX], int D[][N_MAX], const int &maxSec, int * sol) {
    int test[N_MAX];
    for(int i = 0; i < n; i++) {
        sol[i] = i + 1;
        test[i] = i + 1;
    }
    int obj = computeObjectiveValue(n, sol, F, D);
    int objTest;

    clock_t t_init = clock();
    do {
        std::shuffle(&test[0], &test[n], std::mt19937(std::random_device()()));
        objTest = computeObjectiveValue(n, test, F, D);

        if(objTest < obj && isAdmissibleSolution(n, test)) {
            for(int i = 0; i < n; i++) {
                sol[i] = test[i];
            }
            obj = objTest;
        }
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxSec);

    return sol;
}
