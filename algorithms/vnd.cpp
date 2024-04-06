#include <iostream>
#include <vector>
#include <time.h>

#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/solution.h"

#include "../components/log.h"

#include "swap-inter-servers-local.cpp"
#include "swap-inter-servers.cpp"


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
int vnd(Solution &solution){

    Solution solution_copy = solution;
    int vnc_solution = solution.greedy_solution;

    bool improvement = true;

    do {

        improvement = false;

        // Swap Jobs that are in local server with jobs that are in servers to improve the solution
        int solution_1 = swap_inter_server_local(solution_copy, vnc_solution);
        
        if(solution_1 < vnc_solution){
            vnc_solution = solution_1;
            improvement = true;
            continue;
        }

        // Swap Jobs that are in servers with jobs that are in others servers to improve the solution
        int solution_2 = swap_inter_servers(solution_copy, vnc_solution);

        if(solution_2 < vnc_solution){
            vnc_solution = solution_2;
            improvement = true;
            continue;
        }
    
    } while(improvement);

    solution.servers = solution_copy.servers;
    solution.local_server = solution_copy.local_server;

    solution.vnd_solution = solution.greedy_solution <= vnc_solution ? solution.greedy_solution : vnc_solution;
    
    return solution.vnd_solution;
}
