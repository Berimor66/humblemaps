#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streetsedit.h"
#include "fueledit.h"
#include <qmath.h>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gui_state = 0;
    uid = 0;
    uid_edge = 0;
    qDebug() << trUtf8("Справочник ");

    FillStreets();
}

void MainWindow::FillStreets(){
    QSqlRelationalTableModel *comboModel = new QSqlRelationalTableModel(0);
    comboModel->setTable("hm_streets");
    int comboIndex = comboModel->fieldIndex("id");
    comboModel->setRelation(comboIndex, QSqlRelation("hm_streets", "id", "name"));
    comboModel->select();
    QSqlTableModel *comboRelModel = comboModel->relationModel(comboIndex);
    ui->comboBox_street->setModel(comboRelModel);
    ui->comboBox_street->setModelColumn(comboRelModel->fieldIndex("name"));
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

}

void MainWindow::on_comboBox_street_currentIndexChanged(int index)
{
    if ( edges.contains(selected_edge) )
        edges[selected_edge]->street_id = index;
}

void MainWindow::paintEvent (QPaintEvent * event){
        QPainter painter;
        QPen pen;
        QBrush brush;
        //HMNode *node;

        pen.setColor(QColor::fromRgb(0,0,0));
        pen.setWidth(2);
        pen.setJoinStyle(Qt::MiterJoin);

        brush.setColor(QColor::fromRgb(90,90,90));
        brush.setStyle(Qt::SolidPattern);

        painter.begin(this);
        painter.setPen(pen);
        painter.setBrush(brush);

        foreach(HMNode *node, nodes){
            for(int ed = 0; ed<4; ed++){
                if((node->start[ed] != NULL)&&(node->start[ed]->end != NULL)){
                    if ((edges.contains(selected_edge)) && (node->start[ed] == edges[selected_edge]))
                        pen.setColor(QColor::fromRgb(0,200,0));
                    else
                        pen.setColor(QColor::fromRgb(0,0,0));
                    painter.setPen(pen);
                    painter.drawLine(node->x+5,node->y+5,node->start[ed]->end->x+5,node->start[ed]->end->y+5);
                }
            }
        }

        pen.setColor(QColor::fromRgb(0,0,0));
        pen.setWidth(1);
        painter.setPen(pen);
        foreach(HMNode *node, nodes){
            if(nodes.contains(selected_node) && (nodes[selected_node] == node))
                 brush.setColor(QColor::fromRgb(200,90,90));
            else
                 brush.setColor(QColor::fromRgb(90,90,90));
            painter.setBrush(brush);
            painter.drawEllipse(node->x,node->y,10,10);
        }
        painter.end();
}

int MainWindow::findNode(int x, int y){
    foreach(HMNode *node, nodes){
        if (( abs(node->x - x)<20 ) && ( abs(node->y - y)<20 )){
            qDebug() << "finded node";
            return nodes.key(node);
        }
    }
    return -1;
}

int MainWindow::findEdge(int x, int y){
    int xma, xmi, yma, ymi, r = 0;
    double p, l, ls, le, h;
    foreach(HMEdge *edge, edges){
        xma = 25 +  std::max(edge->start->x, edge->end->x);
        xmi = -15 + std::min(edge->start->x, edge->end->x);
        yma = 25 +  std::max(edge->start->y, edge->end->y);
        ymi = -15 + std::min(edge->start->y, edge->end->y);
        if ( (edge->start->x == edge->end->x) && (edge->start->x == edge->end->x) ){
            qDebug() << "WTF?!";
        } else {
            l = qSqrt( (edge->start->x - edge->end->x)*(edge->start->x - edge->end->x) + (edge->start->y - edge->end->y)*(edge->start->y - edge->end->y) );
            ls = qSqrt( (edge->start->x - x)*(edge->start->x - x) + (edge->start->y - y)*(edge->start->y - y) );
            le = qSqrt( (edge->end->x - x)*(edge->end->x - x) + (edge->end->y - y)*(edge->end->y - y) );
            qDebug() << l;
            qDebug() << ls;
            qDebug() << le;
            p = (l + le + ls)/2.0;
            h = qSqrt( p * (p - l) * (p - le) * (p - ls) ) / ( l );
            qDebug() << h;
        }
        if ((xmi<x)&&(x<xma)&&(ymi<y)&&(y<yma)&&(h<15)){
            qDebug() << "finded edge";
            return edges.key(edge);
        }
    }
    return -1;
}

void MainWindow::select_edge(int edge_num){
    selected_node = -1;
    selected_edge = edge_num;
    ui->comboBox_street->setCurrentIndex(edges[edge_num]->street_id);
    ui->groupBox_street->show();
    ui->groupBox_node->hide();
}

void MainWindow::select_node(int node_num){
    selected_edge = -1;
    selected_node = node_num;
    ui->groupBox_street->hide();
    ui->groupBox_node->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int node_num, edge_num;
    switch(gui_state){
    case 0:
        if(event->button() == Qt::LeftButton){
            node_num = findNode(event->x(), event->y());
            edge_num = findEdge(event->x(), event->y());
            if (node_num >= 0){
                select_node(node_num);
                gui_state = 1;
            } else if (edge_num >= 0) {
                select_edge(edge_num);
                gui_state = 5;
            } else {
                gui_state = 2;
            }
            repaint();
        }
        if(event->button() == Qt::RightButton){
            node_num = findNode(event->x(), event->y());
            if (node_num >= 0){
                select_node(node_num);
                gui_state = 3;
            }
            repaint();
        }
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int end = -1;
    switch(gui_state){
    case 0:
        break;
    case 1:
        if (event->button() == Qt::LeftButton){
            gui_state = 0;
            repaint();
        }
        break;
    case 2:
        if (event->button() == Qt::LeftButton){
            nodes[uid] = new HMNode(event->x()-5, event->y()-5);
             select_node(uid);
            uid++;
            gui_state = 0;
            qDebug() << "added node";
            repaint();
        }
        break;
    case 3:
        if (event->button() == Qt::RightButton){
            end = findNode(event->x(), event->y());
            if(end>=0){
                edges[uid_edge] = new HMEdge(nodes[selected_node], nodes[end]);
                uid_edge++;
            }
            gui_state = 0;
            repaint();
        }
        break;
    case 4:
        break;
    case 5:
        gui_state = 0;
        break;
    }
 }

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    switch(gui_state){
    case 0:
        break;
    case 1:
        if (event->buttons() & Qt::LeftButton){
            nodes[selected_node]->x = event->x()-5;
            nodes[selected_node]->y = event->y()-5;
            repaint();
        }
        break;
    }
}

void MainWindow::on_action_triggered()
{
    StreetsEdit se;
    se.exec();
    FillStreets();
}

void MainWindow::on_action_7_triggered()
{
    foreach(HMNode *node, nodes){
        delete node;
    }
    nodes.clear();
    edges.clear();
    repaint();
}

void MainWindow::on_pushButton_clicked()
{
    if (nodes.contains(selected_node)){
        delete nodes[selected_node];
        nodes.erase(nodes.find(selected_node));
    }
    repaint();
}

void MainWindow::on_action_6_triggered()
{
    FuelEdit fe;
    fe.exec();
}
