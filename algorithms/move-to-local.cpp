#include <iostream>
#include "../entities/solution.h"

using namespace std;

// Objetivo: Mover Jobs que possuem valor de custo maior do que o custo do servidor local para o servidor local se esse possuir capacidade
// Complexidade: O(n^3)
void move_to_local(Solution &solution){

    // Itera sobre os servidores
    for(int i = 0; i < solution.servers.size(); i++){

        bool improvement = false;

        // Itera sobre os Jobs do servidor
        for(int j = 0; j < solution.servers[i].jobs.size(); j++){
            
            // Coluna do Job nas matrizes
            int column = solution.servers[i].jobs[j].column;
                
            // Custo do Job nesse servidor
            int job_cost = solution.cost_matrix[i][column];

            // Se o custo do Job nesse servidor for menor do que o custo do servidor local, não faz sentido trocar
            if (job_cost < solution.local_server.fixed_cost) continue;
            
            // Adiciona o Job no servidor local
            solution.local_server.jobs.push_back(solution.servers[i].jobs[j]);

            // Atualiza o row do Job
            solution.local_server.jobs.back().row = -1;

            // Remove o Job do servidor
            // Complexidade do erase: O(n)
            solution.servers[i].jobs.erase(solution.servers[i].jobs.begin() + j);

            int duration = solution.duration_matrix[i][column];
            
            // Atualiza a capacidade do servidor
            solution.servers[i].usage -= duration;

            improvement = true;
            break;
        }

        if(improvement) break;
    }
}