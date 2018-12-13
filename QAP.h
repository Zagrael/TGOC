//
// Created by Aymerick on 11-12-18.
//

#ifndef CHALLENGE_QAP_H
#define CHALLENGE_QAP_H

#include <iostream>
#include <string.h>


const int N_MAX = 1000;

class QAP {

public:

    QAP(const int &n, int F[][N_MAX], int D[][N_MAX]);

    virtual void run()=0;

    int solution[N_MAX];

protected:

    int computeObjectiveValue(const int &n, int solution[]);

    int F[N_MAX][N_MAX];
    int D[N_MAX][N_MAX];
    int n;

};


#endif //CHALLENGE_QAP_H
