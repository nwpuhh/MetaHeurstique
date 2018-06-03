#include "../header/FileTreater.h"
#include "../header/Graph.h"
#include <vector>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;

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
       // machines machines_info = treater.get_all_operation_in_machine(jobs);
        //treater.print_machines_info(machines_info);
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

        /*cout << "Before choix vector" << endl;
       
        cout << "After choix vector" << endl;
        */
        //int possible_noraml = 1;
       /* for(int i = 0; i < choix_vector.size(); i++)
           { cout << choix_vector[i] << " | "; possible_noraml *= choix_vector[i]; }
        cout << endl;
        */

        point_to_point_edges_vector p_p_e_vector = graph.get_more_edges_between_two_points();
        vector<int> choix_vector = graph.get_len_vector_of_vector_more_edges(p_p_e_vector);
        vector< vector<int> > selections = graph.get_vector_of_selection(choix_vector, 0, choix_vector.size());
        
        //try the first selection. Firstly, we need to print the first choix
        for(int i = 0; i < selections[0].size(); i++)
            cout << selections[0][i] << " ";
        cout << endl;

        //Then, we update the graph, then to see is there any changes
        graph.update_graph_by_edges_selected(p_p_e_vector, selections[0]);
        //graph.recover_graph_by_edges_selected(p_p_e_vector, selections[0]);

        cout << "before printing machines info" << endl;
        machines m_graph = graph.get_machines_used_in_graph();
        graph.print_machines_info(m_graph);

        
        // no need to print all machine order, take care of the first machine does not exist.
        cout << "Before printing all order for the first machine" << endl;
        /*vector<pair<int, int> > try_o;
        try_o.push_back(make_pair(1,1));
        try_o.push_back(make_pair(2,2));
        try_o.push_back(make_pair(3,3));
        cout << "Build new vector" << endl;*/
        //graph.print_order_for_one_machine(graph.get_order_for_one_machine(m_graph[1], 0, m_graph[1].size() -1));


        graph.graph_draw();
        

    }
    return 0;
}