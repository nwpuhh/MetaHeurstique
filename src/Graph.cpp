#include "../header/Graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::make_pair;
using std::ofstream;

/* implement the private functions */
/*
**** Description: judge in the graph, is there an edge between p1 and p2 ****
**** return 0  -> there is
            -1 -> there is not, and the reason is no such points
            1  -> there is not, but there are two points specific, just no such edge
*/
int Graph::exist_edge_between_two_points(const Point & p1,const Point & p2) const
{
    bool exist_point_from = false, exist_point_to = false;
    //Firstly, check the two points are in the list of points or not
    for(int i = 0; i < points.size(); i++)
    {
        if(points[i] == p1) 
            exist_point_from = true;
        if(points[i] == p2)
            exist_point_to = true;
    }
    //if one of two points is not in the list of points, means add failed,
    //it should add the point before add new edge
    if( !exist_point_from || !exist_point_to)
        return -1;
    else  //it is time to check the edges
    {
        for(int i = 0; i < edges.size(); i++)
        {
            if(edges[i].first == p1 && edges[i].second.second == p2)
                return 0;
        }
        return 1;
    }
}

/**
**** Description: get the vector of edge_info of edge between Point p1 and p2
**** return ret -> The vector of the edges between p1 and p2
        -> if size is 0; means no edges, else get the info
*/
vector<edge_info> Graph::get_edge_info_by_points(const Point & p1, const Point & p2) const
{   
    vector<edge_info> ret = vector<edge_info>();
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges[i].first == p1 && edges[i].second.second == p2)
            ret.push_back(edges[i].second.first);
    }
    return ret;
}

/**
**** Description: print the points of the graph
**/
void Graph::print_points()
{
    for(int i = 0; i < points.size(); i++)
    { points[i].print_point();}
}

/*
**** define the function for updating the state for the selected edge
*/
void Graph::change_state_of_selected_edge(const pair<Point, pair<edge_info, Point> > & edge_selected)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges[i].first == edge_selected.first && edges[i].second.second == edge_selected.second.second)
        {
            edges[i].second.first.used = 0;
            break;
        }
    }
}

/*
**** define the function for recovering the state for the selected edge
*/
void Graph::recover_state_of_selected_edge(const pair<Point, pair<edge_info, Point> > & edge_selected)
{
    for(int i = 0; i < edges.size(); i++)
    {
        if(edges[i].first == edge_selected.first && edges[i].second.second == edge_selected.second.second)
        {
            //recover the state of edge selected
            edges[i].second.first.used = 1;
            break;
        }
    }
}

/* implement the public functions */
/* !!! need to be changed: which need the specific order of operations
**** Description: change the vector of job to be the type of graph
**** input -> vector<Job>
*/
void Graph::load_jobs(vector<Job> & jobs)
{
    // For all graph in time arragement, there are two special points
    Point start = Point(-1, 0, NULL);
    Point finish = Point(-1, -1, NULL);
    // add the first two points 
    if(!(add_new_point(start) && add_new_point(finish)))
    {
        cout << "Add <start> or <finish> point failed" << endl;
        exit(-1);
    }
    // iterate all the jobs
    for(int i = 0; i < jobs.size(); i++)
    {
        /* For each Job, at first add all the points!!! */
        for(int j = 0; j < jobs[i].get_ops_nums(); j++)
        {
            // get the pointer of operation of Job i and Op j
            Operation* op_temp_p = jobs[i].get_op_p_index(j);
            Point temp(i, j, op_temp_p);
            //add the points by the iteration of operations
            if(!add_new_point(temp))
            {   
                print_points();
                temp.print_point();
                cout << "The load error! in Job " << i << " Op " << j << endl; 
                exit(-1);
            }
        }
        /* Add edges in the graph!!! */
        //add the first edge for each Job
        edge_info start_first_op = {0, -1, 1};
        Point first_point = get_point_by_job_and_op(i, 0);
        pair<Point, pair<edge_info, Point> >  edge_temp_first = make_pair(start, make_pair(start_first_op, first_point));
        if(!add_new_edge(edge_temp_first))
        {
            cout << "Add first edge between <start> and <OP0> for Job" << i << "is failed" << endl;
            exit(-1); 
        }
        /* Then, it is the time to add the edges between points in the Job */
        for(int j = 0; j < jobs[i].get_ops_nums()-1; j++)
        {
            Point temp1 = get_point_by_job_and_op(i, j);
            Point temp2 = get_point_by_job_and_op(i, j+1);
            Operation* op_temp_p = temp1.get_op_related_p();
            // iterate the pairs for the operation before, where add all possible edge for points
            for(int k = 0; k < op_temp_p->get_pairs_num(); k++)
            {   
                //get every possible pair <machine, time>
                pair<int, int> pair_temp = op_temp_p->get_machine_time_pair_by_index(k);
                edge_info p_p_temp = {pair_temp.second, pair_temp.first, 1};
                pair<Point, pair<edge_info, Point> >  edge_temp = make_pair(temp1, make_pair(p_p_temp, temp2));
                if(!add_new_edge(edge_temp))
                {
                    cout << "Add edge between <OP" << j << "> and <OP" << j+1 << "> failed" << endl;
                    exit(-1);
                }
            }   
        }
        /* At last, add the last edge between last point for a Job and the <finish> */
        Point temp_last = get_point_by_job_and_op(i, jobs[i].get_ops_nums()-1);
        Operation* op_temp_last_p = temp_last.get_op_related_p();
        for(int k = 0; k < op_temp_last_p->get_pairs_num(); k++)
        {
            //get every possible pair <machine, time>
            pair<int, int> pair_last_temp = op_temp_last_p->get_machine_time_pair_by_index(k);
            edge_info p_last_temp = {pair_last_temp.second, pair_last_temp.first, 1};
            pair<Point, pair<edge_info, Point> >  edge_temp_last = make_pair(temp_last, make_pair(p_last_temp, finish));
            if(!add_new_edge(edge_temp_last))
            {
                cout << "Add edge between <OP" << jobs[i].get_ops_nums()-1 << "> and <finish>" << " failed" << endl;
                exit(-1);
            }
        }
    }
    //print_points();
    cout << "Finish the load!" << endl;
}

