#include <iostream>
#include <vector>
#include "job.h"

using namespace std;

#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int capacity); // constructor
    int capacity; // server capacity
    int usage = 0; // server usage
    vector<Job> jobs; // jobs allocated to this server
};

#endif