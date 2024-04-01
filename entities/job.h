#ifndef JOB_H
#define JOB_H

class Job {
public:
    Job(int cost, int duration); // constructor

    int getCost(); // get the cost of the job
    int getDuration(); // get the duration of the job

    void setCost(int cost); // set the cost of the job
    void setDuration(int duration); // set the duration of the job

private:
    int cost; // job cost
    int duration; // job duration
};

#endif