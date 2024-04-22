#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
// .h
#include "../entities/job.h"
#include "../entities/solution.h"

using namespace std;



int greedy(Solution &solution) {

    // Critério Guloso: Alocar os jobs de acordo com o menor custo de cada um em cada servidor
    // 1° Passo - Achar a média (soma) de custo de cada job em cada servidor
    // 2° Passo - Ordenar as colunas da matrizes de acordo com a ordenação encontrada pelo sort
    // 3° Passo - Encontrar o melhor servidor disponível para cada job
    // 4° Passo - Alocar o job no servidor que lhe proporciona o menor custo

    // Inicia um vetor de pares, onde o primeiro elemento é a soma dos custos de cada job e o segundo é o índice do job
    vector<pair<int, int>> sum_columns;

    // Calcula a soma dos custos de cada job em cada servidor a fim de encontrar uma média de custo para cada job
    for(int i = 0; i < solution.jobs_length; i++) {
        int sum = 0;
        for(int j = 0; j < solution.servers_length; j++) {
            sum += solution.cost_matrix[j][i];
        }

        // Complexidade do push_back: O(1)
        // Complexidade do make_pair: O(1)
        sum_columns.push_back(make_pair(sum, i));
    }

    // Complexidade do sort: O(n log n)
    sort(sum_columns.begin(), sum_columns.end(), less<pair<int, int>>());

    for(int i = 0; i < solution.jobs_length; i++) {
        int column = sum_columns[i].second;
        
        // Caso a coluna não sofra alteração de index (i), não é necessário realocar os valores
        if(column == i) continue;

        for(int j = 0; j < solution.servers_length; j++) {
            
            // Modificando a matriz de duração
            int temp = solution.duration_matrix[j][i];
            solution.duration_matrix[j][i] = solution.duration_matrix[j][column];
            solution.duration_matrix[j][column] = temp;
            
            // Modificando a matriz de custo
            temp = solution.cost_matrix[j][i];
            solution.cost_matrix[j][i] = solution.cost_matrix[j][column];
            solution.cost_matrix[j][column] = temp;
        }
    }


    // Alocando cada job no servidor que lhe proporciona o menor custo
    for(int i = 0; i < solution.jobs_length; i++) {

        // Achar o índice do servidor que possui o menor custo para o job i
        // caso não seja possível, significa que não existe server disponível para o job
        // logo deverá ser enviado para o local server
        int best_server_index = -1;

        // Complexidade do numeric_limits: O(1)
        int best_server_cost = numeric_limits<int>::max();

        for(int j = 0; j < solution.servers_length; j++) {

            // Duração do job i no servidor j
            int duration = solution.duration_matrix[j][i];

            // Custo do job i no servidor j
            int cost = solution.cost_matrix[j][i];

            // Se o custo do servidor j para o job i for maior que o melhor custo encontrado até o momento
            if(cost >= best_server_cost) continue;

            // Se o servidor j não possuir capacidade suficiente para alocar o job i, 
            // mesmo que esse tenha o melhor custo, está indisponível
            if(solution.servers[j].capacity < solution.servers[j].usage + duration) continue;

            // Se esse for o melhor servidor até agora, atualiza o melhor custo e o índice do servidor
            best_server_cost = cost;
            best_server_index = j;
        }

        // Se não foi encontrado um servidor disponível para o job i, o job i deve ser alocado no servidor local
        if(best_server_index == -1) {
            solution.local_server.jobs.push_back(Job(i, -1));
            continue;
        }

        // Alocando o job i no servidor que lhe proporciona o menor custo
        solution.servers[best_server_index].usage += solution.duration_matrix[best_server_index][i];
        solution.servers[best_server_index].jobs.push_back(Job(i, best_server_index));
    }

    // Calcula o custo da solução gulosa
    int greedy_solution = solution.calculate();
    solution.greedy_solution = greedy_solution;

    return greedy_solution;
}