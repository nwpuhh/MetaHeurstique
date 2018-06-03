#ifndef __JOB_H_
#define __JOB_H_

#include "Operation.h"
#include <map>

using std::vector;
using std::map;

typedef map< int, vector< pair<int, int> > > machines;

class Job 
{
private:
    vector<Operation> ops;
    int         ops_num;

public:
    Job() {ops = vector<Operation>(); ops_num = 0;}
    Job(const int num_ops);
    Job(const int num_ops, const vector<Operation> & op_s);
    void add_op(const Operation & op);
    void set_op_index(const int index, const Operation & op);
    Operation* get_op_p_index(const int index);
    int get_ops_nums() { return ops_num; }
    void print_job_info();

};

#endif