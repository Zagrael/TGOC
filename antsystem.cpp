//
// Created by Sabrine Riahi on 2018-12-11.
//

#include "antsystem.h"
#include "problem.h"
#include "ant.h"
#include "antexception.h"
#include <algorithm>
#include <iostream>


antSystem::antSystem(int nbAnt, problem& d):data(d){
    for (int i=0; i<nbAnt; i++)
        ants.push_back(new ant(data));

    bestLength = 999999;
    pathCount = 0;
    curIteration = 0;
}

antSystem::~antSystem(){
    for (std::list<ant*>::iterator i = ants.begin(); i != ants.end(); i++)
        delete *i;
}

void antSystem::run(int n){
    for (curIteration=0; curIteration<n; curIteration++){
        // process each ant
        std::list<ant*>::iterator it = ants.begin();
        while (it != ants.end()){
            try{
                (*it)->frame();
            }catch(antException &e){

                // La fourmi a trouvé une solution
                // On notifie la solution, on crée une nouvelle fourmi et on supprime l'ancienne
                if (e.state == antException::TO_REGISTER)
                    notifySolution(e.a->tmpVisitedLength, e.a->visitedPlaces);

                if(bestLength <= data.optimalLength)
                    return;

                // on crée une nouvelle fourmi pour remplacer la fourmi courante
                *it = new ant(data);
                delete e.a;
            }
            it++;
        }

        // on évapore les phéromones toutes les 20 itérations
        // juste histoire de ne pas monopoliser toutes les ressources pour ça
        if (curIteration % 20 == 0)
            data.evaporate();

        if (curIteration%50==0)
            std::cout << "Meilleure longueur : " << bestLength << std::endl;
    }
}


void antSystem::notifySolution(int value, std::vector<int>& places){

    if (bestLength == -1){
        bestLength  = value;
        bestSolution = places;
    }else{

        pathCount ++;

        if (value < bestLength){

            bestLength = value;
            bestSolution = places;

            std::cout << "Nombre d'itérations : "<< curIteration << " " << "Meilleure longueur : " << bestLength << " "<<std::endl;
            std::cout<<"Taille de la solution : "<<places.size()<<std::endl;
            std::cout<<"Solution (Emplacements) : "<<std::endl;
            for (int i=0; i<int(places.size()); i++)
                std::cout << places[i] << " ";

            std::cout << std::endl;
        }
    }
}
