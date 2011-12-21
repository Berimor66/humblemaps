#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << trUtf8("0_o");
    QSqlQuery Query("SELECT name FROM hm_streets;");
    while(Query.next()){
        qDebug() << trUtf8("улица = ")+Query.value(0).toString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    MapObject *a = new MapObject("test");
    map[1] = a;
}

void MainWindow::on_comboBox_street_currentIndexChanged(int index)
{

}
