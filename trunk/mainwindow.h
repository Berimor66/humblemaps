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
    int findEdge(int x, int y);
    void select_edge(int edge_num);
    void select_node(int node_num);
    void fill_map();
    void clear_map();
    bool load_map();
    void add_node(int x, int y);
    void update_node(int id);
    void del_node(int id);
    void add_edge(int st, int end);
    void update_edge(int id);
    void del_edge(int id);

private:
    Ui::MainWindow *ui;
    QHash<int, HMNode *> nodes;
    QHash<int, HMEdge *> edges;
    int gui_state;
    int uid;
    int uid_edge;
    void FillStreets();
    int map_id;

private slots:
    void on_action_5_triggered();
    void on_lineEdit_velocity_returnPressed();
    void on_checkBox_clicked(bool checked);
    void on_checkBox_clicked();
    void on_pushButton_2_clicked();
    void on_action_open_triggered();
    void on_action_2_triggered();
    void on_action_6_triggered();
    void on_pushButton_clicked();
    void on_action_7_triggered();
    void on_action_triggered();
    void on_comboBox_street_currentIndexChanged(int index);
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
