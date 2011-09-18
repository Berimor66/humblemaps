/****************************************************************************\

    file: mapobject.h

    This file is part of HumbleMaps.

    Copyright (C) 2011 Ermolaev Aleksey
    Copyright (C) 2011 Nazarov Yuriy
    Copyright (C) 2011 Chubenko Stanislav

    HumbleMaps is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    HumbleMaps is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HumbleMaps. If not, see <http://www.gnu.org/licenses/>.



\****************************************************************************/

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
