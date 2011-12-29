#include "node.h"

HMNode::HMNode(QObject *parent)
{
}

HMNode::HMNode(int _x, int _y)
{
    x = _x;
    y = _y;
    end[0] = NULL;
    end[1] = NULL;
    end[2] = NULL;
    end[3] = NULL;
    start[0] = NULL;
    start[1] = NULL;
    start[2] = NULL;
    start[3] = NULL;
}

bool HMNode::add_st_edge(HMEdge *edge)
{
    for(int i = 0; i < 4; i++){
        if ( start[i] == NULL){
            start[i] = edge;
            return true;
        }
    }
    return false;
}

bool HMNode::add_end_edge(HMEdge *edge)
{
    for(int i = 0; i < 4; i++){
        if ( end[i] == NULL){
            end[i] = edge;
            return true;
        }
    }
    return false;
}

bool HMNode::del_edge(HMEdge *edge)
{
    bool res = false;
    for(int i = 0; i < 4; i++){
        if ( end[i] == edge){
            end[i] = NULL;
            res = true;
        }
    }
    for(int i = 0; i < 4; i++){
        if ( start[i] == edge){
            start[i] = NULL;
            res = true;
        }
    }
    return res;
}

HMNode::~HMNode()
{
    for(int i = 0; i < 4; i++){
        if ( end[i] != NULL){
            delete end[i];
        }
    }
    for(int i = 0; i < 4; i++){
        if ( start[i] != NULL){
            delete start[i];
        }
    }
}
