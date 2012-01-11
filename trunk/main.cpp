#include <QtGui/QApplication>
#include <QMessageBox>
#include "main.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    if (!db.isValid()){
        qDebug() << QObject::trUtf8("Ошибка загрйзки драйвера БД");
        QMessageBox::critical(NULL,QObject::trUtf8("Ошибка"),QObject::trUtf8("Ошибка загрузки драйвера базы данных!"));
        exit(100);
    }
    db.setDatabaseName("db\\db.db");
    if (!db.open()){
        qDebug() << QObject::trUtf8("Ошибка подключения к БД");
        QMessageBox::critical(NULL,QObject::trUtf8("Ошибка"),QObject::trUtf8("Ошибка подключения к базе данных!"));
        exit(100);
    }
    else {
        qDebug() << QObject::trUtf8("Драйвер загружен и подключение установлено.");
    }
    MainWindow w;
    w.show();
    return a.exec();
}
