#include <iostream>
#include <fstream>
#include <string>

#include <time.h>
#include "GRASP.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main() {

    string dataName = "nug12";
    srand(static_cast<unsigned int>(time(nullptr)));

    // Uncomment these lines before using the executable !
    char rep;
    do {
        system("CLS");
        cout << "Data name (bur26a, chr18a, els19, kra32, nug12, nug30, sko42, tai15a, tai15b, tai100a, ...) : ";
        cin >> dataName;
    /********************************************/


        /*
         * Apply Simulated Annealing algorithm
         * */
//        float maxTimeSA = 60.0f;
//        int tempInit = 10000;
//        float alphaSA = 0.9;
//        try {
//            int iterByTemp = 1000;
//            SimulatedAnnealing sa(dataName, tempInit, alphaSA, iterByTemp);
//            int *solutionSA = sa.run(maxTimeSA);
//            cout << "Solution found with Simulated Annealing :";
//            for (int i = 0; i < sa.getN(); i++) {
//                cout << " " << solutionSA[i];
//            }
//            cout << endl << "Admissible solution ? " << (QAP::isAdmissible(sa.getN(), solutionSA) ? "YES" : "NO")
//                 << endl;
//            cout << "Objective found with Simulated Annealing : " << sa.getObjectiveValue() << endl;
//
//            sa.displayOptimalSolution();
//            sa.writeSolution("SimulatedAnnealing");
//        } catch (const char *msg) {
//            cerr << msg << endl;
//        }

        /*
         * Apply GRASP algorithm
         * */
        try {
            cout << endl;
            float alphaGRASP = 0.6;
            float maxTimeGRASP = 7 * 60.0f;
            GRASP grasp(dataName, alphaGRASP);
            int *solutionGRASP = grasp.run(maxTimeGRASP);
            cout << endl << "Solution found with GRASP :";
            for (int i = 0; i < grasp.getN(); i++) {
                cout << " " << solutionGRASP[i];
            }
            cout << endl << "Admissible solution ? " << (QAP::isAdmissible(grasp.getN(), solutionGRASP) ? "YES" : "NO")
                 << endl;
            cout << "Objective found with GRASP : " << grasp.getObjectiveValue() << endl;

//            grasp.displayOptimalSolution();
            grasp.writeSolution("GRABOU");
        } catch (const char *msg) {
            cerr << msg << endl;
        }

        // Uncomment these lines before using the executable !
        cout << "Try with another file ? (Y/N) ";
        cin >> rep;
    } while(rep != 'N');
    /************************************/
    return 0;
}