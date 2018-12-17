#include <iostream>
#include <fstream>
#include <string>

#include "problem.h"
#include "antsystem.h"
#include <cstdlib>

using namespace std;

const char* FILE_DATA = "../instances/tai100a.dat";
const char* FILE_SOLUTION = "../instances/tai100a.sln";

const int N_MAX = 1000;
int n;
int f[N_MAX][N_MAX];
int d[N_MAX][N_MAX];

int objectiveValue;
int sol[N_MAX];

bool readData() {
    ifstream in(FILE_DATA);

    if(!in) {
        cout << "Data file not open !" << endl;
        return false;
    }

    // Number of data
    in >> n;

    // Distances matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            in >> d[i][j];
        }
    }

    // Flow matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            in >> f[i][j];
        }
    }

    in.close();
    return true;
}

bool readSolution() {
    ifstream in(FILE_SOLUTION);

    if(!in) {
        cout << "Solution file not open !" << endl;
        return false;
    }

    // Number of data
    in >> n;

    // Objective value
    in >> objectiveValue;

    // Solution vector
    for(int i = 0; i < n; i++) {
        in >> sol[i];
    }

    in.close();
    return true;
}

int main(int argc, char **argv) {
    cout << "Hello, World!" << endl;

    // Read inputs
    if(!readData()) return -1;
    cout << "Distances matrix : " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << " " << d[i][j];
        }
        cout << endl;
    }
    cout << "Flow matrix : " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << " " << f[i][j];
        }
        cout << endl;
    }

    // Read the solution
    if(!readSolution()) return -1;
    cout << "n = " << n << endl;
    cout << "Objective value : " << objectiveValue << endl;
    cout << "Optimal solution :";
    for(int i = 0; i < n; i++) {
        cout << " " << sol[i];
    }

    // villes, borne sup, borne inf, coeff d'évaporation en %

    int nbIterations = 3000000;
    double time = 10.0;
    int nbFourmis = 100000/n;
    srand(0);
    //586 problem p(n, 50, 1, 10);
    //596 en 3 sec problem p(n, 50, 1, 20);
    //596 problem p(n, 250, 1, 15);
    //590 problem p(n, 100, 1, 5);
    //590 problem p(n, 400, 1, 10);
    //582 problem p(n, 300, 1, 15);
    //592 problem p(n, 250, 1, 10);
    //586 problem p(n, 250, 1, 5);
    //586 direct, nbF = 5000 problem p(n, 10, 1, 0.1f); problem p(n, 10, 1, 1);problem p(n, 10, 1, 0.1f)
    problem p(n, 1000*n, 1, 1/n);

    cout<<"\n";
    cout << "Données enregistrées" << endl;

    // nombre de fourmis
    antSystem sys(nbFourmis, p);

    cout << "Système créé" << endl;

    // unités de temps
    sys.run(nbIterations, time);

    cout << sys.pathCount << "chemins testés" << endl;
}