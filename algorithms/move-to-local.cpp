#include <iostream>
#include "../entities/solution.h"

using namespace std;

int move_to_local(Solution &solution, int result){

    Solution solution_copy = solution;

    // objetivo: mover todos os jobs que possuem valor de custo maior que o custo do servidor local para o servidor local
    for(int i = 0; i < solution_copy.servers.size(); i++){
        for(int j = 0; j < solution_copy.servers[i].jobs.size(); j++){
                
            int job_cost = solution_copy.cost_matrix[i][solution_copy.servers[i].jobs[j].column];

            // verify if the job has cost greater than the local server cost
            if (job_cost < solution_copy.local_server.fixed_cost) {
                continue;
            }

            // move job to local server if the local server has capacity for the new job
            solution_copy.local_server.jobs.push_back(solution_copy.servers[i].jobs[j]);
            solution_copy.servers[i].jobs.erase(solution_copy.servers[i].jobs.begin() + j);

            int cost = solution_copy.calculate();

            if(cost < result){
                result = cost;
                solution = solution_copy;
            }
        }
    }

    return result;
}