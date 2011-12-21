#ifndef MAP_H
#define MAP_H

#include <QObject>
#include "node.h"

class map : public QObject
{
    Q_OBJECT
public:
    explicit map(QObject *parent = 0);
    HMNode * nodes[10000];

signals:

public slots:

};

#endif // MAP_H