/* 
**** Description: add the new point in the graph ****
**** return true  -> add succeufully
****        false -> add failed, means there are the same point
*/
bool Graph::add_new_point(const Point & p_new)
{
    for(int i = 0; i < points.size(); i++)
    {
        if(p_new == points[i])
            return false;
    }
    //means that the point is new in job_no and op_no
    points.push_back(p_new);
    return true;
}

/*
**** Description: add new edge in the graph ****
**** return true  -> add succ
***  return false -> add failed
                probably because of Point, edge label
*/
bool Graph::add_new_edge(const pair<Point, pair<edge_info, Point> > & edge_new)
{
    int ret = exist_edge_between_two_points(edge_new.first, edge_new.second.second);
    if(!ret) // if there is an edge between p1 and p2
    {
        vector<edge_info> existed = get_edge_info_by_points(edge_new.first, edge_new.second.second);
        edge_info info_new = edge_new.second.first;
        // iterate the sitaution of all infos used as the edges
        // if the machine_no is the same, there is no possible to add edge
        for(int i = 0; i < existed.size(); i++)
        {
            if(existed[i].machine_no == info_new.machine_no)
                return false;
        }
        edges.push_back(edge_new);
        return true;
    }
    else if(ret == -1) //no such points
    {
        cout << "Add edge error, no such points" << endl;
        return false;
    }
    else   
    {
        edges.push_back(edge_new);
        return true;
    }
}

/**
**** Description: get the point in the graph by the index of Job_no and op_no
*/
Point& Graph::get_point_by_job_and_op(const int job_no, const int op_no)
{
    Point target(job_no, op_no);
    for(int i = 0; i < points.size(); i++)
    {
        //if find the right point, return the point
        if(points[i] == target)
            return points[i];
    }
    target = Point();
    return target;
}

/**
**** Description: This function aims to change the graph into the type of 
    vector<<P1, p2>, edges_between_p1_p2 >, for easily get those points who have 
    serveral different edges, meaning serveral possibilites.
**/
point_to_point_edges_vector Graph::get_more_edges_between_two_points() const
{
    point_to_point_edges_vector p_p_edges_vector;

    // loop the edges, so that get the vector of items which have more that 1 edges between 2 points
    for(int i = 0; i < edges.size(); i++)
    {
        bool flag_exist = false;
        for(int j = 0; j < p_p_edges_vector.size(); j++)
        {
            // judge the two points have been added into the vector or not
            if(p_p_edges_vector[j].first.first == edges[i].first && p_p_edges_vector[j].first.second == edges[i].second.second)
            {   
                flag_exist = true;
                p_p_edges_vector[j].second.push_back(edges[i]);
                break;
            }
        }

        // judge it needs add at the end of vector or not
        if(!flag_exist)
        {
            pp_pair pp_pair_temp = make_pair(edges[i].first, edges[i].second.second);
            vector< pair<Point, pair<edge_info, Point> > > pp_edges_temp = vector< pair<Point, pair<edge_info, Point> > >();
            pp_edges_temp.push_back(edges[i]);
            p_p_edges_vector.push_back(make_pair(pp_pair_temp, pp_edges_temp));
        }
    }
    
    //select those one who has more than one possibilities.
    for(auto iter = p_p_edges_vector.begin(); iter != p_p_edges_vector.end(); )
    {
        if((iter->second).size() == 1)
            iter = p_p_edges_vector.erase(iter);
        else
            iter++;
    }
    return p_p_edges_vector;
}

