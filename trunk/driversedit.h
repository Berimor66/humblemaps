#ifndef DRIVERSEDIT_H
#define DRIVERSEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlQueryModel>

namespace Ui {
    class driversedit;
}

class driversedit : public QDialog
{
    Q_OBJECT

public:
    explicit driversedit(QWidget *parent = 0);
    ~driversedit();

private:
    Ui::driversedit *ui;
    void FillTable();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_tableView_clicked(QModelIndex index);
};

#endif // DRIVERSEDIT_H
