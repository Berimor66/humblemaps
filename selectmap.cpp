#include "selectmap.h"
#include "ui_selectmap.h"

SelectMap::SelectMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMap)
{
    ui->setupUi(this);
    QSqlRelationalTableModel *comboModel = new QSqlRelationalTableModel(0);
    comboModel->setTable("hm_maps");
    int comboIndex = comboModel->fieldIndex("id");
    comboModel->setRelation(comboIndex, QSqlRelation("hm_maps", "id", "name"));
    comboModel->select();
    QSqlTableModel *comboRelModel = comboModel->relationModel(comboIndex);
    ui->comboBox->setModel(comboRelModel);
    ui->comboBox->setModelColumn(comboRelModel->fieldIndex("name"));
}

SelectMap::~SelectMap()
{
    delete ui;
}

void SelectMap::on_buttonBox_accepted()
{
    map_id = ui->comboBox->currentIndex();
    accept();
}

void SelectMap::on_buttonBox_rejected()
{
    reject();
}
