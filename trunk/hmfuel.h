#ifndef HMFUEL_H
#define HMFUEL_H

#include <QObject>
#include <QString>

class HMFuel : public QObject
{
    Q_OBJECT
public:
    explicit HMFuel(QObject *parent = 0);
    QString name;
    double price;

signals:

public slots:

};

#endif // HMFUEL_H
