#include <iostream>
#include "../entities/solution.h"

using namespace std;

int swap_inter_servers(Solution &solution, int result){

    Solution solution_copy = solution;
    
    for(int i = 0; i < solution_copy.servers.size(); i++){
        for(int j = 0; j < solution_copy.servers.size(); j++){
            if (i == j) continue;

            for(int k = 0; k < solution_copy.servers[i].jobs.size(); k++){
                for(int l = 0; l < solution_copy.servers[j].jobs.size(); l++){

                    int duration_k = solution_copy.duration_matrix[i][solution_copy.servers[i].jobs[k].column];
                    int duration_l = solution_copy.duration_matrix[j][solution_copy.servers[j].jobs[l].column];
                    
                    // verify if the servers have capacity for the new jobs
                    if (solution_copy.servers[i].capacity - duration_k + duration_l < 0 ||
                        solution_copy.servers[j].capacity - duration_l + duration_k < 0) {
                        continue;
                    }

                    // swap jobs if the servers have capacity for the new jobs
                    swap(solution_copy.servers[i].jobs[k], solution_copy.servers[j].jobs[l]);

                    int cost = solution_copy.calculate();

                    if(cost < result){
                        result = cost;
                        solution = solution_copy;
                    }
                }
            }            
        }
    }

    return result;
}