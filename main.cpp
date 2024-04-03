#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdexcept>
#include <ctime>

// entities
#include "entities/job.h"
#include "entities/server.h"
#include "entities/local-server.h"

// .h
#include "components/log.h"
#include "components/print-server.h"
#include "components/print-matrix.h"
#include "components/print-solution.h"

// cpp
#include "algorithms/greedy.cpp"
#include "algorithms/vnd.cpp"


using namespace std;

// to run project in terminal: 
// g++ main.cpp entities/*.cpp components/*.cpp -o main  
// then:
// & ./'main.exe' <file path>
// example & ./'main.exe' input.txt

// to see input.txt format check README.md

int main (int argc, char* argv[]) {
    try{

        if(argc == 0)
            throw runtime_error("Please, provide the input file path");
        
        if(argc > 2)
            throw runtime_error("Too many arguments, please provide only the input file path");

        string INPUT_FILE_PATH = argv[1];

        endl();
        log("Starting program...");
        endl();

        clock_t start = clock();
        
        ifstream file;

        file.open(INPUT_FILE_PATH);

        if (!file.is_open()) {
            throw runtime_error("Input file not found");
        }

        log("Reading file (" + INPUT_FILE_PATH + ")...");

        /**
         * 1. read number of jobs, servers and local server cost
        */
        int JOBS_LENGTH, SERVERS_LENGTH, LOCAL_SERVER_COST;
        file >> JOBS_LENGTH >> SERVERS_LENGTH >> LOCAL_SERVER_COST;

        // log("Number of Jobs to be distributed: " + to_string(JOBS_LENGTH));
        
        // log("Number of available servers: " + to_string(SERVERS_LENGTH));
        
        // log("Local server cost: " + to_string(LOCAL_SERVER_COST));
                
        /**
         * 2. read servers capacities
        */
        vector<Server> servers;
        for (int i = 0; i < SERVERS_LENGTH; i++) {
            int capacity;
            file >> capacity;
            servers.push_back(Server(capacity));
        }

        /**
         * 3. read matrix of duration ( server x job )
         * 
         * @example
         * 120 80 180 95 35
         * 145 70 230 70 40
         * 
         * should be read as an matrix
         * 
         * @obs: how we dont know the number of jobs and servers in compile time, we need to create a matrix dinamically
        */
        int **DURATION_MATRIX = new int*[SERVERS_LENGTH]; // start matrix with number of jobs

        for (int i = 0; i < SERVERS_LENGTH; i++) {
            DURATION_MATRIX[i] = new int[JOBS_LENGTH]; // for each job, create a new array with number of servers, creating a matrix
            for (int j = 0; j < JOBS_LENGTH; j++) {
                file >> DURATION_MATRIX[i][j];
            }
        }

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

        // endl();
        // log("Servers: ");
        // for (int i = 0; i < SERVERS_LENGTH; i++) {
        //     printServer(servers[i], DURATION_MATRIX, COST_MATRIX, i);
        //     if(i != SERVERS_LENGTH - 1) {
        //         log("");
        //     }
        // }

        // endl();
        // log("Duration Matrix: ");
        // printMatrix(DURATION_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);

        // endl();
        // log("Cost Matrix: ");
        // printMatrix(COST_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);

        file.close();

        LocalServer local_server = LocalServer(LOCAL_SERVER_COST);  // starting a vector to store jobs that will be allocated to local server

        endl();

        log("Running Greedy Algorithm...");

        clock_t start_greedy = clock();

        int GREEDY_SOLUTION = greedy(DURATION_MATRIX, COST_MATRIX, LOCAL_SERVER_COST, servers, local_server, SERVERS_LENGTH, JOBS_LENGTH);

        clock_t end_greedy = clock();

        log("Showing greedy solution...");
        printSolution(servers, local_server, DURATION_MATRIX, COST_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);
        log("Greedy Algorithm time execution: " + to_string((double)(end_greedy - start_greedy) / CLOCKS_PER_SEC) + "s");

        endl();

        log("Running VND Algorithm...");

        clock_t start_vnd = clock();

        int VND_SOLUTION = vnd(DURATION_MATRIX, COST_MATRIX, LOCAL_SERVER_COST, servers, local_server, SERVERS_LENGTH, JOBS_LENGTH, GREEDY_SOLUTION);

        clock_t end_vnd = clock();

        log("Showing best solution founded by VND...");
        printSolution(servers, local_server, DURATION_MATRIX, COST_MATRIX, SERVERS_LENGTH, JOBS_LENGTH);
        log("VND Algorithm time execution: " + to_string((double)(end_vnd - start_vnd) / CLOCKS_PER_SEC) + "s");

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