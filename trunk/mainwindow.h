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
    HMNode *nodes[1000];
    int nodes_count;
    int selected;
    HMEdge *edges[1000];
    int edges_count;
    int findNode(int x, int y);

protected:
    void changeEvent(QEvent *e);
    void paintEvent ( QPaintEvent * event );
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
    QHash<int, MapObject *> map;

private slots:
    void on_comboBox_street_currentIndexChanged(int index);
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
