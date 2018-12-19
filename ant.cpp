//
// Created by Sabrine Riahi on 2018-12-11.
//
#include <iostream>
#include "ant.h"

#include "problem.h"
#include "antexception.h"
#include <algorithm>
#include "math.h"

#include "QAP.h"

using namespace std ;

extern const int d[N_MAX][N_MAX];
extern const int f[N_MAX][N_MAX];

ant::ant(problem& d):data(d){
    tmpVisitedLength = 0;
    objectif = 0;
    currentArcPos = -1;
    currentDestination = 0;
    currentOrigin = 0;
    state = NOTHING;

    for (int i=0; i<data.nbPlaces; i++)
        placesStillToAffect.push_back(i);
}

void ant::frame(){
    switch(state){
        case SEARCHING_PATH:
            tmpVisitedLength ++;
        case RETURNING:
            currentArcPos++;
            if (currentArcPos >= currentArcLength)
                findNextSearchDestination();
            break;
        case NOTHING:
            findNextSearchDestination();
            break;
    }
}

void ant::findNextSearchDestination(){
    switch(state){
        case NOTHING:{
            //visitedPlaces.push_back(0);
            randomnumber = rand()%data.nbPlaces;
            visitedPlaces.push_back(randomnumber);
            std::vector<int>::iterator tmp = placesStillToAffect.begin();
            while (tmp != placesStillToAffect.end()){
                if (*tmp == randomnumber){
                    placesStillToAffect.erase(tmp);
                    break;
                }
                tmp++;
            }

            int dest = getNearCity(randomnumber);
            state = SEARCHING_PATH;
            currentOrigin = randomnumber;
            currentDestination = dest;
            currentArcPos = randomnumber;
            currentArcLength = data.distances[randomnumber][currentDestination];
            currentArcFlowSize = data.flows[randomnumber][currentDestination];
            currentArcCost = currentArcFlowSize*currentArcLength;

            break;
        }
        case SEARCHING_PATH:{
            // on a atteint currentDestination

            visitedPlaces.push_back(currentDestination);

            //erase currentDestination des lieux à affecter
            std::vector<int>::iterator tmp = placesStillToAffect.begin();
            while (tmp != placesStillToAffect.end()){
                if (*tmp == currentDestination){
                    placesStillToAffect.erase(tmp);
                    break;
                }
                tmp++;
            }

            //std::remove(placesStillToAffect.begin(), placesStillToAffect.end(), currentDestination );
            //placesStillToAffect.resize(placesStillToAffect.size() -1);

            if (placesStillToAffect.size() == 0){
                // plus rien à affecter, le chemin est complet
                // on revient vers le nid
                tmpVisitedLength += data.distances[currentDestination][0];
                flwVisitedLength += data.flows[currentDestination][0];

                state = RETURNING;
                currentOrigin =  int(visitedPlaces.size())-1;
                currentDestination = int(visitedPlaces.size())-2;
                currentArcLength = data.distances[visitedPlaces[currentOrigin]][visitedPlaces[currentDestination]];
                currentArcFlowSize = data.flows[visitedPlaces[currentOrigin]][visitedPlaces[currentDestination]];
                currentArcCost = currentArcFlowSize*currentArcLength;
                currentArcPos = currentArcLength;
                return;
            }

            int dest = getNearCity(currentDestination);
            currentOrigin = currentDestination;
            currentDestination = dest;
            currentArcLength = data.distances[currentOrigin][currentDestination];
            currentArcFlowSize = data.flows[currentOrigin][currentDestination];
            currentArcCost = currentArcFlowSize*currentArcLength;
            currentArcPos = 0;
            break;
        }
        case RETURNING:{

                // on a trouvé une solution optimale = visitedPlaces
                // on change cette solution pour avoir les usines en fonction des emplacements = affectedFactories

                int n = 0;
                for (vector<int>::const_iterator i = visitedPlaces.begin(); i != visitedPlaces.end(); ++i) {
                    std::vector<int>::iterator tmp = visitedPlaces.begin();
                    while (tmp != visitedPlaces.end()){
                        if (visitedPlaces[*tmp] == n){
                            affectedFactories.push_back((*tmp) + 1);
                            break;
                        }
                        tmp++;
                    }

                    n++;
                }

                //conversion en un tableau
                int tab = 0;

                for (vector<int>::const_iterator i = affectedFactories.begin(); i != affectedFactories.end(); ++i) {
                    objectiftab[tab] = *i;
                    tab++;
                }

                for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                        objectif += data.distances[i][j] * data.flows[objectiftab[i] - 1][objectiftab[j] - 1];
                    }
                }

                // retournée au nid avec succès
                data.setPheromones(visitedPlaces[currentOrigin], visitedPlaces[currentDestination], objectif);

                // sauver le résultat, changer de fourmi
                antException e;
                e.a = this;
                e.state = antException::TO_REGISTER;
                throw e;

        }
    }
}


float ant :: visibility(int i, int j){
  float visibility = 1/float((data.flows[i][j]+data.flows[j][i]));
  return visibility;
 }


int ant::getNearCity(int from){
    // roulette sur les chemins restants, pondérés par les phéromones
    //pheromoneSize = total des phéromones entre le lieu actuel et les autres destinations possibles
    float pheromoneSize = 0;
    float proba = 0 ;
    float alpha = 1 ;
    float beta = 0.2 ;
    vector<float> probavector;

    for (std::size_t i = 0; i < placesStillToAffect.size(); i++){
        if (placesStillToAffect[i] == from)
            continue;
        if (data.flows[from][placesStillToAffect[i]]==0 || data.flows[placesStillToAffect[i]][from]==0)
            continue;
        pheromoneSize  = data.pheromones[from][placesStillToAffect[i]];
        probavector.push_back(pow(pheromoneSize, alpha) + pow(visibility(from,placesStillToAffect[i]), beta));
        proba += pow(pheromoneSize, alpha) + pow(visibility(from,placesStillToAffect[i]), beta);
    }

    for (int j = 0 ; j<probavector.size() ; j++){
        probavector[j] = probavector[j]/proba ;
    }

    float number = 0;
    srand(time(NULL));
    number = (float)rand() / (float)RAND_MAX;

    float tmp = 0;
    std::size_t ii = 0;

    while (ii < placesStillToAffect.size()){
        if (placesStillToAffect[ii] == from){
            ii++;
            continue;
        }

        tmp += probavector[ii];

        if (tmp > number)
            break;

        ii ++;
    }
    if (ii == placesStillToAffect.size()){
        // aucune solution acceptable, détruire la fourmi courante
        antException e;
        e.a = this;
        e.state = antException::TO_DELETE;
        throw e;
    }

    return placesStillToAffect[ii];
}