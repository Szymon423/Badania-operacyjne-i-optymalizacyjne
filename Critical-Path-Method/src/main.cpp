#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>

#include "include/CRP.h"

using namespace std;

int main() {

    CRP task;
    task.importData("test/data_1.txt");
    task.printTaskTimes();
    task.printAdjacencyMatrix();
    task.findProcessTime();
    task.findTaskTimes();
    task.findCRP();
    
    system("pause");

    return 0;
}
