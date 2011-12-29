#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include "mapobject.h"
#include "edge.h"
#include "node.h"
#include "map.h"
#include <QMouseEvent>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int selected_node;
    int selected_edge;

protected:
    void changeEvent(QEvent *e);
    void paintEvent ( QPaintEvent * event );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    int findNode(int x, int y);

private:
    Ui::MainWindow *ui;
    QHash<int, HMNode *> nodes;
    QHash<int, HMEdge *> edges;
    int gui_state;
    int uid;
    int uid_edge;
    void FillStreets();

private slots:
    void on_pushButton_clicked();
    void on_action_7_triggered();
    void on_action_triggered();
    void on_comboBox_street_currentIndexChanged(int index);
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
