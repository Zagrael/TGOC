#include <cmath>

//
// Created by Aymerick on 14-12-18.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(float t, float alpha, int n, int F[][N_MAX], int D[][N_MAX], int iterByTemp) {
    this->t = t;
    this->alpha = alpha;
    this->iterByTemp = iterByTemp;
    this->n = n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            this->F[i][j] = F[i][j];
            this->D[i][j] = D[i][j];
        }
    }
}

int SimulatedAnnealing::getObjectiveValue() const {
    return objectiveValue;
}

int *SimulatedAnnealing::run(const float &maxSec) {
    clock_t t_init = clock();

    int s[N_MAX];
    for(int i = 0; i < n; i++) {
        s[i] = solution[i];
    }
    int v[N_MAX][N_MAX];
    float p[N_MAX];
    do {
        for(int k = 0; k < iterByTemp; k++) {
            for (int i = 0; i < n - 1; i++) { // Each neighbor
                for (int j = 0; j < n; j++) {
                    v[i][j] = s[j];
                }
                v[i][i] = s[i + 1];
                v[i][i + 1] = s[i];

                p[i] = computeProb(v[i]);
            }
            int q = choseRandom(p);
            if(q != -1) {
                for(int i = 0; i < n; i++) {
                    s[i] = v[q][i];
                }
                std::cout << v[q][0] << std::endl;
                std::cout << s[0] << std::endl;
                updateBest(s);
            } else
                std::cout << "q = -1" << std::endl;
        }
        updateTemperature();
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxSec && t > 0);

    this->objectiveValue = QAP::computeObjectiveValue(n, solution, F, D);
    return this->solution;
}

void SimulatedAnnealing::updateTemperature() {
    t *= alpha;
}

void SimulatedAnnealing::findNeighbors(int s[], int v[][N_MAX]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n; j++) {
            v[i][j] = s[j];
        }
        v[i][i] = s[i + 1];
        v[i][i + 1] = s[i];
    }
}

float SimulatedAnnealing::computeProb(int *v) {
    int obj = QAP::computeObjectiveValue(n, v, F, D);
    std::cout << obj << std::endl;
    return (obj <= objectiveValue) ?  1 : std::exp((objectiveValue - obj) / t);
}

void SimulatedAnnealing::updateBest(int *s) {
    int obj = QAP::computeObjectiveValue(this->n, s, this->F, this->D);
    if(QAP::isAdmissibleSolution(n,s) && obj < this->objectiveValue) {
        for(int i = 0; i < n; i++) {
            this->solution[i] = s[i];
        }
        this->objectiveValue = obj;
    }
}

int SimulatedAnnealing::choseRandom(float p[]) {
    float pc = 0.00f;
    float r = ((float) rand() / (RAND_MAX + 1));

    float den = 0;
    for(int i = 0; i < n; i++) {
        den += p[i];
    }
    for(int i = 0; i < n; i++) {
        pc += p[i] / den;
        if(r <= pc) return i;
    }
    return -1;
}

void SimulatedAnnealing::setSolution(int s[]) {
    for(int i = 0; i < n; i++) {
        solution[i] = s[i];
    }
    objectiveValue = QAP::computeObjectiveValue(n, solution, F, D);
}
