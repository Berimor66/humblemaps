#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "node.h"
#include <QHash>

class map : public QObject
{
    Q_OBJECT
public:
    explicit map(QObject *parent = 0);
    QHash<int, HMNode *> nodes;
    QHash<int, HMEdge *> edges;

    void    add_node(int x, int y);
    void    del_selected_node(void);
    HMNode* get_node_by_id(int id);
    HMEdge* get_edge_by_id(int id);
    int     find_node_by_xy(int x, int y);
    int     find_edge_by_xy(int x, int y);


signals:

public slots:

};

#endif // MAP_H
