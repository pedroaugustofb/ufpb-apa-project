
#include <iostream>
#include <string>
#include <vector>

#include "calculate-total-cost.h"
#include "../entities/server.h"
#include "../entities/local-server.h"

int calculateTotalCost(vector<Server> &servers, LocalServer &local_server, int rows) {
    int servers_total_cost = 0;
    int local_server_total_cost = local_server.getCost();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < servers[i].jobs.size(); j++) {
            servers_total_cost += servers[i].jobs[j].cost;
        }
    }

    return servers_total_cost + local_server_total_cost;
}