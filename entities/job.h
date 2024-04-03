#ifndef JOB_H
#define JOB_H

class Job {
public:
    Job(int column, int duration = 0, int cost = 0); // constructor
    int column; // matrices column index
    int duration; // matrices row index
    int cost; // matrices column index
};

#endif