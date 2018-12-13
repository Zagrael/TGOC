//
// Created by Sabrine Riahi on 2018-12-13.
//

#ifndef CHALLENGE_QAP_H
#define CHALLENGE_QAP_H

#include <iostream>

using namespace std ;

const int N_MAX = 1000;

class QAP {

public:
    static int computeObjectiveValue(const int&, int[], int[][N_MAX], int[][N_MAX]);
    static int computeObjectiveValueVector(int, vector<int>, int[][N_MAX], int[][N_MAX]);
};


#endif //CHALLENGE_QAP_H