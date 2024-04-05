#include <iostream>
#include <vector>
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/job.h"
#include "../components/calculate-total-cost.h"

using namespace std;

int swap_inter_server_local(vector<Server> &servers, LocalServer &local_server, int rows, int best_solution){
   for(int i = 0; i < local_server.jobs.size(); i++){
        for(int j = 0; j < rows; j++){
            vector<Server> servers_copy = servers;
            int server_capacity = servers_copy[j].capacity;
            
            for(int k = 0; k < servers[j].jobs.size(); k++){
                LocalServer local_server_copy = local_server;

                // swap local server job with server job if the server has capacity for the new job
                if(server_capacity - servers[j].jobs[k].duration + local_server.jobs[i].duration < 0){
                    continue;
                }

                Job job1 = servers_copy[j].jobs[k];
                Job job2 = local_server_copy.jobs[i];

                servers_copy[j].jobs[k] = job2;

                local_server_copy.jobs[i] = job1;

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