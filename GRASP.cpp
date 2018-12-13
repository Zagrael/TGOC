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

    s[0] = rand() % n + 1; // Return a number between 1 and n
    float prob[N_MAX];
    for(int i = 1; i < n; i++) {
        s[i] = choseProbability(computeProbabilities(s, i, prob)) + 1;
    }
    return s;
}

const int *GRASP::localSearch(const int *s) {
    return s;
}

void GRASP::updateBest(const int *s) {
    int obj = QAP::computeObjectiveValue(this->n, s, this->F, this->D);
    if(QAP::isAdmissibleSolution(n,s) && obj < this->objectiveValue) {
        for(int i = 0; i < n; i++) {
            this->solution[i] = s[i];
        }
        this->objectiveValue = obj;
    }
}

int GRASP::choseProbability(float *prob) {
    float p = 0.00f;
    float r = ((float) rand() / (RAND_MAX + 1));

    for(int i = 0; i < n; i++) {
        p += prob[i];
        if(r <= p) return i;
    }
    return -1;
}

float *GRASP::computeProbabilities(int *s, const int &nS, float *prob) {
    /*
     * Restricted Candidates List
     * */
    int nRCL = 0;
    int minCost = 1000000;
    int maxCost = 0;

    // Find min and max cost
    int costs[N_MAX];
    int cost;
    for(int i = 0; i < n; i++) {
        // Check if i is in the solution
        bool isIn = false;
        for(int q = 0; q < nS; q++) {
            if (s[q] == i + 1) {
                isIn = true;
                break;
            }
        }
        if(!isIn) {
            // Compute added cost
            cost = 0;
            for(int q = 0; q < nS; q++)
                cost += D[nS][q] * (F[s[q] - 1][i] + F[i][s[q] - 1]);
            costs[i] = cost;
            if(cost < minCost)
                minCost = cost;
            if(cost > maxCost)
                maxCost = cost;
        }
    }

    for(int i = 0; i < n; i++) {
        // Check if i is in the solution
        bool isIn = false;
        for(int q = 0; q < nS; q++) {
            if(s[q] == i + 1) {
                isIn = true;
                break;
            }
        }
        // Check if i is in the RCL
        if(!isIn && costs[i] <= minCost + alpha * (maxCost - minCost)) {
            // Apply probability
            prob[i] = 1.0f;
            nRCL++;
        } else
            prob[i] = 0.0f;
    }

    // Divide every probabilities by nRCL
    for(int i = 0; i < n; i++) {
        prob[i] /= nRCL;
    }

    if(nRCL == 0) std::cout << "nRCL null" << std::endl;

    return prob;
}
