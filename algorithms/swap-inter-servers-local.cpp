#include <iostream>
#include <vector>
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/job.h"

using namespace std;

/**
 * Swap Jobs that are in local server with jobs that are in servers to improve the solution
*/
int swap_inter_server_local(Solution &solution, int result){
    Solution solution_copy = solution;

   for(int i = 0; i < solution_copy.local_server.jobs.size(); i++){
       Job local_job = solution_copy.local_server.jobs[i];
        for(int j = 0; j < solution_copy.servers.size(); j++){
            Server server = solution_copy.servers[j];

            for(int k = 0; k < server.jobs.size(); k++){

                int server_job_duration = solution_copy.duration_matrix[j][server.jobs[k].column];

                int local_job_duration = solution_copy.duration_matrix[j][local_job.column];

                // swap local server job with server job if the server has capacity for the new job
                if(server.capacity - server_job_duration + local_job_duration < 0){
                    continue;
                }

                swap(solution_copy.servers[j].jobs[k], solution_copy.local_server.jobs[i]);

                int cost = solution_copy.calculate();

                if(cost < result){
                    result = cost;
                    solution = solution_copy;
                }
            }
        }
    }
    
    return result;
}