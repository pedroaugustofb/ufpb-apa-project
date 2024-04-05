#include <iostream>
#include <vector>
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/job.h"
#include "../components/calculate-total-cost.h"

using namespace std;

int swap_inter_server_local(vector<Server> &servers, LocalServer &local_server, int rows, int best_solution){
    vector<Server> servers_copy = servers;
    LocalServer local_server_copy = local_server;

   for(int i = 0; i < local_server_copy.jobs.size(); i++){
       Job local_job = local_server_copy.jobs[i];
        for(int j = 0; j < rows; j++){
            Server server = servers_copy[j];

            
            for(int k = 0; k < server.jobs.size(); k++){

                // swap local server job with server job if the server has capacity for the new job
                if(server.capacity - server.jobs[k].duration + local_job.duration < 0){
                    continue;
                }

                swap(servers_copy[j].jobs[k], local_server_copy.jobs[i]);

                int cost = calculateTotalCost(servers_copy, local_server, rows);

                if(cost < best_solution){
                    servers = servers_copy;
                    local_server = local_server_copy;
                    best_solution = cost;
                }
            }
        }
    }
    
    return best_solution;
}