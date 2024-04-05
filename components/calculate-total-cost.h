#include <iostream>
#include <string>
#include <vector>

#include "../entities/server.h"
#include "../entities/local-server.h"

using namespace std;

#ifndef CALCULATE_TOTAL_COST_H
#define CALCULATE_TOTAL_COST_H

int calculateTotalCost(vector<Server> &servers, LocalServer &local_server, int rows);

#endif