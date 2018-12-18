#include <random>

#include <cmath>

//
// Created by Aymerick on 14-12-18.
//

#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(std::string dataName, float t, float alpha, int iterByTemp)
    : QAP(dataName), t(t), alpha(alpha), iterByTemp(iterByTemp) {}

int *SimulatedAnnealing::run(const float &maxSec) {
    std::cout << "Running Simulated Annealing..." << std::endl;
    clock_t t_init = clock();

    int *s = new int[n];
    for(int i = 0; i < n; i++) {
        s[i] = solution[i];
    }
    auto *v = new int[n];
    auto *p = new float[n-1];

    do {
        for(int k = 0; k < iterByTemp; k++) {
            // Find neighbors
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < n; j++) {
                    v[j] = s[j];
                }
                v[i] = s[i + 1];
                v[i + 1] = s[i];

                p[i] = computeProb(v);
            }
            int q = choseRandom(p);
            if(q != -1) {
                int temp = s[q];
                s[q] = s[q+1];
                s[q+1] = temp;
                updateBest(s);
            }
        }
        updateTemperature();
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxSec && t >= 1);

    std::cout << "End of Simulated Annealing !" << std::endl;
    objectiveValue = computeObjectiveValue(n, solution);
    return solution;
}

void SimulatedAnnealing::updateTemperature() {
    t *= alpha;
}

float SimulatedAnnealing::computeProb(int *v) {
    int obj = computeObjectiveValue(n, v);
    return (obj <= objectiveValue) ?  1 : std::exp((objectiveValue - obj) / t);
}

void SimulatedAnnealing::updateBest(int *s) {
    int obj = computeObjectiveValue(n, s);
    if(isAdmissible(n,s) && obj < objectiveValue) {
        for(int i = 0; i < n; i++) {
            solution[i] = s[i];
        }
        objectiveValue = obj;
    }
}

int SimulatedAnnealing::choseRandom(float *p) {
    float pc = 0.00f;
    float r = ((float) rand() / (RAND_MAX + 1));

    float den = 0;
    for(int i = 0; i < n - 1; i++) {
        den += p[i];
    }
    for(int i = 0; i < n - 1; i++) {
        den == 0 ? pc += p[i] : pc += p[i] / den;
        if(r <= pc) return i;
    }
    return -1;
}
