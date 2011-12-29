#ifndef FUELEDIT_H
#define FUELEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlQueryModel>

namespace Ui {
    class FuelEdit;
}

class FuelEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FuelEdit(QWidget *parent = 0);
    ~FuelEdit();

private:
    Ui::FuelEdit *ui;
    void FillTable();

private slots:
    void on_tableView_clicked(QModelIndex index);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // FUELEDIT_H
