#ifndef __FILETREATER_H_
#define __FILETREATER_H_

#include "Job.h"
#include "Operation.h"
#include "Machine.h"
#include <vector>
#include <utility>
#include <cstdlib>

using std::vector;
using std::pair;

class FileTreater 
{
private:
    char*       file_path;
    int         jobs_num;
    int         machines_num;

    Job get_from_string(char* data);

public:
    //define the constructor of FileTreater
    FileTreater(){file_path = NULL; jobs_num = 0; machines_num = 0;}
    FileTreater(char* path);
    //define the interface functions of the class
    int get_jobs_num();
    int get_machines_num();
    Job get_ith_job(const int i);
    const vector<Job> get_jobs();

    /*Implement the interface between the Job and Machine*/
    //const vector<Machine> get_machines();
};

#endif