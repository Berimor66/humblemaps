#include "mapobject.h"

MapObject::MapObject()
{
}
MapObject::MapObject(const QString name)
{
    data["name"] = name;
}

MapObject::~MapObject()
{
}
