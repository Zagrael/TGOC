#include <iostream>
#include <fstream>
#include <string>

#include "QAP.h"
#include "GRASP.h"

using namespace std;

int main() {

    string dataName = "nug30";

    // Uncomment these lines before using the executable !
    char rep;
    do {
        system("CLS");
        cout << "Data name (bur26a, chr18a, els19, kra32, nug12, nug30, sko42, tai15a, tai15b, tai100a, ...) : ";
        cin >> dataName;
    /********************************************/

        float alphaGRASP = 0.2;
        float maxTimeGRASP = 10.0f;

        try {
            /*
             * Apply GRASP algorithm
             * */
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

        // Uncomment these lines before using the executable !
        cout << "Try with another file ? (Y/N) ";
        cin >> rep;
    } while(rep != 'N');
    /************************************/
    return 0;
}