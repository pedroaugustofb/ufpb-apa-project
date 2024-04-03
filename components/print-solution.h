#include <iostream>
#include <string>
#include <vector>
#include "../entities/server.h"
#include "../entities/local-server.h"

using namespace std;

#ifndef PRINT_SOLUTION_H
#define PRINT_SOLUTION_H

void printSolution(vector<Server> servers, LocalServer local_server, int **duration_matrix, int **cost_matrix, int rows, int columns);

#endif