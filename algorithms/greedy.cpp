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

    // 1. iterar cada job
    // 2. para cada job, iterar cada servidor, a fim de encontrar um servidor que tenha capacidade suficiente para alocar o job
    // 3. se encontrar podemos ignorar a verificação para outros servidores e alocar o job ao servidor escolhido
    // 4. se não encontrar, não há servidores para alocar o job, e então esse job deve ser alocado no servidor local

    // 1. iterar cada job
    for(int i = 0; i < columns; i++) {
        // 2. para cada job, iterar cada servidor, a fim de encontrar um servidor que tenha capacidade suficiente para alocar o job
        for(int j = 0; j < rows; j++) {
            int capacity = servers[j].capacity;
            int usage = servers[j].usage;
            int duration = duration_matrix[j][i];
            int cost = cost_matrix[j][i];
            

            // 3. se encontrar podemos ignorar a verificação para outros servidores e alocar o job ao servidor escolhido
            if(capacity >= usage + duration) {
                servers[j].usage += duration;
                servers[j].jobs.push_back(Job(i, duration, cost));
                break;
            }
            
            // 4. se não encontrar, não há servidores para alocar o job, e então esse job deve ser alocado no servidor local
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
