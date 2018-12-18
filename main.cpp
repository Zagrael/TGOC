#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include "Tabou.h"



using namespace std;

const char* FILE_DATA = "../instances/bur26a.dat";
const char* FILE_SOLUTION = "../instances/bur26a.sln";

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

int computeObjectiveValue(const int &n, int solution[]) {
    int value = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            value += d[i][j] * f[solution[i] - 1][solution[j] - 1];
        }
    }
    return value;
}

int main() {
    cout << "Hello, World!" << endl;

    readData();
    readSolution();
    int sol[]={1,2,3,4,5,6,7,8,9,10,11,12};
    //Tabou tabou(n, f, d, 100000 ,700);
    //int retour=tabou.run(sol);

    //int r=run(sol, n, 700);
    //int runWithThreads(int startSol[], int n, int tabouSize, int stopAfterTime, int numberOfEquals, int numberOfThreads){
    runWithThreads(n, 70, 30, std::numeric_limits<int>::max(), 12);


    /*
    const long double sysTime1 = time(0);
    cout << sysTime1 << endl;
    sleep(10);
    const long double sysTime2 = time(0);
    cout << sysTime2 << endl;

    cout << difftime(sysTime2,sysTime1) << endl;
    */



    return 0;
}