#ifndef SURFACEEDIT_H
#define SURFACEEDIT_H

#include <QDialog>
#include <QMessageBox>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlQueryModel>

namespace Ui {
    class SurfaceEdit;
}

class SurfaceEdit : public QDialog
{
    Q_OBJECT

public:
    explicit SurfaceEdit(QWidget *parent = 0);
    ~SurfaceEdit();

private:
    Ui::SurfaceEdit *ui;
    void FillTable();

private slots:
    void on_tableView_clicked(QModelIndex index);
    void on_pushButton_save_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();
};

#endif // SURFACEEDIT_H
