#include <iostream>
#include <vector>
#include <time.h>
#include "../entities/solution.h"
#include "move-from-local.cpp"
#include "move-to-local.cpp"
#include "swap-inter-servers.cpp"

using namespace std;

int vnd(Solution &solution){

    Solution solution_copy = solution;
    int vnc_solution = solution.greedy_solution;

    bool improvement = true;

    do {

        improvement = false;

        // Swap Jobs that are in servers with jobs that are in others servers to improve the solution
        swap_inter_servers(solution_copy);

        // Move Jobs that are in servers to local server to improve the solution
        // Complexidade O(n^2)
        move_to_local(solution_copy);

        // Move Jobs that are in local server to servers to improve the solution
        // Complexidade O(n^2)
        move_from_local(solution_copy);

        int new_result = solution_copy.calculate();

        if(new_result < vnc_solution){
            vnc_solution = new_result;
            improvement = true;
            continue;
        }
    
    } while(improvement);

    solution.servers = solution_copy.servers;
    solution.local_server = solution_copy.local_server;

    solution.vnd_solution = solution.greedy_solution <= vnc_solution ? solution.greedy_solution : vnc_solution;
    
    return solution.vnd_solution;
}
