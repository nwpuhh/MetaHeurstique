#include "../header/FileTreater.h"
#include <iostream>
#include <fstream>
#include <cstring>
#define LINE_MAX_READ 256
using std::cout;
using std::endl; 
using std::ifstream;
using std::make_pair;

/* implement the private functions */
Job FileTreater::get_from_string(char* data)
{
    /* define the sep */
    char* sep = " ";
    //for split the string
    char* p;
    p = strtok(data, sep);
    int ops_num = atoi(p);
    Job temp_job(ops_num);
    for(int i = 0; i < ops_num; i++)
    {
        //get the number of pairs
        p = strtok(NULL, sep);
        int pairs_num = atoi(p);
        //set every Operation
        Operation temp_op(pairs_num);
        for(int j = 0; j < pairs_num; j++)
        {
            p = strtok(NULL, sep);
            int machine_no = atoi(p);
            p = strtok(NULL, sep);
            int time = atoi(p);
            temp_op.set_pair_index(j, machine_no, time);
        }
        //set the Operation into the Job
        temp_job.set_op_index(i, temp_op);
    }
    return temp_job;
}

/*
**** Description: Function private for add pairs in the map of machines
        input -> machines& + machine_no + Job_no + Operation_no
**/
void FileTreater::add_pairs_in_machines(machines & m_s, int m_no, int j_no, int o_no)
{
    pair<int, int> temp_pair = make_pair(j_no, o_no);
    bool flag_exist = false;
    for(auto iter = m_s.begin(); iter != m_s.end(); iter++)
    {
        if(iter->first == m_no)
        {
            iter->second.push_back(temp_pair);
            flag_exist = true;
            break;
        }
    }

    // if not find, add the <m_no, <j_no, o_no> > into the map
    if(!flag_exist)
    {
        vector<pair<int, int> > new_vector;
        new_vector.push_back(temp_pair);
        m_s.insert(pair<int, vector<pair<int, int> > >(m_no, new_vector));
    }
}

/* implement the public functions */
FileTreater::FileTreater(char* path) 
{
    char data[LINE_MAX_READ];
    file_path = path;
    cout << file_path<< endl;
    ifstream infile(path);
    if(!infile.is_open())
    {
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    infile.getline(data, LINE_MAX_READ);
    cout << data << endl;

    /* define the sep */
    char* sep = " ";
    //for split the first line to get the numbers
    char* p;
    //get the jobs_num
    p = strtok(data, sep);
    jobs_num = atoi(p);
    p = strtok(NULL, sep);
    machines_num = atoi(p);
    infile.close();
}

int FileTreater::get_jobs_num()
{ return jobs_num; }

int FileTreater::get_machines_num()
{ return machines_num; }


Job FileTreater::get_ith_job(const int line)
{
    ifstream infile(file_path);
    char data[LINE_MAX_READ];
    int i = 0;
    while(i++ != line)
    {
        if(infile.eof()) /*if the file went to end*/
        {
            cout << "The line is to high" << endl;
            return Job();
        }
        infile.getline(data, LINE_MAX_READ);
    }
    //finaly, read the ith line
    infile.getline(data, LINE_MAX_READ);
    Job temp_job = get_from_string(data);
    infile.close();
    return temp_job;
}

const vector<Job> FileTreater::get_jobs()
{
    ifstream infile(file_path);
    char data[LINE_MAX_READ];
    vector<Job> jobs(jobs_num);

    //ignore the first line
    infile.getline(data, LINE_MAX_READ);
    for(int i = 0; i < jobs_num; i++)
    {
        infile.getline(data, LINE_MAX_READ);
        jobs[i] = get_from_string(data);
    }
    infile.close();
    return jobs;
}

/*
**** Description: implementing the interface between the .txt and machines
        with the help of vector<Job> which we have gotten
*/
machines FileTreater::get_all_operation_in_machine(vector<Job> jobs)
{
    machines machines_in_text;
    Operation* temp;
    for(int i = 0; i < jobs.size(); i++)
    {
        for(int j = 0; j < jobs[i].get_ops_nums(); j++)
        {
            temp = jobs[i].get_op_p_index(j);
            for(int k = 0; k < temp->get_pairs_num(); k++)
            {
                // pair<m_no, time>
                pair<int, int> temp_pair_m_t = temp->get_machine_time_pair_by_index(k); 
                add_pairs_in_machines(machines_in_text, temp_pair_m_t.first, i, j);
            }
        }
    }

    return machines_in_text;
}

void FileTreater::print_machines_info(const machines & m_s) 
{
    for(auto iter = m_s.begin(); iter != m_s.end(); iter++)
    {
        cout << iter->first << endl;
        for(int i = 0; i < iter->second.size(); i++)
            cout << "<Job_no " << iter->second[i].first << ", Op_no " << iter->second[i].second << ">" << endl;
    }
}