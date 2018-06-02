#include "../header/FileTreater.h"
#include "../header/Graph.h"
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
        cout << "Before Machines" << endl;
        /*Problem!!!*/
        //vector<Machine> machines = treater.get_machines();
        /*
        cout << "print the jobs:" << endl;
        for(int i = 0; i < treater.get_jobs_num(); i++)
        {
            cout << "Job " << i << ":"<< endl;
            jobs[i].print_job_info();
        } 
        */

        cout << "Before Graph construct" << endl;
        Graph graph = Graph();
        cout << "Construct Graph succ" << endl;
        graph.load_jobs(jobs);
        cout << "load Jobs succ" << endl;
        graph.graph_draw();
        
        cout << "Before choix vector" << endl;
        vector<int> choix_vector = graph.get_size_vector_of_vector_more_edges();
        cout << "After choix vector" << endl;

        int possible_noraml = 1;
        for(int i = 0; i < choix_vector.size(); i++)
           { cout << choix_vector[i] << " | "; possible_noraml *= choix_vector[i]; }
        cout << endl;

        vector< vector<int> > selections = graph.get_vector_of_selection(choix_vector, 0, choix_vector.size());

        cout << "After selections gets" << endl;
        /*
        int cnt = 0;
        for(int i = 0; i < selections.size(); i++)
        {
            for(int j = 0; j < selections[i].size(); j++)
                cout << selections[i][j] << " ";
            cout << endl;
            cnt++;
        }
        cout << possible_noraml << endl;
        cout << cnt << endl;*/
        //graph.print_pp_edges_vector();

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