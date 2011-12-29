#include "fueledit.h"
#include "ui_fueledit.h"

FuelEdit::FuelEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuelEdit)
{
    ui->setupUi(this);
    FillTable();
}

FuelEdit::~FuelEdit()
{
    delete ui;
}

void FuelEdit::FillTable()
{
    QString str_oper = "SELECT * FROM hm_fuel";
    QSqlQueryModel * model_Oper = new QSqlQueryModel(0);
    model_Oper->setQuery(str_oper);
    model_Oper->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Название топлива"));
    model_Oper->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Цена топлива"));
    ui->tableView->setModel(model_Oper);
    ui->tableView->hideColumn(0);
}

void FuelEdit::on_pushButton_3_clicked()
{
    if (ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString()=="")
    {
        QMessageBox::information(this,trUtf8("Предупреждение"),trUtf8("Выберите элемент"));
    }
    else
    {
        if (QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Вы уверенны что хотите удалить элемент?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        {
            QString str_rem_fuel = "DELETE FROM hm_fuel WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
            qDebug() << "request: " << str_rem_fuel;
            QSqlQuery sqlQuery_rem_fuel(str_rem_fuel);
            qDebug() << "result: " << sqlQuery_rem_fuel.exec();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
    FillTable();
}

void FuelEdit::on_pushButton_clicked()
{
    qDebug() << "selected: " << ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString str_upd_fuel = "UPDATE hm_fuel SET name='"+ui->lineEdit->text()+"', price='"+ui->lineEdit_2->text()+
    "' WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    qDebug() << str_upd_fuel;
    QSqlQuery sqlQuery_upd_fuel;
    if (!sqlQuery_upd_fuel.exec(str_upd_fuel))
    {
        QMessageBox::warning(this,trUtf8("Ошибка"),trUtf8("Запись не обновлена"));
    }
    else
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Запись обновлена"));
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    FillTable();
}

void FuelEdit::on_pushButton_2_clicked()
{
    if (ui->lineEdit->text()=="")
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Заполните название"));
    }
    else
    {
        QString str_add_fuel = "INSERT INTO hm_fuel (name, price)"
                                "VALUES ('"+ui->lineEdit->text()+"', "+ui->lineEdit_2->text()+");";
        QSqlQuery sqlQuery_add_fuel;
        if (!sqlQuery_add_fuel.exec(str_add_fuel))
        {
            QMessageBox::warning(this,trUtf8("Ошибка"),trUtf8("Запись не обновлена"));
        }
        else
        {
            QMessageBox::information(this,trUtf8("Информация"),trUtf8("Запись добавлена"));
        }

    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    FillTable();
}

void FuelEdit::on_tableView_clicked(QModelIndex index)
{
    ui->lineEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
}
