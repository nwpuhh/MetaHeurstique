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

