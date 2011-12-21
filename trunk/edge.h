#ifndef HMEDGE_H
#define HMEDGE_H
#include <QObject>
#include "node.h"

class HMNode;

class HMEdge : public QObject
{
    Q_OBJECT
public:
    explicit HMEdge(QObject *parent = 0);
    HMNode *start;
    HMNode *end;
signals:

public slots:

};

#endif // EDGE_H
