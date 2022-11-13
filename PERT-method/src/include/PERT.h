#pragma once

#include <vector>
#include <iostream>

using namespace std;

class PERT {
public:
    int N;  // task number
    int M;  // connection number
    float processTime;
    float CRPwar;
    float CRPtime;
    int XX;
    double Y;

    vector <vector <int>> X;            // adjacency matrix
    vector <vector <float>> TaskTimes;    // times for particular tasks
    vector <vector <float>> CritPath;     // critical path: task_num, start_t, finish_t
    vector <vector <int>> inputTripleTime;
    vector <float> war;
private:
    bool cycle;
    vector <int> taskDuration;
    vector <int> earlyStart;
    vector <int> earlyFinish;
    vector <int> lateStart;
    vector <int> lateFinish;

public:
    PERT();
    ~PERT();
    void importData(string fileName);
    void printAdjacencyMatrix();
    void printTaskTimes();
    void findProcessTime();
    void findTaskTimes();
    void findCRP();
    void dys();
    double inv_dys(double);
    void time_day();
    

};

