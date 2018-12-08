#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char* FILE_DATA = "instances/nug12.dat";
const char* FILE_SOLUTION = "nug12.txt";

const int N_MAX = 1000;
int n;
int f[N_MAX][N_MAX];
int d[N_MAX][N_MAX];

int objectiveValue;
int sol[N_MAX];

bool readData() {
    freopen(FILE_DATA, "r", stdin);

    // Number of data
    scanf("%d", &n);
    cout << n << endl;

    // Distances matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", f[i] + j);
        }
    }

    // Flow matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", d[i] + j);
        }
    }

    return true;
}

bool readSolution() {
//    freopen(FILE_SOLUTION, "r", stdin);
//
//    // Number of data
//    scanf("%d", &n);
//    cout << n << endl;
//
//    // Objective value
//    scanf("%d", &objectiveValue);
//    cout << objectiveValue << endl;
//
//    // Solution vector
//    for(int i = 0; i < n; i++) {
//        scanf("%d", sol + i);
//    }

    ifstream in(R"(C:\Users\Aymerick\Documents\Ma1 - Ing Civil IG\Q1\Graphes et Optimisation combinatoire\Challenge\instances\nug12.sln)");

    if(!in) {
        cout << "File not open !" << endl;
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
    cout << "Hello, World!" << endl;

//    // Read inputs
//    readData();

    // Read the solution
    if(!readSolution()) return -1;

    cout << "n = " << n << endl;
    cout << "Objective value : " << objectiveValue << endl;
    cout << "Optimal solution :";
    for(int i = 0; i < n; i++) {
        cout << " " << sol[i];
    }

    return 0;
}