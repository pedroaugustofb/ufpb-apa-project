#include <iostream>
#include <vector>
#include "job.h"

using namespace std;

#ifndef LOCAL_SERVER_H
#define LOCAL_SERVER_H

class LocalServer {
public:
    LocalServer(int fixed_cost); // constructor
    int fixed_cost;
    vector<Job> jobs; // jobs allocated to this server

    int getCost();
};

#endif