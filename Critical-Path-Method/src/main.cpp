#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>

#include "include/CRP.h"

using namespace std;

int main() {

    CRP test;
    test.importData("test/data_1.txt");
    test.printTaskTimes();
    test.printAdjacencyMatrix();
    test.findProcessTime();
    test.findTaskTimes();
    test.findCRP();
    
    system("pause");

    return 0;
}
