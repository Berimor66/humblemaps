#include "carsedit.h"
#include "ui_carsedit.h"

CarsEdit::CarsEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsEdit)
{
    ui->setupUi(this);
    FillTable();
}

CarsEdit::~CarsEdit()
{
    delete ui;
}

void CarsEdit::FillTable()
{
    QString str_oper = "SELECT hm_cars.id, hm_cars.name, hm_cars.speed, hm_fuel.name, hm_fuel.id FROM hm_cars INNER JOIN hm_fuel ON hm_cars.fuel_id = hm_fuel.id;";
    QSqlQueryModel * model_Oper = new QSqlQueryModel(0);
    model_Oper->setQuery(str_oper);
    model_Oper->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Название автомобиля"));
    model_Oper->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Максимальная скорость"));
    model_Oper->setHeaderData(3, Qt::Horizontal, QObject::trUtf8("Тип топлива"));
    ui->tableView->setModel(model_Oper);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(4);

    QSqlRelationalTableModel *comboModel = new QSqlRelationalTableModel(0);
    comboModel->setTable("hm_fuel");
    int comboIndex = comboModel->fieldIndex("id");
    comboModel->setRelation(comboIndex, QSqlRelation("hm_fuel", "id", "name"));
    comboModel->select();
    QSqlTableModel *comboRelModel = comboModel->relationModel(comboIndex);
    ui->comboBox->setModel(comboRelModel);
    ui->comboBox->setModelColumn(comboRelModel->fieldIndex("name"));
}

void CarsEdit::on_pushButton_del_clicked()
{
    if (ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString()=="")
    {
        QMessageBox::information(this,trUtf8("Предупреждение"),trUtf8("Выберите элемент"));
    }
    else
    {
        if (QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Вы уверенны что хотите удалить элемент?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        {
            QString str_rem_surface = "DELETE FROM hm_cars WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
            qDebug() << "request: " << str_rem_surface;
            QSqlQuery sqlQuery_rem_surface(str_rem_surface);
            qDebug() << "result: " << sqlQuery_rem_surface.exec();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
    FillTable();
}

void CarsEdit::on_pushButton_add_clicked()
{
    if (ui->lineEdit->text()=="")
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Заполните название"));
    }
    else
    {
        QString str_add_surface = "INSERT INTO hm_cars (name, speed, fuel_id)"
                                  "VALUES ('"+ui->lineEdit->text()+"', "+ui->lineEdit_2->text()+", "+QString::number(ui->comboBox->currentIndex())+");";

        QSqlQuery sqlQuery_add_surface;
        if (!sqlQuery_add_surface.exec(str_add_surface))
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

void CarsEdit::on_pushButton_save_clicked()
{
    qDebug() << "selected: " << ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString str_upd_surface = "UPDATE hm_cars SET name='"+ui->lineEdit->text()+
                              "', speed='"+ui->lineEdit_2->text()+
                              "', fuel_id='"+ QString::number(ui->comboBox->currentIndex())+
    "' WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    qDebug() << str_upd_surface;
    QSqlQuery sqlQuery_upd_surface;
    if (!sqlQuery_upd_surface.exec(str_upd_surface))
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

void CarsEdit::on_tableView_clicked(QModelIndex index)
{
    ui->lineEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
    ui->comboBox->setCurrentIndex(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),4)).toInt());
}
