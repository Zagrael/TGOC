
//
// Created by arnaud on 11/12/18.
//

using namespace std;
#include <vector>
#include <cstdio>
#include <list>
#include <limits>
#include "main.h"
#include <ctime>
#include <pthread.h>
#include <random>
#include <algorithm>
#include <unistd.h>

int computeObjectiveValue(vector<int> solution) {

    int value = 0;
    int n=solution.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {

            value += d[i][j] * f[solution[i] - 1][solution[j] - 1];

        }
    }
    return value;
}

void printVector(vector<int> v){
    vector<int>::iterator it;
    for(it=v.begin(); it!=v.end();it++){
        printf("%d, ",*it);
    }
    printf("%s: %d\n","cost",computeObjectiveValue(v));
}



bool isInTabou(list<vector<int>> tabou, vector<int> sol){

    list<vector<int>>:: iterator it;

    for(it=tabou.begin();it!=tabou.end();it++){
        if(*it==sol){
            return true;
        }
    }
    return false;
}

vector<int> bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol){
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

vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals) {
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

struct ThreadParams{
    vector<int> startSol;
    int n;
    int tabouSize;
    int stopAfterTime;
    int numberOfEquals;
};

void* runThread(void* args){
    //	long timeout=(long) arg;
    ThreadParams *params=(ThreadParams*) args;
    printf("sol init: ");
    printVector(params->startSol);
    vector<int> retour=run(params->startSol,params->n, params->tabouSize, params->stopAfterTime, params->numberOfEquals);
    printf("%s\n", "Un thread a finis");
    printVector(retour);
    printf("%s\n", "---------\n");

}

int runWithThreads(int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads){
    ThreadParams params;
    params.n=n;
    params.tabouSize=tabouSize;
    params.stopAfterTime=stopAfterTime;
    params.numberOfEquals=numberOfEquals;
    //vector<int> startSolV(startSol,startSol+n);
    vector<int> toto(n);
    for(int l=0;l<n;l++){
        toto[l]=l+1;
    }
    params.startSol= toto;

    pthread_t liste[numberOfThreads];
    /*
    ThreadParams params1=params;

    random_shuffle(toto.begin(), toto.end());
    params1.startSol=toto;

    printVector(params.startSol);
    printVector(params1.startSol);*/


    for (int i = 0; i <numberOfThreads ; ++i) {
        ThreadParams paramsLoop=params;
        random_shuffle(toto.begin(),toto.end());
        paramsLoop.startSol=toto;
        pthread_create(&liste[i], NULL, runThread, &paramsLoop);
        sleep(1);

    }

    for (int j = 0; j <numberOfThreads ; ++j) {
        pthread_join(liste[j], NULL);

    }

    printf("terminé !\n");
    return 0;

}