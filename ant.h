//
// Created by Sabrine Riahi on 2018-12-11.
//

#ifndef CHALLENGE_ANT_H
#define CHALLENGE_ANT_H

#include <vector>
#include "QAP.h"

class problem;

/**
 * une fourmi
 */
class ant{

    public :
        ant(problem&);

        // liste des lieux visités / à visiter
        std::vector<int> visitedPlaces;
        std::vector<int> placesStillToAffect;
        std::vector<int> affectedFactories;
        int objectiftab[N_MAX];

        // compteur du coût du chemin parcouru
        int objectif;

        // états possibles pour une fourmi

        enum {
            SEARCHING_PATH,
            RETURNING,
            NOTHING
        };

        // état de la fourmi, en route, en retour ..
        int state;

        // faire évoluer la fourmi à chaque itération
        void frame();

    protected :
        // données courantes

        // longueur de l'arc actuellement parcouru
        long currentArcLength;

        // position sur l'arc actuellement parcouru
        long currentArcPos;

        // première extrémité de l'arc actuellement parcouru
        int currentOrigin;

        // seconde extrémité de l'arc actuellement parcouru
        int currentDestination;

        int randomnumber;



        // référence sur les données du problème
        problem& data;

        void findNextSearchDestination();
        float visibility(int, int);
        int getNearCity(int);
};




#endif //CHALLENGE_ANT_H
