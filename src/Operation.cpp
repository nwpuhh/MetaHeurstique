#include "header/Operation.h"
#include <iostream>

using std::cout;
using std::endl;

Operation::Operation() : pair_num(0),
    machine_time_pairs(vector< pair<int, int> >())
{}

Operation::Operation(const int num)
{
    machine_time_pairs = vector< pair<int, int> >(num);
    pair_num = num;
}

Operation::Operation(const int num, const vector< pair<int, int> >& pairs)
{
    pair_num = num;
    machine_time_pairs = pairs;
}

void Operation::add_pair(const pair<int, int> & p)
{
    machine_time_pairs.push_back(p);
    pair_num++;
}

void Operation::set_pair_index(const int i, const int machine_no, const int time)
{
    pair<int, int> temp_pair(machine_no, time);
    machine_time_pairs[i] = temp_pair;
}

pair<int, int> Operation::get_machine_time_pair_by_index(const int index) const
{ return machine_time_pairs[index]; }

void Operation::print_op_info()
{
    cout << "\t\t------" << endl;
    for(int i = 0; i < pair_num; i++)
    {
        cout << "\t\t<machine_no = " << machine_time_pairs[i].first
             << ", time = " << machine_time_pairs[i].second << ">" << endl;
    }
}