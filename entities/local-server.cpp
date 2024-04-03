#include "local-server.h"

LocalServer::LocalServer(int fixed_cost) {
    this->fixed_cost = fixed_cost;
}

int LocalServer::getCost() {
    return this->fixed_cost * this->jobs.size();
}