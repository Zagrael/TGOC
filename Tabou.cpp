
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
#include <mutex>

/*
 * meilleure taille de fenetre 250 et meilleur voisinage 1
 */

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

string printVector(vector<int> v){
    vector<int>::iterator it;
    string s="";
    for(it=v.begin(); it!=v.end();it++){
        //printf("%d, ",*it);
        s=s+std::to_string(*it);
        s+=", ";
    }
    //printf("%s: %d\n","cost",computeObjectiveValue(v));
    s+=std::to_string(computeObjectiveValue(v));
    s+="\n";
    return s;
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


vector<int> bestNeighborNotInTabou0(list<vector<int>> tabou, vector<int> sol){
    int n=sol.size();
    vector<int> bestNeighbor(n);
    vector<int> currentNeighbor(n);

    int bestCost=std::numeric_limits<int>::max();
    int currentCost;

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



vector<int> bestNeighborNotInTabou1(list<vector<int>> tabou, vector<int> sol){
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

vector<int> run(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals, int type) {
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

struct ThreadParams{
    vector<int> startSol;
    int n;
    int tabouSize;
    int stopAfterTime;
    int numberOfEquals;
    int type;
};

struct bestValue{
    int bestCost=numeric_limits<int>::max();
    vector<int> bestSol;
    std::mutex mtx;

    void writeNewSol(vector<int> sol){
        mtx.lock();
        int cost=computeObjectiveValue(sol);
        if(cost<bestCost){
            bestSol=sol;
            bestCost=cost;
        }
        mtx.unlock();

    }
};
bestValue bestValue;
void* runThread(void* args){
    ThreadParams *params=(ThreadParams*) args;
    vector<int> retour=run(params->startSol,params->n, params->tabouSize, params->stopAfterTime, params->numberOfEquals, params->type);

    bestValue.writeNewSol(retour);

}

vector<int> runWithThreads(vector<int> startSol, int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads, int type){
    ThreadParams params;
    params.n=n;
    params.tabouSize=tabouSize;
    params.type=type;
    params.stopAfterTime=stopAfterTime;
    params.numberOfEquals=numberOfEquals;

    vector<int> toto(n);

    if(startSol.empty()){
        for(int l=0;l<n;l++){
            toto[l]=l+1;
        }
        params.startSol= toto;
    }else{
        params.startSol=startSol;
    }

    pthread_t liste[numberOfThreads];

    for (int i = 0; i <numberOfThreads ; ++i) {
        params.type=(params.type+1)%2;
        ThreadParams paramsLoop=params;
        if(startSol.empty()){
            random_shuffle(toto.begin(),toto.end());
            paramsLoop.startSol=toto;
        }

        pthread_create(&liste[i], NULL, runThread, &paramsLoop);
        sleep(1);

    }

    for(int j=0;j<numberOfThreads;j++){
        pthread_join(liste[j],NULL);
    }

    return bestValue.bestSol;
}

