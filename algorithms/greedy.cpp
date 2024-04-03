#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
// .h
#include "../entities/job.h"
#include "../entities/server.h"
#include "../entities/local-server.h"
#include "../components/log.h"
#include "../components/print-server.h"
#include "../components/print-matrix.h"

using namespace std;

/**
 * Greedy algorithm to solve the problem
 *  To solve using greedy algorithm, we need:
 * 
 * @param duration_matrix           dinamic matrix with the duration of each job in each server
 * @param cost_matrix               dinamic matrix with the cost of each job in each server
 * @param local_server_cost         cost of the local server
 * @param servers                   vector with the servers
 * @param local_server              vector with the local server
 * @param rows                      number of jobs 
 * @param columns                   number of servers
 * 
 * @obs:                            both matrices have the same size
*/
int greedy(int **&duration_matrix, int **&cost_matrix, int local_server_cost, vector<Server> &servers, LocalServer &local_server, int rows, int columns) {
    
    // para tomar uma decisão vamos olhar para o tempo de execução (duration) de cada job, ignorando o custo
    // isso porque assim, olhamos para apenas a parte mais satisfatória do proximo job a ser alocado
    // porém, primeiro devemos ordenar as colunas das matrizes de acordo com o custo, assim podemos alocar os jobs mais baratos primeiro
    // 1. somar as colunas das matrizes de custo
    // 2. ordenar colunas das matrizes de acordo com o custo
    // 3. reordenar as colunas das matrizes de com a ordem obtida no passo 2
    // 4. iterar cada job
    // 5. para cada job, iterar cada servidor, a fim de encontrar um servidor que tenha capacidade suficiente para alocar o job
    // 6. se encontrar podemos ignorar a verificação para outros servidores e alocar o job ao servidor escolhido
    // 7. se não encontrar, não há servidores para alocar o job, e então esse job deve ser alocado no servidor local
    
    // 1. somar as colunas das matrizes de custo
    vector<pair<int, int>> sum_columns;
    for(int i = 0; i < columns; i++) {
        int sum = 0;
        for(int j = 0; j < rows; j++) {
            sum += cost_matrix[j][i];
        }
        sum_columns.push_back(make_pair(sum, i));
    }

    // 2. ordenar colunas das matrizes de acordo com o custo
    sort(sum_columns.begin(), sum_columns.end(), less<pair<int, int>>());

    // 3. reordenar as colunas das matrizes de com a ordem obtida no passo 2
    int **new_duration_matrix = new int*[rows];
    int **new_cost_matrix = new int*[rows];

    for(int i = 0; i < rows; i++) {
        new_duration_matrix[i] = new int[columns];
        new_cost_matrix[i] = new int[columns];
    }

    for(int i = 0; i < columns; i++) {
        int column = sum_columns[i].second;
        for(int j = 0; j < rows; j++) {
            new_duration_matrix[j][i] = duration_matrix[j][column];
            new_cost_matrix[j][i] = cost_matrix[j][column];
        }
    }

    // duration_matrix = new_duration_matrix;
    // cost_matrix = new_cost_matrix;

    // 4. iterar cada job
    for(int i = 0; i < columns; i++) {
        // 5. para cada job, iterar cada servidor, a fim de encontrar um servidor que tenha capacidade suficiente para alocar o job
        for(int j = 0; j < rows; j++) {
            int capacity = servers[j].capacity;
            int usage = servers[j].usage;
            int duration = duration_matrix[j][i];
            int cost = cost_matrix[j][i];
            

            // 6. se encontrar podemos ignorar a verificação para outros servidores e alocar o job ao servidor escolhido
            if(capacity >= usage + duration) {
                servers[j].usage += duration;
                servers[j].jobs.push_back(Job(i, duration, cost));
                break;
            }
            
            // 7. se não encontrar, não há servidores para alocar o job, e então esse job deve ser alocado no servidor local
            if(j == rows - 1) {
                local_server.jobs.push_back(Job(i, duration, cost));
            }
        }
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
