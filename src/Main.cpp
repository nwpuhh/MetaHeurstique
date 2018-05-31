#include "header/FileTreater.h"
#include "header/Graph.h"
#include <vector>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::pair;

int main(int argc, char* argv[])
{   
    if(argc != 2)
    {
        cout << "Wrong arguement number!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        //cout << "We have the right argument" << endl;
        //cout << argv[1] << endl;
        FileTreater treater = FileTreater(argv[1]);

        cout << "After the Filetreater" << endl;
        cout << treater.get_jobs_num() << endl;

        vector<Job> jobs = treater.get_jobs();
        vector<Machine> machines = treater.get_machines();
        /*
        cout << "print the jobs:" << endl;
        for(int i = 0; i < treater.get_jobs_num(); i++)
        {
            cout << "Job " << i << ":"<< endl;
            jobs[i].print_job_info();
        } 
        */
        Graph graph = Graph();
        graph.load_jobs(jobs);
        graph.graph_draw();

        /*
        comp c1 = {std::make_pair(Point(1,3), Point(2,3))};
        comp c2 = {std::make_pair(Point(1,3), Point(2,2))};
        if(c1 < c2)
            cout << "c1 < c2" << endl;
        else
            cout << "Non" << endl;
        */
        /*Point p1(1,1, NULL);
       Point p2(1,2, NULL);
       p1.print_point();
       p2.print_point();*/

    }
    return 0;
}