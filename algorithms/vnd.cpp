#include <iostream>
#include <vector>
#include <time.h>

#include "../entities/server.h"
#include "../entities/local-server.h"

#include "../components/log.h"
#include "../components/print-matrix.h"
#include "../components/print-solution.h"

#include "swap-intra.cpp"

using namespace std;


/**
 * VND - Variable Neighborhood Descent
 * 
 * @param duration_matrix           dinamic matrix with the duration of each job in each server
 * @param cost_matrix               dinamic matrix with the cost of each job in each server
 * @param local_server_cost         cost of the local server
 * @param servers                   vector with the servers
 * @param local_server              vector with the local server
 * @param rows                      number of jobs 
 * @param columns                   number of servers
 * @param greedy_solution           cost of the greedy solution to compare
 * 
 * @obs:                            both matrices have the same size
 * @obs:                            both matrices are not the original ones, because they are sorted by cost in the greedy algorithm
*/
vector<int> vnd(int **duration_matrix, int **cost_matrix, int local_server_cost, vector<Server> &servers, LocalServer &local_server, int rows, int columns, int greedy_solution){

    int neighborhoods = 3, neighborhood = 1;
    vector<int> neighborhoods_solutions;

    while(neighborhood <= neighborhoods){

        int solution;
        
        switch(neighborhood){
            case 1:
                log("Starting Swap-Intra neighborhood...");

                clock_t start_swap_intra = clock();

                swapIntra(duration_matrix, cost_matrix, local_server_cost, servers, local_server, rows, columns, greedy_solution);

                clock_t end_swap_intra = clock();

                log("Swap-Intra neighborhood time execution " + to_string((double)(end_swap_intra - start_swap_intra) / CLOCKS_PER_SEC) + "s");
                endl();
                break;
            // case 2:
            //     log("Starting second neighborhood (Two-Opt)...");
            //     break;
            // case 3:
            //     log("Starting third neighborhood (Swap-Inter)...");
            //     break;
        }


        neighborhoods_solutions.push_back(solution);
        
        neighborhood++;

    }

    return neighborhoods_solutions;
}
