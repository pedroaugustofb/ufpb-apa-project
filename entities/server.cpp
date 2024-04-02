#include "server.h"

Server::Server(int capacity) {
    this->capacity = capacity;
}

int Server::getCapacity() {
    return this->capacity;
}

void Server::setCapacity(int capacity) {
    this->capacity = capacity;
}

void Server::increseUsage(int usage) {
    this->usage += usage;
}

int Server::getUsage() {
    return this->usage;
}