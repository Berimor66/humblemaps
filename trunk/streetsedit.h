#ifndef STREETSEDIT_H
#define STREETSEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlQueryModel>

namespace Ui {
    class StreetsEdit;
}

class StreetsEdit : public QDialog
{
    Q_OBJECT

public:
    explicit StreetsEdit(QWidget *parent = 0);
    ~StreetsEdit();

private:
    Ui::StreetsEdit *ui;
    void FillTable();

private slots:
    void on_tableView_clicked(QModelIndex index);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // STREETSEDIT_H
