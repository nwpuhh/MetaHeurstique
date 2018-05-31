#include "../header/Job.h"
#include <iostream>

using std::cout;
using std::endl;

Job::Job(const int num_ops)
{
    ops_num = num_ops;
    ops = vector<Operation>(num_ops);
}

Job::Job(const int num_ops, const vector<Operation> & op_s) : 
    ops_num(num_ops), ops(op_s)
{}

void Job::add_op(const Operation & op)
{
    ops.push_back(op);
    ops_num++;
}

void Job::set_op_index(const int index, const Operation & op)
{ ops[index] = op; }

Operation* Job::get_op_p_index(const int index)
{ return &ops[index]; }

void Job::print_job_info()
{
    cout << "\t++++++" << endl;
    for(int i = 0; i < ops_num; i++)
    {
        cout << "\toperation " << i << endl;
        ops[i].print_op_info();
    }
}
