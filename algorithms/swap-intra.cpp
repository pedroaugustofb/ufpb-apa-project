#include <iostream>
#include <vector>
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/job.h"
#include "../components/log.h"
#include "../components/print-solution.h"

using namespace std;


int swapIntra(int **duration_matrix, int **cost_matrix, int local_server_cost, vector<Server> servers, LocalServer local_server, int rows, int columns, int greedy_solution){
    // 1. iterar cada servidor
    // 2. para cada servidor, iterar cada job
    // 3. para cada job, iterar cada outro job
    // 4. para cada outro job, calcular o custo de trocar os dois jobs de lugar
    // 5. se o custo for menor, trocar os dois jobs de lugar
    // 6. se não, passar para o proximo outro job
    // 7. se não houver outro job, passar para o proximo job
    // 8. se não houver mais jobs, passar para o proximo servidor

    bool changed = false;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < servers[i].jobs.size(); j++){
            for(int k = 0; k < servers[i].jobs.size(); k++){
                if(j == k) continue;

                vector<Server> servers_copy = servers;

                Job job1 = servers_copy[i].jobs[j];
                Job job2 = servers_copy[i].jobs[k];

                servers_copy[i].jobs[j] = job2;

                servers_copy[i].jobs[k] = job1;

                int cost = 0;

                for(int l = 0; l < rows; l++){
                    for(int m = 0; m < servers_copy[l].jobs.size(); m++){
                        cost += servers_copy[l].jobs[m].cost;
                    }
                }

                cost += local_server.getCost();


                if(cost < greedy_solution){
                    servers = servers_copy;
                    greedy_solution = cost;
                    changed = true;
                }
            }
        }
    }

    // fazer a mesma coisa com os jobs do servidor local comparando com cada job de cada servidor
    for(int i = 0; i < local_server.jobs.size(); i++){
        for(int j = 0; j < rows; j++){
            for(int k = 0; k < servers[j].jobs.size(); k++){
                vector<Server> servers_copy = servers;
                LocalServer local_server_copy = local_server;

                Job job1 = servers_copy[j].jobs[k];
                Job job2 = local_server_copy.jobs[i];

                servers_copy[j].jobs[k] = job2;

                local_server_copy.jobs[i] = job1;

                int cost = 0;

                for(int l = 0; l < rows; l++){
                    for(int m = 0; m < servers_copy[l].jobs.size(); m++){
                        cost += servers_copy[l].jobs[m].cost;
                    }
                }

                cost += local_server_copy.getCost();


                if(cost < greedy_solution){
                    servers = servers_copy;
                    local_server = local_server_copy;
                    greedy_solution = cost;
                    changed = true;
                }
            }
        }
    }
    
    if (changed){
        log("Showing swap intra solution...");
        printSolution(servers, local_server, duration_matrix, cost_matrix, rows, columns);
    }
    else {
        log("----------------------------------------------------- |");
        log("No changes were made in Swap-Intra neighborhood");
        log("because the swap was not beneficial");
        log("----------------------------------------------------- |");
    }

    int servers_total_cost = 0;
    int local_server_total_cost = local_server.getCost();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < servers[i].jobs.size(); j++) {
            servers_total_cost += servers[i].jobs[j].cost;
        }
    }

    return servers_total_cost + local_server_total_cost;

}