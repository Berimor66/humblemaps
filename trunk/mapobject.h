#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>

/*
 * Discussion: main map object
 *
 */
class MapObject : public QObject {
public:
    MapObject();
    ~MapObject();
    quint64 id;          //unic object id
    quint16 type;
    //need map here
protected:
private:
};

#endif // MAPOBJECT_H
