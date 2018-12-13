//
// Created by Aymerick on 11-12-18.
//

#include "GRASP.h"

GRASP::GRASP(const float &alpha, const int &n, const int F[][N_MAX], const int D[][N_MAX]) {

    this->alpha = alpha;
    this->n = n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            this->F[i][j] = F[i][j];
            this->D[i][j] = D[i][j];
        }
    }
}

const int *GRASP::getSolution() const {
    return solution;
}

int GRASP::getObjectiveValue() const {
    return objectiveValue;
}

int *GRASP::run(const float &maxSec) {
    clock_t t_init = clock();

    int s[N_MAX];
    do {
        updateBest(localSearch(greedyProbability(s)));
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxSec);

    this->objectiveValue = QAP::computeObjectiveValue(n, solution, F, D);
    return this->solution;
}

const int *GRASP::greedyProbability(int* s) {
    int best = 0;
    int bestVal;

    s[0] = rand() % n + 1; // Return a number between 1 and n

    // Look at each places
    for(int j = 1; j < n; j++) {
        bestVal = 1000000;
        // Look at each factories
        for (int i = 1; i <= n; i++) {
            // Check if i is in the solution
            bool isIn = false;
            for (int q = 0; q < j; q++) {
                if (s[q] == i) {
                    isIn = true;
                    break;
                }
            }
            if (!isIn) {
                // Compute added cost
                int cost = 0;
                for (int q = 0; q < j; q++) {
                    cost += D[j][q] * (F[s[q] - 1][i - 1] + F[i - 1][s[q] - 1]);
                }
                if (cost < bestVal) {
                    best = i;
                    bestVal = cost;
                }
            }
        }
        s[j] = best;
    }
    return s;
}

const int *GRASP::localSearch(const int *s) {
    return s;
}

void GRASP::updateBest(const int *s) {
    int obj = QAP::computeObjectiveValue(this->n, s, this->F, this->D);
    if(obj < this->objectiveValue) {
        for(int i = 0; i < n; i++) {
            this->solution[i] = s[i];
        }
        this->objectiveValue = obj;
    }
}
