#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "node.h"
#include <QVector>

class map : public QObject
{
    Q_OBJECT
public:
    explicit map(QObject *parent = 0);
    //HMNode * _nodes[10000];
    QVector<HMNode*> nodes;

    void add_node(void);
    HMNode* get_node_by_id(int id);
    HMEdge* get_edge_by_id(int id);
    int     find_node_by_xy(int x, int y);
    int     find_edge_by_xy(int x, int y);


signals:

public slots:

};

#endif // MAP_H
