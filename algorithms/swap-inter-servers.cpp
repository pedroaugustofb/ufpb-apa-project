#include <iostream>
#include <vector>
#include "../entities/solution.h"
#include "../entities/job.h"
#include "../components/log.h"

using namespace std;


// Objetivo: Trocar Jobs de Servidores se a troca for benéfica
void swap_inter_servers(Solution &solution){

    vector<pair<Job, int>> jobs;

    int index;
    for(int i = 0; i < solution.servers.size(); i++){
        
        index = 0;
        for(int j = 0; j < solution.servers[i].jobs.size(); j++ ){
            jobs.push_back(make_pair(solution.servers[i].jobs[j], index));
            index++;
        }
    }


    for(int i = 0; i < jobs.size(); i++){
        Job job1 = jobs[i].first;
        int index1 = jobs[i].second;

        int duration1_1 = solution.duration_matrix[job1.row][job1.column];
        int cost1_1 = solution.cost_matrix[job1.row][job1.column];

        bool improvement = false;

        for(int j = 0; j < jobs.size(); j++){

            Job job2 = jobs[j].first;

            if(job1.row == job2.row) continue;

            int index2 = jobs[j].second;

            int cost1_2 = solution.cost_matrix[job1.row][job2.column];
            int cost2_1 = solution.cost_matrix[job2.row][job1.column];
            int cost2_2 = solution.cost_matrix[job2.row][job2.column];

            int old_cost = cost1_1 + cost2_2;
            int new_cost = cost1_2 + cost2_1;

            if(new_cost >= old_cost) continue;

            int duration1_2 = solution.duration_matrix[job1.row][job2.column];
            int duration2_1 = solution.duration_matrix[job2.row][job1.column];
            int duration2_2 = solution.duration_matrix[job2.row][job2.column];

            if(solution.servers[job1.row].capacity - duration1_1 + duration1_2 < 0 ||
               solution.servers[job2.row].capacity - duration2_2 + duration2_1 < 0) continue;

            // Troca os Jobs
            // Complexidade do swap: O(1)
            swap(solution.servers[job1.row].jobs[index1], solution.servers[job2.row].jobs[index2]);

            // Atualiza a capacidade dos servidores
            solution.servers[job1.row].usage -= duration1_1 - duration2_1;
            solution.servers[job2.row].usage -= duration2_2 - duration1_2;

            // Atualiza o row dos Jobs
            solution.servers[job1.row].jobs[index1].row = job1.row;
            solution.servers[job2.row].jobs[index2].row = job2.row;

            improvement = true;
            break;

        }

        if(improvement) break;
    }

}