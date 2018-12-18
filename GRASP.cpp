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
    objectiveValue = QAP::computeObjectiveValue(n, solution);
    delete[] s;
    return solution;
}

int *GRASP::greedyProbability(int *s) {

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
            if(cost > maxCost)
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

int *GRASP::localSearch(int *s) {

    int lastBestNeighbor = -1;
    int bestNeighbor = -1;
    int bestVal = -1;
    int val;

    bool locked = false;
    auto last = new int[n];
    for(int i = 0; i < n; i++) {
        last[i] = s[i];
    }

    int temp;
    auto *v = new int[n];
    clock_t t_init = clock();
    float tMax = 10.0f;
    do {
        // Find neighbors
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n; j++) {
                v[j] = s[j];
            }
            v[i] = s[i + 1];
            v[i + 1] = s[i];

            // Test neighbor
            val = QAP::computeObjectiveValue(n, v);
            if (bestVal == -1 || val < bestVal) {
                bestNeighbor = i;
                bestVal = val;
            }
        }

        if(bestVal <= QAP::computeObjectiveValue(n, s) && (!equals(s, last, n) || lastBestNeighbor == -1)) {
            // Update current
            temp = s[bestNeighbor];
            s[bestNeighbor] = s[bestNeighbor + 1];
            s[bestNeighbor + 1] = temp;

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

    } while(!locked && (float) clock() - t_init <= tMax);

    return s;
}

void GRASP::updateBest(int *s) {
    int obj = QAP::computeObjectiveValue(n, s);
    if(isAdmissible(n,s) && obj < objectiveValue) {
        for(int i = 0; i < n; i++) {
            solution[i] = s[i];
        }
        objectiveValue = obj;
    }
}

vector<int> GRASP::bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol) {
    int n=sol.size();
    vector<int> bestNeighbor(n);
    vector<int> currentNeighbor(n);

    int bestCost=std::numeric_limits<int>::max();
    int currentCost=std::numeric_limits<int>::max();

    for(int i=0;i<n-1;i++){//pour chaque voisin
        for(int j=0;j<n;j++){//on construit le voisin

            if(i==j){
                currentNeighbor[j]=sol[j+1];
                currentNeighbor[j+1]=sol[j];
                j++;
            }else{
                currentNeighbor[j]=sol[j];
            }
        }

        if(not isInTabou(tabou, currentNeighbor)){
            currentCost=computeObjectiveValue(currentNeighbor);

            if(currentCost<bestCost){
                bestCost=currentCost;

                for(int k=0; k<n;k++){
                    bestNeighbor[k]=currentNeighbor[k];
                }
            }
        }
    }
    return bestNeighbor;
}

bool GRASP::isInTabou(list<vector<int>> tabou, vector<int> sol) {
    list<vector<int>>:: iterator it;

    for(it=tabou.begin();it!=tabou.end();it++){
        if(*it==sol){
            return true;
        }
    }
    return false;
}

vector<int> GRASP::run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals) {
    //stop time en secondes
    vector<int> bestSol=startSol;//[copie OK]
    vector<int> currentSol(n);//[taille OK]
    vector<int> neighbor(12);
    currentSol=bestSol;//[copie OK]
    int currentCost=std::numeric_limits<int>::max();
    int bestCost=std::numeric_limits<int>::max();
    list<vector<int>>:: iterator it;


    list<vector<int>> tabou;

    bool canContinue=true;
    const long double sysTime = time(0);
    int numberOfBestEquals=0;

    while(canContinue) {
        canContinue = ((numberOfBestEquals<=numberOfEquals) and (difftime(time(0), sysTime)<=stopAfterTime));

        if (tabou.size() == tabouSize) {
            tabou.pop_back();
        }
        tabou.push_front(currentSol);

        neighbor = bestNeighborNotInTabou(tabou, currentSol);
        currentSol=neighbor;
        currentCost = computeObjectiveValue(currentSol);

        if(currentCost<bestCost){
            bestCost=currentCost;
            numberOfBestEquals=0;

            for(int i=0;i<n;i++){
                bestSol[i]=neighbor[i];
            }
        }else{
            numberOfBestEquals++;
        }
        for(int j=0;j<n;j++){
            currentSol[j]=neighbor[j];
        }
        //printVector(bestSol);
    }

    return bestSol;
}

int GRASP::computeObjectiveValue(vector<int> solution) {

    int value = 0;
    int n=solution.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {

            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];

        }
    }
    return value;
}


void GRASP::printVector(vector<int> v){
    vector<int>::iterator it;
    for(it=v.begin(); it!=v.end();it++){
        printf("%d, ",*it);
    }
    printf("%s: %d\n","cost",computeObjectiveValue(v));
}