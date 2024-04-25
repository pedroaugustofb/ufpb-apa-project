#include <iostream>
#include "../entities/solution.h"
#include "../entities/job.h"

using namespace std;

// Objetivo: Mover Jobs que possuem valor de custo menor do que o custo do servidor local para os servidores se esses possuirem capacidade
// Complexidade: O(n^3)
void move_from_local(Solution &solution){

    // Itera sobre os servidores
    for( int i = 0; i < solution.servers.size(); i++){

        bool improvement = false;

        // Itera sobre os Jobs do servidor local
        for(int j = 0; j < solution.local_server.jobs.size(); j++){

            // Job a ser movido
            Job job = solution.local_server.jobs[j];

            // Duração do Job nesse servidor
            int job_duration = solution.duration_matrix[i][job.column];

            // Se o servidor não possuir capacidade para o Job, não faz sentido trocar
            if(solution.servers[i].capacity < job_duration) continue;
            
            // Custo do Job nesse servidor
            int job_cost = solution.cost_matrix[i][job.column];

            // Se o custo do Job nesse servidor for maior ou igual ao custo do servidor local, não faz sentido trocar
            if(job_cost >= solution.local_server.fixed_cost) continue;
            
            // Atualiza o row do Job
            job.row = i;
            
            // Adiciona o Job no servidor
            solution.servers[i].jobs.push_back(job);

            // Atualiza a capacidade do servidor
            solution.servers[i].usage += job_duration;

            // Remove o Job do servidor local
            // Complexidade do erase: O(n)
            solution.local_server.jobs.erase(solution.local_server.jobs.begin() + j);

            improvement = true;
            break;
        }

        if(improvement) break;
    }

}