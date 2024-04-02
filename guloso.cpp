#include <iostream>
#include <vector>
#include "entities/job.h"
#include "entities/server.h"
#include <climits>
#include <algorithm>

using namespace std;

bool compareJobs(Job &a, Job &b) {
    return (a.getCost() / a.getDuration()) > (b.getCost() / b.getDuration());
}

bool compareServers(Server &a, Server &b) {
    return a.getCapacity() > b.getCapacity();
}

void GreedyAlgorithm(vector<Job> jobs, vector<Server> servers, int LOCAL_SERVER_COST){

}

// int GreedyAlgorithm(vector<Job> jobs, vector<Server> servers, int LOCAL_SERVER_COST) {

//     // To solve using greedy algorithm, we need:
//     // 1. Sort jobs by decreasing order of processing time
//     // 2. Assign each job to the server with the most available capacity
//     // 3. If there is no server with enough capacity, assign the job to the local server

//     // 1. Sort jobs by decreasing order of processing time
//     sort(jobs.begin(), jobs.end(), compareJobs);

//     vector<Job> localJobs;

//     // 2. Assign each job to the server with the most available capacity
//     for (auto &job: jobs) {
//         Server *selectedServer = nullptr;

//         int minLoad = INT_MAX; // to find the server with the most available capacity

//         for (auto &server: servers) {
            
//             if(server.getUsage() + job.getDuration() <= server.getCapacity() && server.getUsage() < minLoad) {
//                 minLoad = server.getUsage();
//                 selectedServer = &server;
//             }
//         }

//         if (selectedServer){
//             selectedServer->increseUsage(job.getDuration());
//         }
//         else localJobs.push_back(job);
//     }
// }