//
// Created by Sabrine Riahi on 2018-12-11.
//

#include "antsystem.h"
#include "problem.h"
#include "ant.h"
#include "antexception.h"
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;


antSystem::antSystem(int nbAnt, problem& d):data(d){
    for (int i=0; i<nbAnt; i++)
        ants.push_back(new ant(data));

    bestObj = 9999999999;
    pathCount = 0;
    curIteration = 0;
}

antSystem::~antSystem(){
    for (std::list<ant*>::iterator i = ants.begin(); i != ants.end(); i++)
        delete *i;
}

void antSystem::run(int n, double duration){

    std::clock_t start;
    start = std::clock();

    for (curIteration=0; curIteration<n; curIteration++){
        double durationstart = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        // process each ant
        std::list<ant*>::iterator it = ants.begin();
        while (it != ants.end()){
            try{
                (*it)->frame();
            }catch(antException &e){
                // La fourmi a trouvé une solution
                // On notifie la solution, on crée une nouvelle fourmi et on supprime l'ancienne
                if (e.state == antException::TO_REGISTER) {
                    notifySolution(e.a->objectif, e.a->affectedFactories);
                }

                if(bestObj <= data.optimalLength)
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
            std::cout << "Meilleur objectif : " << bestObj << std::endl;

        if (duration < durationstart){
            cout<<"Time elapsed : "<<durationstart<<" seconds"<<endl;
            cout<<"Number of iterations : "<<curIteration<<endl;
            break;
        }

        if(curIteration==n-1){
            cout<<"Time elapsed : "<<durationstart<<" seconds"<<endl;
            cout<<"Number of iterations : "<<curIteration+1<<endl;
        }
    }
}


void antSystem::notifySolution(int value, std::vector<int>& factories){

    if (bestObj == -1){
        bestObj  = value;
        bestSolution = factories;
    }else{

        pathCount ++;

        if (value < bestObj){

            bestObj = value;
            bestSolution = factories;

            std::cout << "Nombre d'itérations : "<< curIteration << " " << "Meilleur Objectif : " << bestObj << " "<<std::endl;
            std::cout<<"Taille de la solution : "<<factories.size()<<std::endl;
            std::cout<<"Solution (Usines) : "<<std::endl;
            for (int i=0; i<int(factories.size()); i++)
                std::cout << factories[i] << " ";

            std::cout << std::endl;
        }
    }
}

struct ThreadParams{
    int n;
    double duration;
};

void* antSystem :: runThread(void* args){
    ThreadParams *params=(ThreadParams*) args;
    run(params->n, params->duration);
    cout<<"One thread executed"<<endl;
}

int antSystem :: runThreads(int n, double duration, int numberOfThreads){
    ThreadParams params;
    params.n=n;
    params.duration=duration;

    for (int j = 0; j <numberOfThreads ; ++j) {


    }

    return 0;
}
