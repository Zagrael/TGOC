//
// Created by arnaud on 11/12/18.
//

#include "Tabou.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <queue>
#include <vector>
#include <list>

using namespace std;


int stopAfter=1000;

void getNeighbors(vector<vector<int >> &neighbors, vector<int> &sol){
    neighbors.clear();

    for(int j=0;j<sol.size(); j++){
        vector<int> neighbor(sol.size());
        for(int i=0;i<sol.size()-1; i++){

            if(i==j){
                neighbor[i]=sol[i+1];
                neighbor[i+1]=sol[i];
                i++;
            }else{
                neighbor[i]=sol[i];
            }
        }
        neighbors.push_back(neighbor);
    }

}

void initSol(vector<int> &sol, int minValue, int maxValue){
    sol.clear();
    //??Commence a 1 ou a 0
    for(int i=0; i<sol.size();i++){
        sol[i]=i+1;
    }

}

int cost(vector<int> const& data){
    //todo
    return 0;
}

int getBestSol(vector<vector<int>> const& neighbors){
    int bestSolIndex=0;
    for(int i=1;i<neighbors.size();i++){
        if(cost(neighbors[i])<cost(neighbors[bestSolIndex])){
            bestSolIndex=i;
        }
    }
    return bestSolIndex;
}



void run(vector<int> const& d, vector<int> const& f, vector<int>&bestSol, bool startFromSol, int nbrIter, int tabouSize){

    vector<int> currentSol;
    list<vector<int >> tabou;
    vector<vector<int >> neighbors;

    if(! startFromSol){
        initSol(bestSol, NULL, NULL);
    }
    currentSol=bestSol;

    while(nbrIter>0){

        getNeighbors(neighbors, bestSol);

        for(int i=0; i<=neighbors.size();i++){
            vector<int> data=neighbors[i];
            for(int j=0;j<=tabou.size();j++){
                list<vector<int >>::iterator it= tabou.begin();
                advance(it, j);
                if(data == *it ){
                    neighbors.erase(neighbors.begin()+i);
                }
            }

        }
        int indexBestSol=getBestSol(neighbors);
        if(tabou.size()==tabouSize){
            tabou.pop_back();
            tabou.push_front(currentSol);
        }
        currentSol=neighbors[indexBestSol];
        if(cost(currentSol)<cost(bestSol)){
            bestSol=currentSol;
        }


        nbrIter--;
    }

}