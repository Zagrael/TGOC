#include <iostream>
#include <fstream>
#include <string>

#include "QAP.h"

using namespace std;

int main() {

    const string dataName = "nug12";

    try {
        QAP qap(dataName);

        qap.displayOptimalSolution();
    } catch(const char *msg) {
        cerr << msg << endl;
    }

    // Uncomment this line before using the executable !
//    system("pause");
    return 0;
}