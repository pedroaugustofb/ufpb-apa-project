#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "solution.h"
#include "server.h"
#include "local-server.h"
#include "../components/log.h"

using namespace std;

Solution::Solution(int **DURATION_MATRIX, int **COST_MATRIX, int JOBS_LENGTH, int SERVERS_LENGTH, int LOCAL_SERVER_COST , vector<Server> servers){
    this->jobs_length = JOBS_LENGTH;
    this->servers_length = SERVERS_LENGTH;
    this->duration_matrix = DURATION_MATRIX;
    this->cost_matrix = COST_MATRIX;
    this->local_server.fixed_cost = LOCAL_SERVER_COST;
    this->servers = servers;
}

int Solution::calculate(){
    int servers_cost = this->calculateServersCost();
    int local_server_cost = this->local_server.jobs.size() * this->local_server.fixed_cost;
    return servers_cost + local_server_cost;
}

int Solution::calculateServersCost(){
    int servers_cost = 0;

    for (int i = 0; i < this->servers.size(); i++) {
        for (int j = 0; j < this->servers[i].jobs.size(); j++) {
            int column = this->servers[i].jobs[j].column;
            servers_cost += this->cost_matrix[i][column];
        }
    }

    return servers_cost;
}




void Solution::print(){
    endl();
    log("----------------------------------------------------- |");
    log("Servers: ");

    for (int i = 0; i < this->servers_length; i++) {
        Server server = this->servers[i];
        log("Server " + to_string(i + 1));
        log("Capacity: " + to_string(server.capacity));

        if(server.jobs.size() == 0) {
            log("No jobs allocated to this server");
            continue;
        }

        log("Jobs allocated to this server: ");
        for (int j = 0; j < server.jobs.size(); j++) {
            int column = server.jobs[j].column;
            int duration = this->duration_matrix[i][column];
            int cost = this->cost_matrix[i][column];

            log("Job " + to_string(column) + ": " + "(duration: " + to_string(duration) + ") (cost: " + to_string(cost) + ")");
        }

        log("Total time allocated: " + to_string(server.usage));

        int cost = 0;

        for (int j = 0; j < server.jobs.size(); j++) {
            int column = server.jobs[j].column;
            cost += this->cost_matrix[i][column];
        }

        log("Total cost: " + to_string(cost));
        if(i != this->servers_length - 1) {
            log("");
        }
    }

    log("");
    int servers_total_cost = 0;
    int local_server_total_cost = this->local_server.getCost();

    for (int i = 0; i < this->servers_length; i++) {
        for (int j = 0; j < this->servers[i].jobs.size(); j++) {
            int column = this->servers[i].jobs[j].column;
            int cost = this->cost_matrix[i][column];
            servers_total_cost += cost;
        }
    }

    log("Servers total cost: " + to_string(servers_total_cost));

    log("");

    if(this->local_server.jobs.size() > 0) {
        log("Local Jobs: ");
        for (int i = 0; i < this->local_server.jobs.size(); i++) {
            int column = this->local_server.jobs[i].column;
            log("Job " + to_string(column));
        }
    }

    log("Local server total cost ( for " + to_string(this->local_server.jobs.size()) + " job(s) ): " + to_string(local_server_total_cost));

    log("");

    log("Total cost: " + to_string(servers_total_cost + local_server_total_cost));
    log("----------------------------------------------------- |");
}

void Solution::createFile(string filename){

    ofstream file;

    int best_solution = this->greedy_solution < this->vnd_solution ? this->greedy_solution : this->vnd_solution;
    int serves_cost = this->calculateServersCost();
    int local_server_cost = this->local_server.jobs.size() * this->local_server.fixed_cost;

    file.open(filename);

    file << best_solution << endl;
    file << serves_cost << endl;
    file << local_server_cost << endl;
    file << endl;
    
    for (int i = 0; i < this->servers_length; i++) {
        for (int j = 0; j < this->servers[i].jobs.size(); j++) {
            int column = this->servers[i].jobs[j].column;
            file << column << " ";
        }
        
        if (i != this->servers_length - 1)
            file << endl;
    }


    file.close();
}