// print the vector we have gotten
void Graph::print_pp_edges_vector()
{
    point_to_point_edges_vector v = get_more_edges_between_two_points();
    for(int i = 0; i < v.size(); i++) 
    {
        v[i].first.first.print_point(); 
        cout << "|";
        v[i].first.second.print_point();
        cout << ":";
        v[i].second.size();
    } 
}


/*
**** Description: Generate the selector for the servral edges for two points
**** Input => The vector of number of the serveral possible choix for each pair<Point, Point>
**** return the vector of int[vect_pp_info.size()],
     where items are one selection. 
*/
vector<vector<int> > Graph::get_vector_of_selection(const vector<int> & p_p_e_num, int start, int last)
{
    vector<vector<int> > selections = vector<vector<int> >();
    //The basic condition, return the vector of enum of the items in the last items
    if(last == 0)
        return selections;

    if(start == last-1)
    {
        for(int i = 0; i < p_p_e_num[start]; i++)
        {
            vector<int> temp(1);
            temp[0] = i+1;
            selections.push_back(temp);
        }
    }
    else
    {
        vector<vector<int> > selections_rest = get_vector_of_selection(p_p_e_num, start+1, last);
    
        for(int i = 0; i < p_p_e_num[start]; i++)
        {
            for(int j = 0; j < selections_rest.size(); j++)
            {
                selections_rest[j].push_back(i+1);
                selections.push_back(selections_rest[j]);
                selections_rest[j].pop_back();
            }        
        }
    }
    return selections;
}


/**
**** Description: Get the size of vector from the point_to_point_edges_vector
*/
vector<int> Graph::get_size_vector_of_vector_more_edges()
{
    vector<int> ret;
    point_to_point_edges_vector edges_vector = get_more_edges_between_two_points();
    for(int i = 0; i < edges_vector.size(); i++)
        ret.push_back(edges_vector[i].second.size());
    return ret;
}

/* The part of updating the graph with selected edges and selected machine order*/
/*
**** Description: update the graph with the edges selected, which is decided by the 
      vector of chosen, and the p_p_e_vector
*/
void Graph::update_graph_by_edges_selected(const point_to_point_edges_vector & p_p_e_vector, const vector<int> & edges_selected)
{
    int edges_size = edges_selected.size();
    for(int i = 0; i < edges_size; i++)
    {
        for(j = 0; j < p_p_e_vector[i].second.size(); j++)
        {
            // if it is not the selected edge, change the state of used => 0
            // because of the vector should be in reverse
            if(j != edges_selected[edges_size - 1 -i] - 1)
                update_graph_by_edges_selected(p_p_e_vector[i].second[j]);
        }
    }
}

void Graph::recover_graph_by_edges_selected(const point_to_point_edges_vector & p_p_vector, const vector<int> & edges_selected)
{
    int edges_size = edges_selected.size();
    for(int i = 0; i < edges_size; i++)
    {
        for(j = 0; j < p_p_e_vector[i].second.size(); j++)
        {
            // if it is not the selected edge, change the state of used => 1 for recover  
            // because of the vector should be in reverse
            if(j != edges_selected[edges_size - 1 -i] - 1)
                recover_state_of_selected_edge(p_p_e_vector[i].second[j]);
        }
    }
}


/**** Part of visualisation of graph ****/
/**
**** Description: draw the graph by generating the .dot file to use the dot tool
****    in graphviz library
**** !!note: This is the function of draw graph initilaized
            no color specific!! no choosing path!!
*/
void Graph::graph_draw()
{
    ofstream out("graph_out.dot");
    if(out.is_open())
    {
        /* At first, output the form of the dot */
        out << "digraph graph_out{\n";
        /* Then output all the points info */
        Point start(-1, 0, NULL);
        Point finish(-1, -1, NULL);
        for(int i = 0; i < points.size(); i++)
        {   
            //should classify the start and the end points
            if(points[i] == start)
                out << "\tP01" << " [label=\"START\"]\n"; //P01 is the start
            else if(points[i] == finish)
                out << "\tP00" << " [label=\"FINISH\"]\n";  //P00 is the end
            else     // normal points
            {
                int job_no = points[i].get_point_job_no()+1;
                int op_no  = points[i].get_point_op_no()+1;
                out << "\tP" << job_no << op_no << " [label=\"o" << job_no << op_no << "\"]\n";
            }
        }
        out << "\n";
        /* Finally,add the edges in the graph */
        for(int i = 0; i < edges.size(); i++)
        {
            Point from = edges[i].first;
            Point to = edges[i].second.second;
            edge_info edge_label = edges[i].second.first;
            int job_no_from = from.get_point_job_no()+1;
            int op_no_from  = from.get_point_op_no()+1;
            int job_no_to   = to.get_point_job_no()+1;
            int op_no_to    = to.get_point_op_no()+1;
            out << "\tP" << job_no_from<<op_no_from << "->" 
                << "P" << job_no_to<<op_no_to 
                << " [label=\"<machine " << edge_label.machine_no 
                << ", time " << edge_label.weight << ">\"]\n";
        }
        out << "}";
        out.close();
    }
}