#ifndef HMSURFACE_H
#define HMSURFACE_H

#include <QObject>
#include <QString>

class HMSurface : public QObject
{
    Q_OBJECT
public:
    explicit HMSurface(QObject *parent = 0);
    QString name;
    double max_speed;

signals:

public slots:

};

#endif // HMSURFACE_H
