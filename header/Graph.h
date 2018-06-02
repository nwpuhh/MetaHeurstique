#ifndef __GRAPH_H_
#define __GRAPH_H_

#include "Point.h"
#include "Job.h"
#include <map>
#include <cstdlib>

using std::map;

typedef struct Edge_info {
    int weight;
    int machine_no;
    int used;
} edge_info;

typedef pair<Point, Point> pp_pair;

typedef vector< pair< pp_pair, vector< pair<Point, pair<edge_info, Point> > > > > point_to_point_edges_vector;

class Graph 
{
private:
    vector<Point> points;
    //edge is the tuple of <point, label(the value), point>
    vector< pair<Point, pair<edge_info, Point> > > edges;

    //private function
    int exist_edge_between_two_points(const Point & p1,const Point & p2) const;
    vector<edge_info> get_edge_info_by_points(const Point & p1, const Point & p2) const;
    void print_points();

    //define the function for changing the state of selected edge, which will made the 
    // "used" in the edge_info to be 2 if this edge is selected
    void change_state_of_selected_edge(const pair<Point, pair<edge_info, Point> > & edge_selected);

    //function for recover the state of selected edges
    void recover_state_of_selected_edge(const pair<Point, pair<edge_info, Point> > & edge_selected);

public:
    Graph() { points = vector<Point>(); edges = vector< pair<Point, pair<edge_info, Point> > >(); }
    void load_jobs(vector<Job> & jobs);
    bool add_new_point(const Point & p_new);
    bool add_new_edge(const pair<Point, pair<edge_info, Point> > & edge_new);
    Point& get_point_by_job_and_op(const int job_no, const int op_no);
   // pp_edges get_edges_by_pp();
    point_to_point_edges_vector get_more_edges_between_two_points() const;
    void print_pp_edges_vector();


    // get all combination of the edges
    vector<vector<int> > get_vector_of_selection(const vector<int> & p_p_e_num, int start, int last);
    vector<int> get_size_vector_of_vector_more_edges();

    //define the function for changing the graph
    void update_graph_by_edges_selected(const point_to_point_edges_vector & p_p_vector, const vector<int> & edges_selected);
    void recover_graph_by_edges_selected(const point_to_point_edges_vector & p_p_vector, const vector<int> & edges_selected);

    //need to add the function for visualisation
    void graph_draw();
};

#endif