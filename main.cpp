#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <time.h>
#include <ctime>
// entities
#include "entities/server.h"
#include "entities/solution.h"
// .h
#include "components/log.h"
// cpp
#include "algorithms/greedy.cpp"
#include "algorithms/vnd.cpp"

using namespace std;

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

        if (!file.is_open()) throw runtime_error("Input file not found");
        
        log("Reading file (" + INPUT_FILE_PATH + ")...");

        // 1. read number of jobs, servers and local server cost
        int JOBS_LENGTH, SERVERS_LENGTH, LOCAL_SERVER_COST;
        file >> JOBS_LENGTH >> SERVERS_LENGTH >> LOCAL_SERVER_COST;

        // 2. read servers capacities
        vector<Server> servers;
        for (int i = 0; i < SERVERS_LENGTH; i++) {
            int capacity;
            file >> capacity;
            servers.push_back(Server(capacity));
        }

        // creating dinamic matrix because we don't know the size of the matrix at compile time
        int **DURATION_MATRIX = new int*[SERVERS_LENGTH];
        int **COST_MATRIX = new int*[SERVERS_LENGTH];

        // 3. read matrix of duration ( server x job )
        for (int i = 0; i < SERVERS_LENGTH; i++) {
            DURATION_MATRIX[i] = new int[JOBS_LENGTH];
            for (int j = 0; j < JOBS_LENGTH; j++) {
                file >> DURATION_MATRIX[i][j];
            }
        }

        // 4. read matrix of cost ( server x job )
        for (int i = 0; i < SERVERS_LENGTH; i++) {
            COST_MATRIX[i] = new int[JOBS_LENGTH];
            for (int j = 0; j < JOBS_LENGTH; j++) {
                file >> COST_MATRIX[i][j];
            }
        }

        file.close();

        endl();

        Solution solution = Solution(DURATION_MATRIX, COST_MATRIX, JOBS_LENGTH, SERVERS_LENGTH, LOCAL_SERVER_COST, servers);

        log("Running Greedy Algorithm...");

        clock_t start_greedy = clock();

        // 5. run greedy algorithm
        int GREEDY_SOLUTION = greedy(solution);

        clock_t end_greedy = clock();

        log("Showing greedy solution...");

        solution.print();

        log("Greedy Algorithm time execution: " + to_string((double)(end_greedy - start_greedy) / CLOCKS_PER_SEC) + "s");

        endl();

        log("Running VND Algorithm...");

        clock_t start_vnd = clock();

        // 6. run VND algorithm
        int VND_SOLUTION = vnd(solution);

        clock_t end_vnd = clock();


        if (solution.vnd_solution != solution.greedy_solution) {

            log("Showing best solution founded by VND..."); 
            solution.print();

        } else log("VND did not find a better solution than Greedy");

        log("VND Algorithm time execution: " + to_string((double)(end_vnd - start_vnd) / CLOCKS_PER_SEC) + "s");

        clock_t end = clock();

        endl();
        
        size_t pos_open = INPUT_FILE_PATH.find('/');
        size_t pos_close = INPUT_FILE_PATH.find('.');

        string filename = "results/" + INPUT_FILE_PATH.substr(pos_open + 1, pos_close - pos_open - 1) + ".output.txt";
        
        log("Creating output file (" + filename + ")...");

        solution.createFile(filename);

        endl();
        
        log("Program time execution: " + to_string((double)(end - start) / CLOCKS_PER_SEC) + "s");

        endl();

        return 0;

    } catch (exception& e) {
        cerr << "Oops, something happend: " << e.what() << endl;
        return 1;
    }
}