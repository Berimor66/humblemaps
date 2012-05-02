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
    id = ui->comboBox->currentIndex();
    accept();
}

void SelectMap::on_buttonBox_rejected()
{
    reject();
}

void SelectMap::setup(QString table){
    if(table == "hm_maps"){
        setWindowTitle(trUtf8("Выбрать карту"));
    } else if("hm_cars") {
        setWindowTitle(trUtf8("Выбрвть водителя"));
    } else if("hm_drivers") {
        setWindowTitle(trUtf8("Выбрвть автомобиль"));
    } else {
        setWindowTitle("#ОШИБКА#");
    }
    QSqlRelationalTableModel *comboModel = new QSqlRelationalTableModel(0);
    comboModel->setTable(table);
    int comboIndex = comboModel->fieldIndex("id");
    comboModel->setRelation(comboIndex, QSqlRelation(table, "id", "name"));
    comboModel->select();
    QSqlTableModel *comboRelModel = comboModel->relationModel(comboIndex);
    ui->comboBox->setModel(comboRelModel);
    ui->comboBox->setModelColumn(comboRelModel->fieldIndex("name"));
}
