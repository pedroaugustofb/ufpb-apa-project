#include <iostream>
#include "../entities/solution.h"
#include "../entities/job.h"

using namespace std;



// Objetivo: Mover Jobs que possuem valor de custo menor do que o custo do servidor local para os servidores se esses possuirem capacidade
// Complexidade: O(n^3)
int move_from_local(Solution &solution, int result){

    Solution solution_copy = solution;

    // Quantidade de Jobs no servidor local
    int jobs_size = solution_copy.local_server.jobs.size();

    if (jobs_size == 0){
        return result;
    }
    
    // Itera sobre os servidores
    for( int i = 0; i < solution_copy.servers.size(); i++){
        // Itera sobre os Jobs do servidor local
        for(int j = 0; j < solution_copy.local_server.jobs.size(); j++){

            // Job a ser movido
            Job job = solution_copy.local_server.jobs[j];

            // Duração do Job nesse servidor
            int job_duration = solution_copy.duration_matrix[i][job.column];

            // Se o servidor não possuir capacidade para o Job, não faz sentido trocar
            if(solution_copy.servers[i].capacity < job_duration) continue;
            
            // Custo do Job nesse servidor
            int job_cost = solution_copy.cost_matrix[i][job.column];

            // Se o custo do Job nesse servidor for maior ou igual ao custo do servidor local, não faz sentido trocar
            if(job_cost >= solution_copy.local_server.fixed_cost) continue;
            
            // Atualiza o row do Job
            job.row = i;
            
            // Adiciona o Job no servidor
            solution_copy.servers[i].jobs.push_back(job);

            // Atualiza a capacidade do servidor
            solution_copy.servers[i].usage += job_duration;

            // Remove o Job do servidor local
            // Complexidade do erase: O(n)
            solution_copy.local_server.jobs.erase(solution_copy.local_server.jobs.begin() + j);

            // Novo custo da solução
            int cost = solution_copy.calculate();

            // Somente atualiza a solução se o custo for menor
            if(cost < result){
                result = cost;
                solution = solution_copy;
                continue;
            }

            // Se o custo não for menor, desfaz a alteração:

            // Atualiza o row do Job
            job.row = -1;

            // Adiciona o Job no servidor local
            solution_copy.local_server.jobs.push_back(job);

            // Remove o Job do servidor
            // Complexidade do erase: O(n)
            solution_copy.servers[i].jobs.erase(solution_copy.servers[i].jobs.begin() + solution_copy.servers[i].jobs.size() - 1);

            // Atualiza a capacidade do servidor
            solution_copy.servers[i].usage -= job_duration;
        }
    }

    return result;
}