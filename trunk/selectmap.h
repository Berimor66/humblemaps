#ifndef SELECTMAP_H
#define SELECTMAP_H

#include <QDialog>
#include <QHash>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QString>

namespace Ui {
    class SelectMap;
}

class SelectMap : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMap(QWidget *parent = 0);
    ~SelectMap();
    int id;
    void setup(QString table);

private:
    Ui::SelectMap *ui;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // SELECTMAP_H
