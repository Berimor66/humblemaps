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
    explicit HMEdge(HMNode *_start, HMNode *_end);
    ~HMEdge(void);
    HMNode *start;
    HMNode *end;
    int street_id;

signals:

public slots:

};

#endif // EDGE_H
