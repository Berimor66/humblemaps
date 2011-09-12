#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QObject>
#include <QHash>

/*
 * Discussion: main map object
 *
 */
class MapObject : public QObject {
public:
    MapObject();
    MapObject(const QString name);
    ~MapObject();
    quint64 id;          //unic object id
    quint16 type;
    QHash<QString, QString> data;
protected:
private:
};

#endif // MAPOBJECT_H
