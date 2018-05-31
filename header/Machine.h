#ifndef MACHINE_H_
#define MACHINE_H_

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Machine 
{
private: 
    int machine_no;
    // <Job_no, Op_no> is the item in that vector, which is 
    // one of the work the machine can do
    vector< pair<int, int> >  related_ops;
 
public:
    Machine() {machine_no = 0;related_ops=vector< pair<int, int> >();}
    Machine(const int m_no) 
    {machine_no = m_no; related_ops = vector< pair<int, int> >();}
    void add_op(const pair<int, int> & op_related)
    {related_ops.push_back(op_related);}  
    int get_machine_no() { return machine_no;}
};

#endif