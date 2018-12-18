#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include "GRASP.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main() {

    string dataName = "nug12";
    srand(time(NULL));

    string files[] = {"bur26a", "chr18a", "els19", "kra32", "nug12", "nug30", "sko42", "tai15a", "tai15b", "tai100a"};
    // Uncomment these lines before using the executable !
//    char rep;
//    do {
//        system("CLS");
//        cout << "Data name (bur26a, chr18a, els19, kra32, nug12, nug30, sko42, tai15a, tai15b, tai100a, ...) : ";
//        cin >> dataName;
    /********************************************/

    // Uncomment this line to run all files
    for(int zk = 0; zk < files->length(); zk++) {
        dataName = files[zk];
        cout << "Trying " << dataName << endl;
    /*********************************************/

        /*
         * Apply GRASP algorithm
         * */
        try {
            float alphaGRASP = 0.6;
            float maxTimeGRASP = 60.0f;
            GRASP grasp(dataName, alphaGRASP);
            int *solutionGRASP = grasp.run(maxTimeGRASP);
            cout << "Solution found with GRASP :";
            for (int i = 0; i < grasp.getN(); i++) {
                cout << " " << solutionGRASP[i];
            }
            cout << endl << "Admissible solution ? " << (QAP::isAdmissible(grasp.getN(), solutionGRASP) ? "YES" : "NO")
                 << endl;
            cout << "Objective found with GRASP : " << grasp.getObjectiveValue() << endl;

            grasp.displayOptimalSolution();
        } catch (const char *msg) {
            cerr << msg << endl;
        }

        /*
         * Apply Simulated Annealing algorithm
         * */
        try {
            float maxTimeSA = 60.0f;
            int tempInit = 10000;
            float alphaSA = 0.9;
            int iterByTemp = 1000;
            SimulatedAnnealing sa(dataName, tempInit, alphaSA, iterByTemp);
            int *solutionGRASP = sa.run(maxTimeSA);
            cout << "Solution found with Simulated Annealing :";
            for (int i = 0; i < sa.getN(); i++) {
                cout << " " << solutionGRASP[i];
            }
            cout << endl << "Admissible solution ? " << (QAP::isAdmissible(sa.getN(), solutionGRASP) ? "YES" : "NO")
                 << endl;
            cout << "Objective found with Simulated Annealing : " << sa.getObjectiveValue() << endl;

            sa.displayOptimalSolution();
        } catch (const char *msg) {
            cerr << msg << endl;
        }

    /******************************************/
    }
    system("pause");
        // Uncomment these lines before using the executable !
//        cout << "Try with another file ? (Y/N) ";
//        cin >> rep;
//    } while(rep != 'N');
    /************************************/
    return 0;
}