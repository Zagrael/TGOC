//
// Created by Aymerick on 15-12-18.
//

#include "GRASP.h"

GRASP::GRASP(std::string &dataName, float alpha) : QAP(dataName), alpha(alpha) {}

int *GRASP::run(const float &maxTimeSec) {
    std::cout << "Running GRASP..." << std::endl;
    clock_t t_init = clock();

    int *s = new int[n];
    do {
        updateBest(localSearch(greedyProbability(s)));
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxTimeSec);

    std::cout << "End of GRASP !" << std::endl;
    objectiveValue = computeObjectiveValue(n, solution);
    delete[] s;
    return solution;
}

const int *GRASP::greedyProbability(int *s) {

    s[0] = rand() % n + 1;
    auto *prob = new float[n];
    for(int i = 1; i < n; i++) {
        try {
            computeProbabilities(s, i, prob);
            s[i] = choseProbability(prob) + 1;
        } catch(const char *msg) {
            std::cerr << msg << std::endl;
        }
    }
    delete[] prob;
    return s;
}

float *GRASP::computeProbabilities(int *s, const int &nS, float *p) {

    int nRCL = 0;
    int minCost = -1;
    int maxCost = -1;

    // Find min and max costs
    int *costs = new int[n];
    int cost;
    auto *isIn = new bool[n];
    for(int i = 0; i < n; i++) {
        // Check if i is in the solution
        isIn[i] = false;
        for(int q = 0; q < nS; q++) {
            if (s[q] == i + 1) {
                isIn[i] = true;
                break;
            }
        }
        if(!isIn[i]) {
            // Compute added cost
            cost = 0;
            for(int q = 0; q < nS; q++)
                cost += D[nS][q] * (F[s[q] - 1][i] + F[i][s[q] - 1]);
            costs[i] = cost;
            if(cost < minCost || minCost == -1)
                minCost = cost;
            if(cost > maxCost || maxCost == -1)
                maxCost = cost;
        }
    }

    // Fill the Restricted Candidates List with their probability
    for(int i = 0; i < n; i++) {
        // Check if i is in the RCL
        if(!isIn[i] && costs[i] <= minCost + alpha * (maxCost - minCost)) {
            // Apply probability
            p[i] = 1.0f;
            nRCL++;
        } else
            p[i] = 0.0f;
    }

    delete[] costs;

    if(nRCL == 0) throw "Error in GRASP::computeProbabilities(s, nS) : RCL is empty !";

    // Divide every probabilities by nRCL
    for(int i = 0; i < n; i++) {
        p[i] /= nRCL;
    }

    return p;
}

int GRASP::choseProbability(float *p) {
    float pc = 0.00f;
    float r = ((float) rand() / (RAND_MAX + 1));

    for(int i = 0; i < n; i++) {
        pc += p[i];
        if(r <= pc) return i;
    }

    throw "Error in GRASP::choseProbability(p) : Could not chose any probability !";
}

const int *GRASP::localSearch(const int *s) {

    int lastBestNeighbor = -1;
    int bestNeighbor = -1;
    int bestVal = -1;
    int val;

    bool locked = false;
    int *current = new int[n];
    auto last = new int[n];
    for(int i = 0; i < n; i++) {
        current[i] = s[i];
        last[i] = s[i];
    }

    int temp;
    auto *v = new int[n];
    do {
        // Find neighbors
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n; j++) {
                v[j] = current[j];
            }
            v[i] = current[i + 1];
            v[i + 1] = current[i];

            // Test neighbor
            val = computeObjectiveValue(n, v);
            if (bestVal == -1 || val < bestVal) {
                bestNeighbor = i;
                bestVal = val;
            }
        }

        if(bestVal <= computeObjectiveValue(n, current) && (!equals(current, last, n) || lastBestNeighbor == -1)) {
            // Update current
            temp = current[bestNeighbor];
            current[bestNeighbor] = current[bestNeighbor + 1];
            current[bestNeighbor + 1] = temp;

            // Update last
            if(lastBestNeighbor != -1) {
                temp = last[lastBestNeighbor];
                last[lastBestNeighbor] = last[lastBestNeighbor + 1];
                last[lastBestNeighbor + 1] = temp;
            }
            lastBestNeighbor = bestNeighbor;
        } else {
            locked = true;
        }

    } while(!locked);

    return current;
}

void GRASP::updateBest(const int *s) {
    int obj = computeObjectiveValue(n, s);
    if(isAdmissible(n,s) && obj < objectiveValue) {
        for(int i = 0; i < n; i++) {
            solution[i] = s[i];
        }
        objectiveValue = obj;
    }
}
