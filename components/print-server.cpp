#include <iostream>
#include "../entities/server.h"
#include "log.h"

using namespace std;

void printServer(Server server, int index) {
    log("Server " + to_string(index + 1));
    log("Capacity: " + to_string(server.capacity));

    if(server.jobs.size() == 0) {
        log("No jobs allocated to this server");
        return;
    }

    log("Jobs allocated to this server: ");
    for (int i = 0; i < server.jobs.size(); i++) {
        log("Job " + to_string(server.jobs[i].column) + ": " + "(duration: " + to_string(server.jobs[i].duration) + ") (cost: " + to_string(server.jobs[i].cost) + ")");
    }

    log("Total time allocated: " + to_string(server.usage));

    int cost = 0;

    for (int i = 0; i < server.jobs.size(); i++) {
        cost += server.jobs[i].cost;
    }

    log("Total cost: " + to_string(cost));
}