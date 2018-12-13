#include <iostream>
#include <fstream>
#include <string>

#include "common.h"
#include "GRASP.h"

using namespace std;

const char* FILE_DATA = "../instances/nug12.dat";
const char* FILE_SOLUTION = "../instances/nug12.sln";

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

int main() {
    float maxTime = 10.0f;
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

    // Apply GRASP algorithm
    float alpha = 0.2;
    GRASP grasp = GRASP(alpha, n, f, d);
    int* solution = grasp.run(maxTime);
    cout << "Solution found with GRASP :";
    for(int i = 0; i < n; i++) {
        cout << " " << solution[i];
    }
    cout << endl <<  "Objective found with GRASP : " << grasp.getObjectiveValue() << endl;

    // Read the solution
    if(!readSolution()) return -1;
    cout << "Optimal solution :";
    for(int i = 0; i < n; i++) {
        cout << " " << sol[i];
    }
    cout << endl << "Objective value : " << objectiveValue << endl;

    return 0;
}