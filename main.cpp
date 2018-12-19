#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <pthread.h>
#include <unistd.h>
#include "Tabou.h"



using namespace std;

string FILE_DATA ;//= "../instances/nug12.dat";
//char* FILE_SOLUTION = "../instances/nug12.sln";

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
/*
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
*/

void tests(){
    vector<string> files{"bur26a", "chr18a", "els19", "kra32", "nug12", "nug30", "sko42", "tai15a", "tai15b", "tai100a"};
    int tabouSize=250;
    ofstream myfile;
    for(int i=0;i<10;i++){
        myfile.open ("dataWithChange.txt", std::ios_base::app);
        FILE_DATA=std::string("../instances/")+files[i]+std::string(".dat");
        readData();
        myfile << std::string("fichier: ")+files[i].c_str()+std::string("\n");

        vector<int>sol(n);
        for(int i=0;i<n;i++){
            sol[i]=i+1;
        }

        myfile << "       voisinage 0: ";
        myfile << computeObjectiveValue(run(sol, n, tabouSize, 60,300 ,0));
        myfile << "\n";
        myfile << "       voisinage 1: ";
        myfile << computeObjectiveValue(run(sol, n, tabouSize, 60,300 ,1));
        myfile << "\n";

        myfile << "fin fichier --------------\n";
        myfile.close();

    }
    printf("finis !");
}



int main() {
    cout << "Hello, World!" << endl;
    //FILE_SOLUTION = "../instances/nug12.sln";
    /*readData();
    readSolution();
    vector<int>sol(n);
    for(int i=0;i<n;i++){
        sol[i]=i+1;
    }*/
    tests();






    return 0;
}