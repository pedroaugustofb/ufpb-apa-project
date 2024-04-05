#include <iostream>
#include <vector>

#include "../entities/server.h"
#include "../entities/local-server.h"
#include "log.h"
#include "print-server.h"

void printSolution(vector<Server> servers, LocalServer local_server, int rows){
    endl();
    log("----------------------------------------------------- |");
    log("Servers: ");

    for (int i = 0; i < rows; i++) {
        printServer(servers[i], i);
        if(i != rows - 1) {
            log("");
        }
    }

    log("");
    int servers_total_cost = 0;
    int local_server_total_cost = local_server.getCost();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < servers[i].jobs.size(); j++) {
            servers_total_cost += servers[i].jobs[j].cost;
        }
    }

    log("Servers total cost: " + to_string(servers_total_cost));

    log("");

    if(local_server.jobs.size() > 0) {
        log("Local Jobs: ");
        for (int i = 0; i < local_server.jobs.size(); i++) {
            Job job = local_server.jobs[i];
            int duration = job.duration;
            int cost = job.cost;
            log("Job " + to_string(job.column));
        }
    }

    log("Local server total cost ( for " + to_string(local_server.jobs.size()) + " job(s) ): " + to_string(local_server_total_cost));

    log("");

    log("Total cost: " + to_string(servers_total_cost + local_server_total_cost));
    log("----------------------------------------------------- |");
}