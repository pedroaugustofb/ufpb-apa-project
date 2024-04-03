#include "server.h"

Server::Server(int capacity) {
    this->capacity = capacity;
}

int Server::getCost() {
    int cost = 0;
    for (int i = 0; i < this->jobs.size(); i++) {
        cost += this->jobs[i].cost;
    }
    return cost;
}