#include <iostream>
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../entities/job.h"
#include "../entities/solution.h"

using namespace std;


// Objetivo: Trocar Jobs do Servidor Local com Jobs de Servidores se a troca for benéfica
// Complexidade: O(n^2)
int swap_inter_server_local(Solution &solution, int result){

    Solution solution_copy = solution;

    vector<Job> servers_jobs;

    for(int i = 0; i < solution_copy.servers.size(); i++){
        for(int j = 0; j < solution_copy.servers[i].jobs.size(); j++){
            servers_jobs.push_back(solution_copy.servers[i].jobs[j]);
        }
    }

    // Itera sobre os Jobs do servidor local
    for(int i = 0; i < solution_copy.local_server.jobs.size(); i++){

        // Coluna do Job nas matrizes
        int column = solution_copy.local_server.jobs[i].column;

        // Itera sobre os Jobs dos servidores
        for(int j = 0; j < servers_jobs.size(); j++){

            // Linha do Servidor nas matrizes
            int row = servers_jobs[j].row;

            // Duração do Job (servidor) nesse servidor
            int duration = solution_copy.duration_matrix[row][j];

            // Duração do Job (local) nesse servidor
            int local_duration = solution_copy.duration_matrix[row][column];

            // Se o servidor não possuir capacidade para o Job, não faz sentido trocar
            if(solution_copy.servers[row].capacity - duration + local_duration < 0) continue;

            // Realiza a troca
            // Complexidade do swap: O(1)
            swap(servers_jobs[j], solution_copy.local_server.jobs[i]);

            // Atualiza o row dentro dos Jobs
            solution_copy.local_server.jobs[i].row = -1;
            servers_jobs[j].row = row;

            // Atualiza o row dentro dos Jobs
            solution_copy.local_server.jobs[i].row = row;
            servers_jobs[j].row = -1;

            // Atualiza o usage do servidor
            solution_copy.servers[row].usage += local_duration;

            int cost = solution_copy.calculate();

            // Se o custo for menor, atualiza a solução
            if(cost < result){
                result = cost;
                solution = solution_copy;
                continue;
            }

            // Se o custo não for menor, desfaz a alteração:

            // Realiza a troca
            // Complexidade do swap: O(1)
            swap(servers_jobs[j], solution_copy.local_server.jobs[i]);

            // Atualiza o row dentro dos Jobs
            solution_copy.local_server.jobs[i].row = -1;
            servers_jobs[j].row = row;

            // Atualiza o usage do servidor
            solution_copy.servers[row].usage -= local_duration;

        }
    }
    
    return result;
}