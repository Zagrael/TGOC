
//
// Created by arnaud on 11/12/18.
//

#include "Tabou.h"

Tabou::Tabou(const int &n, int F[][N_MAX], int D[][N_MAX], int time, int tabouSize):QAP(n, F, D){
    this->time=time;
    this->tabouSize=tabouSize;
}

int Tabou::computeObjectiveValue(vector<int> solution) {

    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {

            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];

        }
    }
    return value;
}

void Tabou::printVector(vector<int> v){
    vector<int>::iterator it;
    for(it=v.begin(); it!=v.end();it++){
        printf("%d, ",*it);
    }
    printf("%s: %d\n","cost",computeObjectiveValue(v));
}

bool Tabou:: continu(){
    /*if(time==0){
        return false;
    }else{
        time=time-1;
        return true;
    }*/
    return true;

}


bool Tabou:: isInTabou(list<vector<int>> tabou, vector<int> sol){

    list<vector<int>>:: iterator it;

    for(it=tabou.begin();it!=tabou.end();it++){
        if(*it==sol){
            return true;
        }
    }
    return false;
}

vector<int> Tabou:: bestNeighborNotInTabou(list<vector<int>> tabou, vector<int> sol){
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

int Tabou::run(int startSol[]) {
    vector<int> bestSol(startSol,startSol+n);//[copie OK]
    vector<int> currentSol(n);//[taille OK]
    vector<int> neighbor(12);
    currentSol=bestSol;//[copie OK]
    int currentCost=std::numeric_limits<int>::max();
    int bestCost=std::numeric_limits<int>::max();
    list<vector<int>>:: iterator it;


    list<vector<int>> tabou;

    bool canContinue=true;

    while(canContinue) {
        canContinue = continu();

        if (tabou.size() == tabouSize) {
            tabou.pop_back();
        }
        tabou.push_front(currentSol);

        neighbor = bestNeighborNotInTabou(tabou, currentSol);
        currentSol=neighbor;
        currentCost = computeObjectiveValue(currentSol);

        if(currentCost<bestCost){
            bestCost=currentCost;

            for(int i=0;i<n;i++){
                bestSol[i]=neighbor[i];
            }
        }
        for(int j=0;j<n;j++){
            currentSol[j]=neighbor[j];
        }

    }


    return 0;

}