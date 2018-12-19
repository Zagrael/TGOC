//
// Created by Sabrine Riahi on 2018-12-11.
//
#include <iostream>
#include "problem.h"
#include <cstdlib>
#include <fstream>
using namespace std ;

problem::problem(int nbVilles, float borne1, float borne2, float coeff)
        : nbPlaces(nbVilles), borneMax(borne1), borneMin(borne2), evaporation(coeff),
          distances(nbPlaces, std::vector<int>(nbPlaces, 0)),
          pheromones(nbPlaces, std::vector<float>(nbPlaces, borneMin)),
          flows(nbPlaces, std::vector<int>(nbPlaces, 0))
{
    const char* FILE_DATA = "../instances/bur26a.dat";

    ifstream in(FILE_DATA);

    // Number of data
    int n;
    in >> n;

    // Distances matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            in >> distances[i][j];
        }
    }

    // Flow matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            in >> flows[i][j];
        }
    }

    in.close();

    optimalLength = nbPlaces;
}

void problem::setPheromones(int i, int j, int obj){
    if (obj == 0)
        return;

    pheromones[i][j] += float(10000*optimalLength) / obj;

    if( pheromones[i][j] < borneMin) pheromones[i][j] = borneMin;
    if (pheromones[i][j] > borneMax) pheromones[i][j] = borneMax;

}

void problem::evaporate(){
    for (int i=0; i<nbPlaces; i++)
        for (int j=0; j<i; j++){
            pheromones[i][j] = pheromones[i][j]*(100-evaporation) /100;
            if (pheromones[i][j] < borneMin)
                pheromones[i][j] = borneMin;
        }
}
