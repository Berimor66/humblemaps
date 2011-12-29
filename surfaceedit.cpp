#include "surfaceedit.h"
#include "ui_surfaceedit.h"

SurfaceEdit::SurfaceEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SurfaceEdit)
{
    ui->setupUi(this);
    FillTable();
}

SurfaceEdit::~SurfaceEdit()
{
    delete ui;
}

void SurfaceEdit::FillTable()
{
    QString str_oper = "SELECT * FROM hm_surface";
    QSqlQueryModel * model_Oper = new QSqlQueryModel(0);
    model_Oper->setQuery(str_oper);
    model_Oper->setHeaderData(1, Qt::Horizontal, QObject::trUtf8("Название поверхности"));
    model_Oper->setHeaderData(2, Qt::Horizontal, QObject::trUtf8("Максимальная скорость"));
    ui->tableView->setModel(model_Oper);
    ui->tableView->hideColumn(0);
}

void SurfaceEdit::on_pushButton_del_clicked()
{
    if (ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString()=="")
    {
        QMessageBox::information(this,trUtf8("Предупреждение"),trUtf8("Выберите элемент"));
    }
    else
    {
        if (QMessageBox::warning(this,trUtf8("Предупреждение"),trUtf8("Вы уверенны что хотите удалить элемент?"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
        {
            QString str_rem_surface = "DELETE FROM hm_surface WHERE id="+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
            qDebug() << "request: " << str_rem_surface;
            QSqlQuery sqlQuery_rem_surface(str_rem_surface);
            qDebug() << "result: " << sqlQuery_rem_surface.exec();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
    FillTable();
}

void SurfaceEdit::on_pushButton_save_clicked()
{
    qDebug() << "selected: " << ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();
    QString str_upd_surface = "UPDATE hm_surface SET name='"+ui->lineEdit->text()+"', coef='"+ui->lineEdit_2->text()+
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

void SurfaceEdit::on_pushButton_add_clicked()
{
    if (ui->lineEdit->text()=="")
    {
        QMessageBox::information(this,trUtf8("Информация"),trUtf8("Заполните название"));
    }
    else
    {
        QString str_add_surface = "INSERT INTO hm_surface (name, coef)"
                                "VALUES ('"+ui->lineEdit->text()+"', "+ui->lineEdit_2->text()+");";

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

void SurfaceEdit::on_tableView_clicked(QModelIndex index)
{
    ui->lineEdit->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString());
    ui->lineEdit_2->setText(ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString());
}
