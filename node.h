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
    double x;
    double y;
    HMEdge *start[4];
    HMEdge *end[4];
signals:

public slots:

};

#endif // NODE_H
