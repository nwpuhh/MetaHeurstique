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

struct comp{
    pp_pair pair_key;
    bool operator< (const comp s)
    {
        return (pair_key.first < s.pair_key.first) || (pair_key.first == s.pair_key.first && pair_key.second < s.pair_key.second);
    }
};

typedef map< comp, vector< pair<Point, pair<edge_info, Point> > > > pp_edges;

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

public:
    Graph() { points = vector<Point>(); edges = vector< pair<Point, pair<edge_info, Point> > >(); }
    void load_jobs(vector<Job> & jobs);
    bool add_new_point(const Point & p_new);
    bool add_new_edge(const pair<Point, pair<edge_info, Point> > & edge_new);
    Point& get_point_by_job_and_op(const int job_no, const int op_no);
    pp_edges get_edges_by_pp();

    //need to add the function for visualisation
    void graph_draw();
};

#endif