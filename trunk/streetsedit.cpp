#include "streetsedit.h"
#include "ui_streetsedit.h"
#include <QDebug>

StreetsEdit::StreetsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreetsEdit)
{
    ui->setupUi(this);
    FillTable();
}

StreetsEdit::~StreetsEdit()
{
    delete ui;
}

void StreetsEdit::FillTable()
{
    QString str_oper = "SELECT * FROM hm_streets";
    QSqlQueryModel * model_Oper = new QSqlQueryModel(0);
        model_Oper->setQuery(str_oper);
        model_Oper->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Название улицы"));
    ui->tableView->setModel(model_Oper);
    ui->tableView->hideColumn(0);
}

void StreetsEdit::on_pushButton_3_clicked()
{
    if (ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString()=="")
    {
        QMessageBox::information(this,trUtf8("Предупреждение"),trUtf8("Выберите элемент"));
    }
    else
    {
        if (QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Вы уверенны что хотите удалить элемент?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        {
            QString str_rem_street = "DELETE FROM hm_streets WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
            qDebug() << "request: " << str_rem_street;
            QSqlQuery sqlQuery_rem_street(str_rem_street);
            qDebug() << "result: " << sqlQuery_rem_street.exec();
            ui->lineEdit->clear();
        }
    }
    FillTable();
}

void StreetsEdit::on_pushButton_clicked()
{
    qDebug() << "selected: " << ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString str_upd_street = "UPDATE hm_streets SET name='"+ui->lineEdit->text()+
    "' WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    qDebug() << str_upd_street;
    QSqlQuery sqlQuery_upd_street;
    if (!sqlQuery_upd_street.exec(str_upd_street))
    {
        QMessageBox::warning(this,trUtf8("Ошибка"),trUtf8("Запись не обновлена"));
    }
    else
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Запись обновлена"));
    }
    ui->lineEdit->clear();
    FillTable();
}

void StreetsEdit::on_pushButton_2_clicked()
{
    if (ui->lineEdit->text()=="")
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Заполните название"));
    }
    else
    {
        QString str_add_street = "INSERT INTO hm_streets (name)"
                                "VALUES ('"+ui->lineEdit->text()+"');";
        QSqlQuery sqlQuery_add_street;
        if (!sqlQuery_add_street.exec(str_add_street))
        {
            QMessageBox::warning(this,trUtf8("Ошибка"),trUtf8("Запись не обновлена"));
        }
        else
        {
            QMessageBox::information(this,trUtf8("Информация"),trUtf8("Запись добавлена"));
        }

    }
    ui->lineEdit->clear();
    FillTable();
}

void StreetsEdit::on_tableView_clicked(QModelIndex index)
{
    ui->lineEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
}
