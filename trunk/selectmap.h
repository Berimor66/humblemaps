#ifndef SELECTMAP_H
#define SELECTMAP_H

#include <QDialog>

namespace Ui {
    class SelectMap;
}

class SelectMap : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMap(QWidget *parent = 0);
    ~SelectMap();
    int map_id;

private:
    Ui::SelectMap *ui;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // SELECTMAP_H
