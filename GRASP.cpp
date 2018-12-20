#include <random>

//
// Created by Aymerick on 15-12-18.
//

#include "GRASP.h"

GRASP::GRASP(std::string &dataName, float alpha) : QAP(dataName), alpha(alpha) {}

int *GRASP::run(const float &maxTimeSec) {
    std::cout << "Running GRASP..." << std::endl;
    clock_t t_init = clock();

    int *s = new int[n];
    int tabouSize = 250, stopAfterTime = 10, numberOfEquals = std::numeric_limits<int>::max();
    do {
        s = greedyProbability(s);
        // Tabu search only
        updateBest(&(run(vector<int>(s, s + n), n, tabouSize, stopAfterTime, numberOfEquals, 1)[0]));

        // Local search + tabu
//        s = localSearch(s);
//        updateBest(&(run(vector<int>(s, s + n), n, std::numeric_limits<int>::max(), 6, std::numeric_limits<int>::max())[0]));

        // Random + local search + tabu
//        std::shuffle(&s[0], &s[n], std::mt19937(std::random_device()()));
//        s = localSearch(s);
//        updateBest(&(run(vector<int>(s, s + n), n, std::numeric_limits<int>::max(), 6, std::numeric_limits<int>::max())[0]));
    } while((float)(clock() - t_init) / CLOCKS_PER_SEC <= maxTimeSec);

    std::cout << "GRASP ended after " << (clock() - t_init) / CLOCKS_PER_SEC << " sec" << std::endl;
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

vector<int> GRASP::run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals, int type) {
    //numberOfEquals: nombre de best sol egales avant qu'on change de voisinage
    //stop time en secondes
    vector<int> bestSol=startSol;//[copie OK]
    vector<int> currentSol(n);//[taille OK]
    vector<int> neighbor(12);
    int myType=type;// 0 ou 1

    currentSol=bestSol;//[copie OK]
    int currentCost;
    int bestCost=std::numeric_limits<int>::max();
    list<vector<int>>:: iterator it;


    list<vector<int>> tabou;

    bool canContinue=true;
    const long double sysTime = time(0);
    int numberOfBestEquals=0;

    while(canContinue) {
        canContinue = (/*(numberOfBestEquals<=numberOfEquals) and */(difftime(time(0), sysTime)<=stopAfterTime));
        if(numberOfBestEquals>numberOfEquals){
            myType=(myType+1)%2;
        }

        if (tabou.size() == tabouSize) {
            tabou.pop_back();
        }
        tabou.push_front(currentSol);

        if(myType==0){
            neighbor = bestNeighborNotInTabou0(tabou, currentSol);
        }else{
            neighbor = bestNeighborNotInTabou1(tabou, currentSol);
        }
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

    }


    return bestSol;
}

vector<int> GRASP::bestNeighborNotInTabou0(list<vector<int>> tabou, vector<int> sol) {
    //faire une transposition
    int n=sol.size();
    vector<int> bestNeighbor(n);
    vector<int> currentNeighbor(n);

    int bestCost=std::numeric_limits<int>::max();
    int currentCost=std::numeric_limits<int>::max();
    /*
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
    */

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(j>i and k==j){
                    currentNeighbor[k]=sol[i];
                    currentNeighbor[i]=sol[k];
                    //printVector(sol);
                    //printf("------------\n\n");
                    //printf("%d\n",sol[i]);
                }else{
                    currentNeighbor[k]=sol[k];
                    //printf("t%d\n",sol[i]);
                }
            }

            //printVector(currentNeighbor);
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
    }
    return bestNeighbor;
}

vector<int> GRASP::bestNeighborNotInTabou1(list<vector<int>> tabou, vector<int> sol) {
    int n=sol.size();
    vector<int> bestNeighbor(n);
    vector<int> currentNeighbor(n);

    int bestCost=std::numeric_limits<int>::max();
    int currentCost;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(j>i and k==j){
                    currentNeighbor[k]=sol[i];
                    currentNeighbor[i]=sol[k];

                }else{
                    currentNeighbor[k]=sol[k];
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

void GRASP::writeSolution(const std::string &method) {
    std::string fileName = "../results/" + dataName + "-" +  method + ".txt";

    // Read optimal value if file already exists
    std::ifstream in(fileName);
    int val = -1;
    if(in) {
        int k;
        in >> k;
        in >> val;
    }
    in.close();

    // Write solution found if better than last one
    if(val == -1 || objectiveValue < val) {
        std::ofstream out(fileName, std::ios::out | std::ios::trunc);

        out << n << "  " << objectiveValue << '\n';
        for (int i = 0; i < n; i++) {
            out << "  " << solution[i];
        }
        out.close();
    }
}
