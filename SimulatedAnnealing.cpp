//
// Created by Aymerick on 14-12-18.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(float t, float alpha, int n, int F[][N_MAX], int D[][N_MAX]) {
    this->t = t;
    this->alpha = alpha;
    this->n = n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            this->F[i][j] = F[i][j];
            this->D[i][j] = D[i][j];
        }
    }
}
