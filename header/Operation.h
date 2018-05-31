#ifndef __OPERATION_H_
#define __OPERATION_H_

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class Operation
{
private:
    vector< pair<int, int> > machine_time_pairs;
    int pair_num;

public:
    Operation();
    Operation(const int num);
    Operation(const int num, const vector< pair<int, int> > & pairs);
    void add_pair(const pair<int, int> & p);
    void set_pair_index(const int i,const int machine_no, const int time);
    pair<int, int> get_machine_time_pair_by_index(const int index) const;
    int get_pairs_num()  { return pair_num; } 
    void print_op_info();
};

#endif