#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdexcept>
#include "entities/job.h"
#include "entities/server.h"
#include <ctime>

using namespace std;

// to run project in terminal: g++ main.cpp entities/job.cpp entities/server.cpp -o main && ./main

#define INPUT_FILE_PATH "data/data.txt"

// file format
// jobsLenght
// serversLenght
// localServerCost
// empty line
// servers capacities (in line like "220 350" means server 1 has capacity 220 and server 2 has capacity 350)
// empty line

int main () {
    try{

    clock_t start = clock();
    
    ifstream file;

    file.open(INPUT_FILE_PATH);

    if (!file.is_open()) {
        throw runtime_error("Input file not found");
    }

    int JOBS_LENGTH, SERVERS_LENGTH, LOCAL_SERVER_COST;
    file >> JOBS_LENGTH >> SERVERS_LENGTH >> LOCAL_SERVER_COST;

    cout << "Number of Jobs to be distributed: " << JOBS_LENGTH << endl << "Number of available servers: " << SERVERS_LENGTH << endl << "Local server cost: " << LOCAL_SERVER_COST << endl;

    // iniciando vetores de servidores e jobs
    vector<Job> jobs;
    vector<Server> servers;

    // getting servers capacities
    for (int i = 0; i < SERVERS_LENGTH; i++) {
        int capacity;
        file >> capacity;
        servers.push_back(Server(capacity));
    }

    cout << "Servers capacities: ";
    for (int i = 0; i < SERVERS_LENGTH; i++) 
        cout << servers[i].getCapacity() << " ";
    cout << endl;


    // getting jobs
    for (int i = 0; i < JOBS_LENGTH; i++) {
        int cost, duration;
        file >> cost >> duration;
        jobs.push_back(Job(cost, duration));
    }

    cout << "Jobs costs and durations: ";
    for (int i = 0; i < JOBS_LENGTH; i++) 
        cout << "| cost: " << jobs[i].getCost() << " duration: " << jobs[i].getDuration() << " ";
    cout << endl;


    file.close(); // fechando arquivo

    clock_t end = clock();

    cout << "program time execution: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

    return 0;

    } catch (exception& e) {
        cerr << "Oops, something happend: " << e.what() << endl;
        return 1;
    }
}