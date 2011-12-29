#include "selectmap.h"
#include "ui_selectmap.h"

SelectMap::SelectMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMap)
{
    ui->setupUi(this);
}

SelectMap::~SelectMap()
{
    delete ui;
}

void SelectMap::on_buttonBox_accepted()
{
    accept();
}

void SelectMap::on_buttonBox_rejected()
{
    reject();
}
