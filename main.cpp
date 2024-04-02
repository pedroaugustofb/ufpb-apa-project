#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdexcept>
#include "entities/job.h"
#include "entities/server.h"
#include <ctime>
#include "guloso.cpp"
#include "print-matrix.cpp"
#include "log.cpp"

using namespace std;

// to run project in terminal: g++ main.cpp entities/job.cpp entities/server.cpp -o main && ./main

#define INPUT_FILE_PATH "input.txt"

// file format
// jobsLenght
// serversLenght
// localServerCost
// empty line
// servers capacities (in line like "220 350" means server 1 has capacity 220 and server 2 has capacity 350)
// empty line

int main () {
    try{

        endl();
        log("Starting program...");
        endl();

    clock_t start = clock();
    
    ifstream file;

    file.open(INPUT_FILE_PATH);

    if (!file.is_open()) {
        throw runtime_error("Input file not found");
    }

    /**
     * 1. read number of jobs, servers and local server cost
    */
    int JOBS_LENGTH, SERVERS_LENGTH, LOCAL_SERVER_COST;
    file >> JOBS_LENGTH >> SERVERS_LENGTH >> LOCAL_SERVER_COST;

    log("Number of Jobs to be distributed: " + to_string(JOBS_LENGTH));
    
    log("Number of available servers: " + to_string(SERVERS_LENGTH));
    
    log("Local server cost: " + to_string(LOCAL_SERVER_COST));
    
    
    /**
     * 2. read servers capacities
    */
    vector<Server> servers;
    for (int i = 0; i < SERVERS_LENGTH; i++) {
        int capacity;
        file >> capacity;
        servers.push_back(Server(capacity));
    }

    endl();
    log("Servers Capacities: ");
    for (int i = 0; i < SERVERS_LENGTH; i++) {
        log("Server " + to_string(i + 1) + " capacity: " + to_string(servers[i].getCapacity()));
    }


    /**
     * 3. read matrix of duration ( server x job )
     * 
     * 120 80 180 95 35
     * 145 70 230 70 40
     * 
     * should be read as an matrix
    */
    int **DURATION_MATRIX = new int*[SERVERS_LENGTH]; // start matrix with number of jobs

    for (int i = 0; i < SERVERS_LENGTH; i++) {
        DURATION_MATRIX[i] = new int[JOBS_LENGTH]; // for each job, create a new array with number of servers, creating a matrix
        for (int j = 0; j < JOBS_LENGTH; j++) {
            file >> DURATION_MATRIX[i][j];
        }
    }

    endl();
    log("Duration Matrix: ");
    PrintMatrix(DURATION_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);


    /**
     * 4. read matrix of cost ( server x job )
     * 
     * 350 50 540 245 145
     * 410 80 500 200 100
     * 
     * should be read as an matrix
    */
    int **COST_MATRIX = new int*[SERVERS_LENGTH]; // start matrix with number of jobs

    for (int i = 0; i < SERVERS_LENGTH; i++) {
        COST_MATRIX[i] = new int[JOBS_LENGTH]; // for each job, create a new array with number of servers, creating a matrix
        for (int j = 0; j < JOBS_LENGTH; j++) {
            file >> COST_MATRIX[i][j];
        }
    }

    endl();
    log("Cost Matrix: ");
    PrintMatrix(COST_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);




    endl();
    log("Running Greedy Algorithm...");

    file.close(); // fechando arquivo

    clock_t end = clock();

    endl();
    log("Program time execution: " + to_string((double)(end - start) / CLOCKS_PER_SEC) + "s");
    endl();

    return 0;

    } catch (exception& e) {
        cerr << "Oops, something happend: " << e.what() << endl;
        return 1;
    }
}