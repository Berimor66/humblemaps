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
};

#endif // STREETSEDIT_H
