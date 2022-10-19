#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>

#include "include/PERT.h"

using namespace std;

int main() {

    PERT task;
    task.importData("test/data_1.txt");
    task.printTaskTimes();
    task.printAdjacencyMatrix();
    task.findProcessTime();
    task.findTaskTimes();
    task.findCRP();
    
    system("pause");

    return 0;
}
