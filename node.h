#ifndef NODE_H
#define NODE_H
#include <QObject>
#include "edge.h"

class HMEdge;

class HMNode : public QObject
{
    Q_OBJECT
public:
    explicit HMNode(QObject *parent = 0);
    explicit HMNode(int _x, int _y);
    ~HMNode(void);
    double x;
    double y;
    HMEdge *start[4];
    HMEdge *end[4];
    bool add_st_edge(HMEdge * edge);
    bool add_end_edge(HMEdge * edge);
    bool del_edge(HMEdge * edge);
signals:

public slots:

};

#endif // NODE_H
