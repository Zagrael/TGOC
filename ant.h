//
// Created by Sabrine Riahi on 2018-12-11.
//

#ifndef CHALLENGE_ANT_H
#define CHALLENGE_ANT_H

#include <vector>

class problem;

/**
 * une fourmi
 */
class ant{

    public :
        ant(problem&);

        // liste des villes visitées / à visiter
        std::vector<int> visitedPlaces;
        std::vector<int> placesStillToAffect;

        // compteur de longueur du chemin parcouru
        long tmpVisitedLength;

        // compteur du flow du chemin parcouru
        long flwVisitedLength;

        // compteur du coût du chemin parcouru
        long cstVisitedLength;

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
        long currentArcSize;

        // position sur l'arc actuellement parcouru
        long currentArcPos;

        // première extrémité de l'arc actuellement parcouru
        int currentOrigin;

        // seconde extrémité de l'arc actuellement parcouru
        int currentDestination;

        // flux de la première extrémité de l'arc actuellement parcouru
        int currentArcFlowSize;

        // coût de l'arc
        long currentArcCost;



        // référence sur les données du problème
        problem& data;

        void findNextSearchDestination();

        int getNearCity(int);
};




#endif //CHALLENGE_ANT_H
