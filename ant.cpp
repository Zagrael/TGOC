//
// Created by Sabrine Riahi on 2018-12-11.
//
#include <iostream>
#include "ant.h"

#include "problem.h"
#include "antexception.h"
#include <algorithm>

using namespace std ;

ant::ant(problem& d):data(d){
    tmpVisitedLength = 0;
    cstVisitedLength = 0;
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
            visitedPlaces.push_back(0);
            std::vector<int>::iterator tmp = placesStillToAffect.begin();
            while (tmp != placesStillToAffect.end()){
                if (*tmp == 0){
                    placesStillToAffect.erase(tmp);
                    break;
                }
                tmp++;
            }

            int dest = getNearCity(0);
            state = SEARCHING_PATH;
            currentOrigin = 0;
            currentDestination = dest;
            currentArcPos = 0;
            currentArcLength = data.distances[0][currentDestination];
            cout<<"currentDestination : "<<currentDestination;
            cout<<"currentArcLength : "<<currentArcLength<<endl;
            currentArcFlowSize = data.flows[0][currentDestination];
            currentArcCost = currentArcFlowSize*currentArcLength;

            break;
        }
        case SEARCHING_PATH:{
            // on a atteint currentDestination

            visitedPlaces.push_back(currentDestination);

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
                cstVisitedLength += tmpVisitedLength*flwVisitedLength;

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
            if (currentDestination == 0){
                // retourné au nid avec succès
                data.setPheromones(visitedPlaces[currentOrigin], visitedPlaces[currentDestination], cstVisitedLength);

                // sauver le résultat, changer de fourmi
                antException e;
                e.a = this;
                e.state = antException::TO_REGISTER;
                throw e;
            }

            // trouver la ville précédemment visitée et la passer en destination
            // mettre des phéromones sur l'arc parcouru
            data.setPheromones(visitedPlaces[currentOrigin], visitedPlaces[currentDestination], cstVisitedLength );
            currentOrigin = currentDestination;
            currentDestination --;
            currentArcLength = data.distances[visitedPlaces[currentOrigin]][visitedPlaces[currentDestination]];
            currentArcFlowSize = data.flows[visitedPlaces[currentOrigin]][visitedPlaces[currentDestination]];
            currentArcCost = currentArcLength*currentArcFlowSize;
            currentArcPos = currentArcLength;

            break;
        }
    }
}

int ant::getNearCity(int from){
    // roulette sur les chemins restants, pondérés par les phéromones
    float pheromoneSize = 0;
    for (std::size_t i = 0; i < placesStillToAffect.size(); i++){
        if (placesStillToAffect[i] == from)
            continue;
        pheromoneSize  += data.pheromones[from][placesStillToAffect[i]];
    }

    float found = float(rand()%int(pheromoneSize*10))/float(10)  ;
    float tmpPheromones = 0;
    std::size_t ii = 0;
    while (ii < placesStillToAffect.size()){
        if (placesStillToAffect[ii] == from){
            ii++;
            continue;
        }

        tmpPheromones  += data.pheromones[currentDestination][placesStillToAffect[ii]];

        if (tmpPheromones   > found)
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