#include "job.h"

Job::Job(int cost, int duration) {
    this->cost = cost;
    this->duration = duration;
}

int Job::getCost() {
    return this->cost;
}

int Job::getDuration() {
    return this->duration;
}

void Job::setCost(int cost) {
    this->cost = cost;
}

void Job::setDuration(int duration) {
    this->duration = duration;
}