//
// Created by Sabrine Riahi on 2018-12-11.
//

#ifndef CHALLENGE_PROBLEM_H
#define CHALLENGE_PROBLEM_H

#include <vector>

/**
 * données du problème : distances + phéromones + flows
 */

class problem{

    public :
        problem(int, float, float, float);

        void setPheromones(int, int, int);

        void evaporate();

        int nbPlaces;
        float borneMax, borneMin;
        float evaporation;

        int optimalLength;

        // arcs
        // pheromones
        //flux
        std::vector<std::vector<int> > distances;
        std::vector<std::vector<float> > pheromones;
        std::vector<std::vector<int> > flows;
};

#endif //CHALLENGE_PROBLEM_H
