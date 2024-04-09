#include <iostream>
#include "../entities/solution.h"
#include "../entities/job.h"

using namespace std;

int move_from_local(Solution &solution, int result){

    Solution solution_copy = solution;

    // objetivo: tentar mover todos os jobs que possuem valor de custo menor do que o custo do servidor local para os servidores se esses possuirem capacidade

    for( int i = 0; i < solution_copy.servers.size(); i++){
        for(int j = 0; j < solution_copy.local_server.jobs.size(); j++){

            Job job = solution_copy.local_server.jobs[j];
            int job_duration = solution_copy.duration_matrix[i][job.column];

            if(solution_copy.servers[i].capacity < job_duration){
                continue;
            }

            int job_cost = solution_copy.cost_matrix[i][job.column];

            if(job_cost >= solution_copy.local_server.fixed_cost){
                continue;
            }

            solution_copy.servers[i].jobs.push_back(job);
            solution_copy.local_server.jobs.erase(solution_copy.local_server.jobs.begin() + j);

            int cost = solution_copy.calculate();

            if(cost < result){
                result = cost;
                solution = solution_copy;
            }
        }
    }

    return result;
}