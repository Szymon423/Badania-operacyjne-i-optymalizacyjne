#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <iomanip>

#include "PERT.h"

using namespace std;

int main() {

    PERT task;
    task.importData("test/data_1.txt");
    task.printTaskTimes();
    task.printAdjacencyMatrix();
    task.findProcessTime();
    task.findTaskTimes();
    task.findCRP();
    task.dys();
    cout << setprecision(4) << "\nOdwrotna dystrybuanta wynosi: " << task.inv_dys(task.Y) << endl;
    task.time_day();
   
    system("pause");

    return 0;
}
