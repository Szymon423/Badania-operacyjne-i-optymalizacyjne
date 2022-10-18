#pragma once

#include <vector>
#include <iostream>

using namespace std;

class CRP {
     public:
         int N;  // task number
         int M;  // connection number
         int processTime;
         vector <vector <int>> X;            // adjacency matrix
         vector <vector <int>> TaskTimes;    // times for particular tasks
         vector <vector <int>> CritPath;     // critical path: task_num, start_t, finish_t

     private:
         bool cycle;
         vector <int> P;
         vector <int> C;

    public:
        CRP();
        ~CRP();
        void importData(string fileName);
        void printAdjacencyMatrix();
        void printTaskTimes();
        void findProcessTime();
        void findTaskTimes();
        void findCRP();
        
};
