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

    string files[] = {
            "bur26a", "bur26b", "bur26c", "bur26d", "bur26e", "bur26f", "bur26g", "bur26h",
            "chr12a", "chr12b", "chr12c",
            "chr15a", "chr15b", "chr15c",
            "chr18a", "chr18b",
            "chr20a", "chr20b","chr20c",
            "chr22a", "chr22b",
            "chr25a",
            "els19",
            "esc16a", "esc16b", "esc16c", "esc16d", "esc16e", "esc16f", "esc16g", "esc16h", "esc16i", "esc16j",
            "esc32e", "esc32g",
            "esc128",
            "had12", "had14", "had16", "had18", "had20",
            "kra30a", "kra30b",
            "kra32",
            "lipa20a", "lipa20b",
            "lipa30a", "lipa30b",
            "lipa40a", "lipa40b",
            "lipa50a", "lipa50b",
            "lipa60a", "lipa60b",
            "lipa70a", "lipa70b",
            "lipa80a", "lipa80b",
            "lipa90a", "lipa90b",
            "nug12", "nug14", "nug15", "nug16a", "nug16b", "nug17", "nug18", "nug20", "nug21", "nug22", "nug24",
            "nug25", "nug27", "nug28", "nug30",
            "rou12", "rou15", "rou20",
            "scr12", "scr15", "scr20",
            "sko42", "sko49", "sko56", "sko64", "sko72", "sko81", "sko90",
            "sko100a", "sko100b", "sko100c", "sko100d", "sko100e", "sko100f",
            "ste36a", "ste36b", "ste36c",
            "tai12a", "tai12b", "tai15a", "tai15b", "tai17a", "tai20a", "tai20b", "tai25a", "tai25b",
            "tai30a", "tai30b", "tai35a", "tai35b", "tai40a", "tai40b", "tai50a", "tai50b", "tai60a", "tai60b",
            "tai64c", "tai80a", "tai80b", "tai100a", "tai100b", "tai150b", "tai256c",
            "tho30", "tho40", "tho150",
            "wil50", "wil100"
    };
    int nFiles = sizeof(files) / sizeof(*files);
    // Uncomment these lines before using the executable !
    char rep;
    do {
        system("CLS");
        cout << "Data name (bur26a, chr18a, els19, kra32, nug12, nug30, sko42, tai15a, tai15b, tai100a, ...) : ";
        cin >> dataName;
    /********************************************/

    // Uncomment this line to run all files
//    cout << "Testing with " << nFiles << " files" << endl;
//    for(int zk = 0; zk < nFiles; zk++) {
//        dataName = files[zk];
//        cout << "Trying " << dataName << endl;
    /*********************************************/

        /*
         * Apply GRASP algorithm
         * */
        try {
            cout << endl;
            float alphaGRASP = 0.6;
            float maxTimeGRASP = 60.0f;
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
            grasp.writeSolution("GRASP");
        } catch (const char *msg) {
            cerr << msg << endl;
        }

        /*
         * Apply Simulated Annealing algorithm
         * */
//        float maxTimeSA = 60.0f;
//        int tempInit = 10000;
//        float alphaSA = 0.7;
//        try {
//            int iterByTemp = 1000;
//            SimulatedAnnealing sa(dataName, tempInit, alphaSA, iterByTemp);
//            int *solutionGRASP = sa.run(maxTimeSA);
//            cout << "Solution found with Simulated Annealing :";
//            for (int i = 0; i < sa.getN(); i++) {
//                cout << " " << solutionGRASP[i];
//            }
//            cout << endl << "Admissible solution ? " << (QAP::isAdmissible(sa.getN(), solutionGRASP) ? "YES" : "NO")
//                 << endl;
//            cout << "Objective found with Simulated Annealing : " << sa.getObjectiveValue() << endl;
//
//            sa.displayOptimalSolution();
//            sa.writeSolution("SimulatedAnnealing");
//        } catch (const char *msg) {
//            cerr << msg << endl;
//        }

    /******************************************/
//    }
//    system("pause");
        // Uncomment these lines before using the executable !
        cout << "Try with another file ? (Y/N) ";
        cin >> rep;
    } while(rep != 'N');
    /************************************/
    return 0;
}