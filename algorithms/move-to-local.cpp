#include <iostream>
#include "../entities/solution.h"

using namespace std;

// Objetivo: Mover Jobs que possuem valor de custo maior do que o custo do servidor local para o servidor local se esse possuir capacidade
// Complexidade: O(n^3)
int move_to_local(Solution &solution, int result){

    Solution solution_copy = solution;


    // Itera sobre os servidores
    for(int i = 0; i < solution_copy.servers.size(); i++){
        // Itera sobre os Jobs do servidor
        for(int j = 0; j < solution_copy.servers[i].jobs.size(); j++){
            
            // Coluna do Job nas matrizes
            int column = solution_copy.servers[i].jobs[j].column;
                
            // Custo do Job nesse servidor
            int job_cost = solution_copy.cost_matrix[i][column];

            // Se o custo do Job nesse servidor for menor do que o custo do servidor local, não faz sentido trocar
            if (job_cost < solution_copy.local_server.fixed_cost) continue;
            
            // Adiciona o Job no servidor local
            solution_copy.local_server.jobs.push_back(solution_copy.servers[i].jobs[j]);

            // Atualiza o row do Job
            solution_copy.local_server.jobs.back().row = -1;

            // Remove o Job do servidor
            // Complexidade do erase: O(n)
            solution_copy.servers[i].jobs.erase(solution_copy.servers[i].jobs.begin() + j);

            int duration = solution_copy.duration_matrix[i][column];
            
            // Atualiza a capacidade do servidor
            solution_copy.servers[i].usage -= duration;

            int cost = solution_copy.calculate();

            if(cost < result){
                result = cost;
                solution = solution_copy;
                continue;
            }

            // Se o custo não for menor, desfaz a alteração:

            // Adiciona o Job no servidor
            solution_copy.servers[i].jobs.push_back(solution_copy.local_server.jobs.back());

            // Atualiza o row do Job
            solution_copy.servers[i].jobs.back().row = i;

            // Remove o Job do servidor local
            // Complexidade do pop_back: O(1)
            solution_copy.local_server.jobs.pop_back();

            // Atualiza a capacidade do servidor
            solution_copy.servers[i].usage += duration;
        }
    }

    return result;
}