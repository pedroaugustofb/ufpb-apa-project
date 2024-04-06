#include <iostream>
#include <vector>
#include <time.h>
#include "../entities/solution.h"
#include "move-to-local.cpp"
#include "swap-inter-servers-local.cpp"
#include "swap-inter-servers.cpp"


using namespace std;


/**
 * VND - Variable Neighborhood Descent
 * 
 * @param solution                                  solution to be improved
 * 
 * @returns best result if founded                  the improved solution
 * otherwise returns before solution                
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

        // Move Jobs that are in servers to local server to improve the solution
        int solution_3 = move_to_local(solution_copy, vnc_solution);

        if(solution_3 < vnc_solution){
            vnc_solution = solution_3;
            improvement = true;
            continue;
        }
    
    } while(improvement);

    solution.servers = solution_copy.servers;
    solution.local_server = solution_copy.local_server;

    solution.vnd_solution = solution.greedy_solution <= vnc_solution ? solution.greedy_solution : vnc_solution;
    
    return solution.vnd_solution;
}
