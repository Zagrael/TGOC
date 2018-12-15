#include <iostream>
#include <fstream>
#include <string>

#include "QAP.h"
#include "GRASP.h"

using namespace std;

int main() {

    const string dataName = "nug30";

    float alphaGRASP = 0.2;
    float maxTimeGRASP = 10.0f;

    try {
        /*
         * Apply GRASP algorithm
         * */
        GRASP grasp(dataName, alphaGRASP);
        int *solutionGRASP = grasp.run(maxTimeGRASP);
        cout << "Solution found with GRASP :";
        for(int i = 0; i < grasp.getN(); i++) {
            cout << " " << solutionGRASP[i];
        }
        cout << endl << "Admissible solution ? " << (QAP::isAdmissible(grasp.getN(), solutionGRASP) ? "YES" : "NO") << endl;
        cout <<  "Objective found with GRASP : " << grasp.getObjectiveValue() << endl;

        grasp.displayOptimalSolution();
    } catch(const char *msg) {
        cerr << msg << endl;
    }

    // Uncomment this line before using the executable !
    system("pause");
    return 0;
}