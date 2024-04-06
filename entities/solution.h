#include <iostream>
#include <string>
#include <vector>
#include "server.h"
#include "local-server.h"

using namespace std;

#ifndef SOLUTION_H
#define SOLUTION_H

class Solution {
public:
    Solution(int **DURATION_MATRIX, int **COST_MATRIX, int JOBS_LENGTH, int SERVERS_LENGTH, int LOCAL_SERVER_COST, vector<Server> servers);
    
    int jobs_length;
    int servers_length;
    int **duration_matrix;
    int **cost_matrix;
    vector<Server> servers;
    LocalServer local_server;

    int greedy_solution;
    int vnd_solution;

    int calculate();

    void print();

};

#endif