#include "edge.h"

HMEdge::HMEdge(QObject *parent)
{
    street_id = -1;
}

HMEdge::HMEdge(HMNode *_start, HMNode *_end)
{
    start = _start;
    end = _end;
    street_id = 0;
    surface_id = 0;
    if ( start->add_st_edge(this) && end->add_end_edge(this) )
        ;
    else {
        start->del_edge(this);
        end->del_edge(this);
    }
}

HMEdge::~HMEdge(void){
    start->del_edge(this);
    end->del_edge(this);
}
