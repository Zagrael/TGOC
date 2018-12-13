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
    const char* FILE_DATA = "../instances/nug30.dat";

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


    /*for (int i = 0; i<nbPlaces; i++){
        distances[i][i] = 0;
        for (int j = i+1; j<nbPlaces; j++)
            distances[i][j] = distances[j][i] = rand()%100;
    }*/

    // solution optimale
    /*for (int i=0; i<nbPlaces; i++)
        distances[i][(i+1)%nbPlaces] = distances[(i+1)%nbPlaces][i] = 1 ;*/

    optimalLength = nbPlaces;
}

void problem::setPheromones(int i, int j, int obj){
    float ph = 100.f*optimalLength / (obj + 1 - optimalLength);

    pheromones[i][j] += ph;

    if( pheromones[i][j] < borneMin) pheromones[i][j] = borneMin;
    if (pheromones[i][j] > borneMax) pheromones[i][j] = borneMax;

    pheromones[j][i] = pheromones[i][j];
}

void problem::evaporate(){
    for (int i=0; i<nbPlaces; i++)
        for (int j=0; j<i; j++){
            pheromones[i][j] = pheromones[i][j]*(100-evaporation) /100;
            if (pheromones[i][j] < borneMin)
                pheromones[i][j] = borneMin;

            pheromones[j][i] = pheromones[i][j];
        }
}

// int nbPlaces;
// int borneMax = 500, borneMin = 2;
// evaporation = 1%

// optimalLength