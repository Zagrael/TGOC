//
// Created by Sabrine Riahi on 2018-12-11.
//

#ifndef CHALLENGE_ANTSYSTEM_H
#define CHALLENGE_ANTSYSTEM_H


#include <list>
#include <vector>

class problem;
class ant;

/**
 * moteur d'algorithme
 */
class antSystem {

    public :
        antSystem(int, problem&);
        ~antSystem();

        // on déroule l'exécution sur n itérations

        void run(int n, double duration);
        int pathCount;

    private :
        // fourmis gérées
        std::list<ant*> ants;

        // données du problème

        problem &data;

        // meilleure solution trouvée
        long bestObj;
        std::vector<int> bestSolution;

        int curIteration;

        void notifySolution(int , std::vector<int>& );

    };


#endif //CHALLENGE_ANTSYSTEM_H
