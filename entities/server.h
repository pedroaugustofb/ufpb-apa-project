#include <vector>
#include "job.h"

#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int capacity); // constructor

    int getCapacity(); // get the capacity of the server

    void setCapacity(int capacity); // set the capacity of the server

    void increseUsage(int usage); // set the usage of the server

    int getUsage(); // get the usage of the server

private:
    int capacity; // server capacity
    int usage; // server usage

};

#endif