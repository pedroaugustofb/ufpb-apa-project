
#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int capacity); // constructor

    int getCapacity(); // get the capacity of the server

    void setCapacity(int capacity); // set the capacity of the server

private:
    int capacity; // server capacity

};

#endif