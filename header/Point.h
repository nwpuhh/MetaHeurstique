#ifndef __POINT_H_
#define __POINT_H_
#include "Operation.h"
#include <cstdlib>
#include <iostream>

#define LABEL_LENGTH 10
using std::cout;
using std::endl;

/*
** define the Point class in the Graph **
*/
class Point
{
private:
    int         job_no;
    int         op_no;
    Operation * op_related;  //one point one operation

public:
    Point() { job_no = -1; op_no = -1; op_related = NULL; }
    //using the default of Operation * is NULL, to make sure 
    //the "start" and "last" situation
    Point(int no_job, int no_op, Operation * op_p = NULL)
        { job_no = no_job; op_no = no_op; op_related = op_p; }
    //define the copy constructor
    Point(const Point & p)
        { job_no = p.job_no; op_no = p.op_no; op_related = p.op_related;}
    int get_point_job_no() { return job_no; }
    int get_point_op_no()  { return op_no; }
    Operation* get_op_related_p() const {return op_related;}
    //define the meaning of "equal" between points
    // the job_no and op_no are only indicator of the point
    bool operator==(const Point & p) const
    { return ((job_no == p.job_no) && (op_no == p.op_no)) ? true : false;}
    bool operator!=(const Point & p) const
    { return (*this == p) ? false : true; }
    bool operator<(const Point & p) const
    { return (job_no < p.job_no)||(job_no == p.job_no && op_no < p.op_no); }
    void print_point() 
    { cout << "<job_no " << job_no << ", op_no " << op_no << ">" << endl; }
};

#endif