#include "local-server.h"

int LocalServer::getCost() {
    return this->fixed_cost * this->jobs.size();
}