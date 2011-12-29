#include "streetsedit.h"
#include "ui_streetsedit.h"

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
