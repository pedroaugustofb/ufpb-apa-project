#include <iostream>


#ifndef JOB_H
#define JOB_H

class Job {
public:
    Job(int column, int row); // constructor
    int column; // matrices column index
    int row; // matrices row index
};

#endif