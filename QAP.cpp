//
// Created by Aymerick on 11-12-18.
//

#include "QAP.h"


QAP::QAP(const int &n, int F[][N_MAX], int D[][N_MAX]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            this->F[i][j]=F[i][j];
            this->D[i][j]=D[i][j];
        }
    }
    this->n=n;

}

int QAP::computeObjectiveValue(const int &n, int solution[]) {

    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {

            value += D[i][j] * F[solution[i] - 1][solution[j] - 1];

        }
    }
    return value;
}