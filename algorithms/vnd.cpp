#include <iostream>
#include <vector>
#include <time.h>

#include "../entities/server.h"
#include "../entities/local-server.h"

#include "../components/log.h"
#include "../components/print-matrix.h"
#include "../components/print-solution.h"

#include "swap-inter-servers-local.cpp"


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
 * @param best_solution             solution by previus algorithm (greedy)
 * 
 * @obs:                            both matrices have the same size
 * @obs:                            both matrices are not the original ones, because they are sorted by cost in the greedy algorithm
*/
int vnd(vector<Server> &servers, LocalServer &local_server, int rows, int columns, int best_solution){

    vector<Server> servers_copy = servers;
    LocalServer local_server_copy = local_server;
    int best_solution_copy = best_solution;

    bool improvement = true;

    do {

        improvement = false;

        // Swap Jobs that are in local server with jobs that are in servers to improve the solution
        int solution = swap_inter_server_local(servers_copy, local_server_copy, rows, best_solution_copy);
        
        if(solution < best_solution_copy){
            best_solution_copy = solution;
            improvement = true;
            continue;
        }

    } while(improvement);

    if (best_solution < best_solution_copy) {
        log("VND did not find a better solution than Greedy");
        return best_solution;
    }

    servers = servers_copy;
    local_server = local_server_copy;
    
    return best_solution_copy;
}
