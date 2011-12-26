#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << trUtf8("0_o");
    QSqlQuery Query("SELECT name FROM hm_streets;");
    while(Query.next()){
        qDebug() << trUtf8("улица = ")+Query.value(0).toString();
    }
    nodes_count = 0;
    for(int i=0;i<0;i++){
        nodes[nodes_count] = new HMNode();
        nodes[nodes_count]->x = (rand()%500+500)%500;
        nodes[nodes_count]->y = (rand()%500+500)%500;
        nodes[nodes_count]->start[0] = NULL;
        nodes[nodes_count]->start[1] = NULL;
        nodes[nodes_count]->start[2] = NULL;
        nodes[nodes_count]->start[3] = NULL;
        nodes_count++;
    }
    //nodes[0]->start[0] = new HMEdge();
    //nodes[0]->start[0]->end = nodes[2];
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
    MapObject *a = new MapObject("test");
    map[1] = a;
}

void MainWindow::on_comboBox_street_currentIndexChanged(int index)
{

}

void MainWindow::paintEvent (QPaintEvent * event){
        QPainter painter;
        QPen pen;
        QBrush brush;
        HMNode *node;

        pen.setColor(QColor::fromRgb(0,0,0));
        pen.setWidth(1);
        pen.setJoinStyle(Qt::MiterJoin);

        brush.setColor(QColor::fromRgb(90,90,90));
        brush.setStyle(Qt::SolidPattern);

        painter.begin(this);
        painter.setPen(pen);
        painter.setBrush(brush);

        for(int i = 0;i<nodes_count;i++){
            node = nodes[i];
            for(int ed = 0; ed<4; ed++){
                if((node->start[ed] != NULL)&&(node->start[ed]->end != NULL)){
                    painter.drawLine(node->x+5,node->y+5,node->start[ed]->end->x+5,node->start[ed]->end->y+5);
                }
            }
        }
        for(int i = 0;i<nodes_count;i++){
            node = nodes[i];
            painter.drawEllipse(node->x,node->y,10,10);
        }
        painter.end();
}

int MainWindow::findNode(int x, int y){
    for(int i = 0; i< nodes_count;i++){
        if (( abs(x-nodes[i]->x)<20 ) && ( abs(y-nodes[i]->y)<20 )){
            return i;
        }
    }
    return -1;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
 {
     if (event->button() == Qt::LeftButton) {
         selected = findNode(event->x(), event->y());
         if(selected<0){
             nodes[nodes_count] = new HMNode();
             nodes[nodes_count]->x = event->x()-5;
             nodes[nodes_count]->y = event->y()-5;
             nodes[nodes_count]->start[0] = NULL;
             nodes[nodes_count]->start[1] = NULL;
             nodes[nodes_count]->start[2] = NULL;
             nodes[nodes_count]->start[3] = NULL;
             nodes_count++;
             this->repaint();
         }
     } else if ((event->button() == Qt::RightButton)) {
         selected = findNode(event->x(), event->y());
         qDebug() << selected;
         this->repaint();
     } else {
         // передаём кнопки базовому классу
         QWidget::mousePressEvent(event);
     }
 }

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
 {
    int i = 0, fnd;
    if ((event->button() == Qt::LeftButton)) {
        if(selected>=0){
            nodes[selected]->x=event->x();
            nodes[selected]->y=event->y();
            this->repaint();
        }
    }else if ((event->button() == Qt::RightButton)) {
         fnd = findNode(event->x(), event->y());
         qDebug() << fnd;
         if((fnd>=0)&&(selected>=0)){
             while(nodes[selected]->start[i] != NULL) i++;
             nodes[selected]->start[i] = new HMEdge();
             nodes[selected]->start[i]->end = nodes[fnd];
         }
         selected = -1;

         this->repaint();
     } else {
         // передаём кнопки базовому классу
         QWidget::mousePressEvent(event);
     }
 }
