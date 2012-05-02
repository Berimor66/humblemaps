#ifndef CARSEDIT_H
#define CARSEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlQueryModel>

namespace Ui {
    class CarsEdit;
}

class CarsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CarsEdit(QWidget *parent = 0);
    ~CarsEdit();

private:
    Ui::CarsEdit *ui;
    void FillTable();

private slots:
    void on_tableView_clicked(QModelIndex index);
    void on_pushButton_save_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();
};

#endif // CARSEDIT_H
