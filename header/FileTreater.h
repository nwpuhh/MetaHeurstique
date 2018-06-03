#ifndef __FILETREATER_H_
#define __FILETREATER_H_

#include "Job.h"
#include "Operation.h"
#include <vector>
#include <utility>
#include <cstdlib>

using std::vector;
using std::pair;

typedef map< int, vector< pair<int, int> > > machines;

class FileTreater 
{
private:
    char*       file_path;
    int         jobs_num;
    int         machines_num;

    Job get_from_string(char* data);

    // private function for help insert the items in machines
    void add_pairs_in_machines(machines & m_s, int m_no, int j_no, int o_no);

public:
    //define the constructor of FileTreater
    FileTreater(){file_path = NULL; jobs_num = 0; machines_num = 0;}
    FileTreater(char* path);
    //define the interface functions of the class
    int get_jobs_num();
    int get_machines_num();
    Job get_ith_job(const int i);

    /*Implement the interface between the Job and Machine*/
    const vector<Job> get_jobs();
    machines get_all_operation_in_machine(vector<Job> jobs);
    void print_machines_info(const machines & m_s);
};

#endif