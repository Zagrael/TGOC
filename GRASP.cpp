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

    do {
        updateBest(localSearch(greedyProbability()));
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxSec);
}

const int *GRASP::greedyProbability() {
    return nullptr;
}

const int *GRASP::localSearch(const int *s) {
    return nullptr;
}

void GRASP::updateBest(const int *s) {

}
