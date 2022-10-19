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

    vector <vector <int>> X;            // adjacency matrix
    vector <vector <float>> TaskTimes;    // times for particular tasks
    vector <vector <float>> CritPath;     // critical path: task_num, start_t, finish_t
    vector <vector <int>> inputTripleTime;     
    vector <float> war;
    private:
        bool cycle;
        vector <float> P;
        vector <float> C;

    public:
        PERT();
        ~PERT();
        void importData(string fileName);
        void printAdjacencyMatrix();
        void printTaskTimes();
        void findProcessTime();
        void findTaskTimes();
        void findCRP();
        float finishPossibilityIn(float duration);
        float projectLenthWithPossibility(float possibility);
        
};

