#ifndef HMSTREET_H
#define HMSTREET_H

#include <QObject>
#include <QString>

class HMStreet : public QObject
{
    Q_OBJECT
public:
    explicit HMStreet(QObject *parent = 0);
    QString name;

signals:

public slots:

};

#endif // HMSTREET_H
