#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "streetsedit.h"
#include "fueledit.h"
#include "surfaceedit.h"
#include "selectmap.h"
#include "driversedit.h"
#include "carsedit.h"
#include <qmath.h>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QInputDialog>
#include <vector>
#include <set>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const int MAX = 1001;
const int MAXINT = 1000000000;

int n;
vvii G(MAX);
vi D(MAX, MAXINT);
vi P(MAX, MAXINT);

void MainWindow::Dijkstra(int s)
{
    set<ii> Q;
    D[s] = 0;
    Q.insert(ii(0,s));

    while(!Q.empty())
    {
        ii top = *Q.begin();
        Q.erase(Q.begin());
        int v = top.second;
        int d = top.first;

        for (vii::const_iterator it = G[v].begin(); it != G[v].end(); it++)
        {
            int v2 = it->first;
            int cost = it->second;
            if (D[v2] > D[v] + cost)
            {
                if (D[v2] != 1000000000)
                {
                    Q.erase(Q.find(ii(D[v2], v2)));
                }
                D[v2] = D[v] + cost;
                P[v2] = v;
                Q.insert(ii(D[v2], v2));
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox_street->hide();
    gui_state = 0;
    uid = 0;
    uid_edge = 0;
    qDebug() << trUtf8("Справочник ");
    clear_map();
    FillStreets();
}

void MainWindow::clear_map(){
    foreach(HMNode *node, nodes){
        delete node;
    }
    path.clear();
    nodes.clear();
    edges.clear();
    QSqlQuery Query("SELECT MAX(id) from hm_edge;");
    Query.next();
    uid_edge = Query.value(0).toInt()+1;
    QSqlQuery Query1("SELECT MAX(id) from hm_node;");
    Query1.next();
    uid = Query1.value(0).toInt()+1;
}

void MainWindow::fill_map(){
    qDebug() << "fill map" << map_id;
    clear_map();
    QSqlQuery Query("SELECT * FROM hm_node WHERE map_id="+QString::number(map_id)+";");
    while(Query.next()){
        if (Query.value(0).toInt() >= uid)
            uid = Query.value(0).toInt() + 1;
        nodes[Query.value(0).toInt()] = new HMNode(Query.value(1).toInt(), Query.value(2).toInt());
        //qDebug() << Query.value(1) << Query.value(2);
    }
    QSqlQuery Query_e("SELECT * FROM hm_edge WHERE map_id="+QString::number(map_id)+";");
    while(Query_e.next()){
        if (Query_e.value(0).toInt() >= uid_edge)
            uid_edge = Query_e.value(0).toInt() + 1;
        if((nodes[Query_e.value(2).toInt()]!=NULL)&&
           (nodes[Query_e.value(3).toInt()]!=NULL)){
            edges[Query_e.value(0).toInt()] = new HMEdge( nodes[Query_e.value(2).toInt()], nodes[Query_e.value(3).toInt()]);
        } else {
            qDebug() << "ERROR!!!";
            qDebug() << Query_e.value(2) << Query_e.value(3);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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

bool MainWindow::load_map(){

    return true;
}

void MainWindow::optimize(){
    int a = 0, b = 1, w = 10, t;

    path.clear();
    G.clear();
    D.clear();
    P.clear();
    n = 0;
    foreach(HMEdge *edge, edges){
        a = nodes.key(edge->start);
        b = nodes.key(edge->end);
        w = qSqrt( (edge->start->x - edge->end->x)*(edge->start->x - edge->end->x) +
                   (edge->start->y - edge->end->y)*(edge->start->y - edge->end->y) );
        G[a].push_back(ii(b, w));
        G[b].push_back(ii(a, w));
    }
    Dijkstra(from_node);
    if (P[to_node]<1000000){
        t = to_node;
        while(t != from_node){
            qDebug() << t;
            foreach(HMEdge *edge, edges){
                if ( (nodes.key(edge->start) == t) && (nodes.key(edge->end) == P[t]) )
                    path.push_back(edge);
                if ( (nodes.key(edge->start) == P[t]) && (nodes.key(edge->end) == t) )
                    path.push_back(edge);
            }
            t = P[t];
        }
    }
    qDebug() << D[to_node];
    repaint();
    //qDebug() << P[to_node] << P[P[to_node]] << P[P[P[to_node]]] << P[P[P[P[to_node]]]];
    return;
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

void MainWindow::on_comboBox_street_currentIndexChanged(int index)
{
    if ( edges.contains(selected_edge) )
        edges[selected_edge]->street_id = index;
}

void MainWindow::paintEvent (QPaintEvent * event){
        QPainter painter;
        QPen pen;
        QBrush brush;
        double angle;
        int fx,fy,tx,ty;
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
                    fx = node->x+5;
                    fy = node->y+5;
                    tx = node->start[ed]->end->x+5;
                    ty = node->start[ed]->end->y+5;
                    angle = qAtan2(tx-fx, ty-fy);
                    fx += 5.0*qCos(angle);
                    fy += 5.0*qSin(-angle);
                    tx += 5.0*qCos(angle);
                    ty += 5.0*qSin(-angle);
                    //qDebug() << angle;
                    if ((edges.contains(selected_edge)) && (node->start[ed] == edges[selected_edge]))
                        pen.setColor(QColor::fromRgb(0,200,0));
                    else
                        pen.setColor(QColor::fromRgb(50,50,50));
                    painter.setPen(pen);
                    painter.drawLine(fx,fy,tx,ty);
                    painter.drawLine(tx-15.0*qSin(angle-0.3),ty-15.0*qCos(angle-0.3),tx,ty);
                    painter.drawLine(tx-15.0*qSin(angle+0.3),ty-15.0*qCos(angle+0.3),tx,ty);
                }
            }
        }

        foreach(HMEdge *edge, path){
            if(1){
                fx = edge->start->x+5;
                fy = edge->start->y+5;
                tx = edge->end->x+5;
                ty = edge->end->y+5;
                angle = qAtan2(tx-fx, ty-fy);
                fx += 5.0*qCos(angle);
                fy += 5.0*qSin(-angle);
                tx += 5.0*qCos(angle);
                ty += 5.0*qSin(-angle);
                //qDebug() << angle;
                pen.setColor(QColor::fromRgb(0,0,200));
                painter.setPen(pen);
                painter.drawLine(fx,fy,tx,ty);
                painter.drawLine(tx-15.0*qSin(angle-0.3),ty-15.0*qCos(angle-0.3),tx,ty);
                painter.drawLine(tx-15.0*qSin(angle+0.3),ty-15.0*qCos(angle+0.3),tx,ty);
            }
        }


        pen.setColor(QColor::fromRgb(0,0,0));
        pen.setWidth(1);
        painter.setPen(pen);
        foreach(HMNode *node, nodes){
            if(nodes.contains(selected_node) && (nodes[selected_node] == node))
                 brush.setColor(QColor::fromRgb(90,200,90));
            else if(nodes.contains(from_node) && (nodes[from_node] == node))
                brush.setColor(QColor::fromRgb(200,90,90));
            else if(nodes.contains(to_node) && (nodes[to_node] == node))
                brush.setColor(QColor::fromRgb(90,90,200));
            else
                brush.setColor(QColor::fromRgb(90,90,90));
            painter.setBrush(brush);
            painter.drawEllipse(node->x-5,node->y-5,20,20);
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
    //TODO: find nearest edge
    int xma, xmi, yma, ymi, r = 0, angle, res = -1;
    double p, l, ls, le, h, fx, fy, ty, tx, min_h = 15.0;
    foreach(HMEdge *edge, edges){
        xma = 25 +  std::max(edge->start->x, edge->end->x);
        xmi = -15 + std::min(edge->start->x, edge->end->x);
        yma = 25 +  std::max(edge->start->y, edge->end->y);
        ymi = -15 + std::min(edge->start->y, edge->end->y);

        fx = edge->start->x+5;
        fy = edge->start->y+5;
        tx = edge->end->x+5;
        ty = edge->end->y+5;
        angle = qAtan2(tx-fx, ty-fy);
        fx += 5.0*qCos(angle);
        fy += 5.0*qSin(-angle);
        tx += 5.0*qCos(angle);
        ty += 5.0*qSin(-angle);

        if ( (edge->start->x == edge->end->x) && (edge->start->x == edge->end->x) ){
            qDebug() << "WTF?!";
        } else {
            l =  qSqrt( (fx - tx)*(fx - tx) + (fy - ty)*(fy - ty) );
            ls = qSqrt( (fx -  x)*(fx -  x) + (fy -  y)*(fy -  y) );
            le = qSqrt( (tx -  x)*(tx -  x) + (ty -  y)*(ty -  y) );
            p = (l + le + ls)/ 2.0;
            h = qSqrt( p * (p - l) * (p - le) * (p - ls) ) / ( l );
        }
        if ((xmi<x)&&(x<xma)&&(ymi<y)&&(y<yma)&&(h<min_h)){
            qDebug() << "finded edge " << h;
            res = edges.key(edge);
            min_h = h;
        }
    }
    return res;
}

void MainWindow::select_edge(int edge_num){
    selected_node = -1;
    selected_edge = edge_num;
    ui->comboBox_street->setCurrentIndex(edges[edge_num]->street_id);
    ui->groupBox_street->show();
    ui->groupBox_node->hide();
    ui->checkBox->setChecked( edges[edge_num]->policeman );
    ui->lineEdit_velocity->setText( QString::number( edges[edge_num]->max_velocity ) );
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

    path.clear();

    if (gui_state == 20)
        gui_state = 0;

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
    case 21:
        if(event->button() == Qt::LeftButton){
            node_num = findNode(event->x(), event->y());
            if (node_num >= 0){
                from_node = node_num;
                path.clear();
                gui_state = 0;
            }
            repaint();
        }
        break;
    case 22:
        if(event->button() == Qt::LeftButton){
            node_num = findNode(event->x(), event->y());
            if (node_num >= 0){
                to_node = node_num;
                path.clear();
                gui_state = 0;
            }
            repaint();
        }
        break;
    }
}

void MainWindow::add_node(int x, int y){
    if (map_id > 100){
        qDebug() << "map_id not defined";
        close();
        return;
    }
    QString str_add_fuel = "INSERT INTO hm_node (x, y, map_id) "
                           "VALUES ("+QString::number(x)+", "+QString::number(y)+", "+ QString::number(map_id) +");";
    qDebug() << str_add_fuel;
    QSqlQuery sqlQuery_add_fuel;
    if (!sqlQuery_add_fuel.exec(str_add_fuel))
    {
        //QMessageBox::warning(this,trUtf8("Ошибка"),trUtf8("Запись не обновлена"));
    }
    else
    {
        //QMessageBox::information(this,trUtf8("Информация"),trUtf8("Запись добавлена"));
    }
    nodes[uid] = new HMNode(x, y);
}

void MainWindow::update_node(int id){
    QString str_upd_node = "UPDATE hm_node SET x='"+QString::number(nodes[id]->x)+"', y='"+QString::number(nodes[id]->y)+
                           "' WHERE id="+QString::number(id);
    qDebug() << str_upd_node;
    QSqlQuery sqlQuery_upd_node;
    if (sqlQuery_upd_node.exec(str_upd_node)){
        qDebug() << "updated";
    }
}

void MainWindow::del_node(int id){
    qDebug() << "enter";
    for(int i=0; i<4; i++){
        if(nodes[id]->start[i] != NULL){
            qDebug() << "start";
            del_edge(edges.key(nodes[id]->start[i]));
            delete edges[edges.key(nodes[id]->start[i])];
            nodes[id]->start[i] = NULL;
            edges.erase(edges.find(edges.key(nodes[id]->start[i])));
        }
        if(nodes[id]->end[i] != NULL){
            qDebug() << "end";
            del_edge(edges.key(nodes[id]->end[i]));
            delete edges[edges.key(nodes[id]->end[i])];
            edges.erase(edges.find(edges.key(nodes[id]->end[i])));
        }
    }

}

void MainWindow::add_edge(int st, int end){
    if (map_id > 100){
        qDebug() << "map_id not defined";
        close();
        return;
    }
    QString str_add_fuel = "INSERT INTO hm_edge (start_id, end_id, map_id) "
                           "VALUES ("+QString::number(st)+", "+QString::number(end)+", "+ QString::number(map_id) +");";
    qDebug() << str_add_fuel;
    QSqlQuery sqlQuery_add_fuel;
    if (!sqlQuery_add_fuel.exec(str_add_fuel))
    {
        qDebug() << trUtf8("Запись не обновлена");
    }
    else
    {
        qDebug() << trUtf8("Запись добавлена");
    }
    edges[uid_edge] = new HMEdge(nodes[st], nodes[end]);
}

void MainWindow::del_edge(int id){
    QString str_rem_surface = "DELETE FROM hm_edge WHERE id="+QString::number(id);
    qDebug() << "request: " << str_rem_surface;
    QSqlQuery sqlQuery_rem_surface(str_rem_surface);
    qDebug() << "result: " << sqlQuery_rem_surface.exec();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int end = -1;
    switch(gui_state){
    case 0:
        break;
    case 1:
        if (event->button() == Qt::LeftButton){
            update_node(selected_node);
            gui_state = 0;
            repaint();
        }
        break;
    case 2:
        if (event->button() == Qt::LeftButton){
            add_node(event->x()-5, event->y()-5);
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
                if(selected_node != end){
                   add_edge( selected_node, end );
                   uid_edge++;
                   qDebug() << "edge added";
               } else {
                   qDebug() << "from to self";
               }
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
    bool ok;
     QString text = QInputDialog::getText(this, trUtf8("Создание карты"),
                                          trUtf8("Название карты:"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()){
        QString str_add_map = "INSERT INTO hm_maps (name) VALUES ('"+text+"');";
        QSqlQuery sqlQuery_add_map;
        if (sqlQuery_add_map.exec(str_add_map)){
            fill_map();

            QSqlQuery Query1("SELECT last_insert_rowid() FROM hm_maps;");
            Query1.next();
            map_id = Query1.value(0).toInt()-1;
            repaint();
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    if (nodes.contains(selected_node)){
        del_node(selected_node);
        if (nodes[selected_node]->start[0] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->start[0]) ));
        if (nodes[selected_node]->start[1] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->start[1]) ));
        if (nodes[selected_node]->start[2] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->start[2]) ));
        if (nodes[selected_node]->start[3] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->start[3]) ));
        if (nodes[selected_node]->end[0] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->end[0]) ));
        if (nodes[selected_node]->end[1] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->end[1]) ));
        if (nodes[selected_node]->end[2] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->end[2]) ));
        if (nodes[selected_node]->end[3] != NULL) edges.erase(edges.find( edges.key(nodes[selected_node]->end[3]) ));
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

void MainWindow::on_action_2_triggered()
{
    SurfaceEdit sfe;
    sfe.exec();
}

void MainWindow::on_action_open_triggered()
{
    SelectMap sm;
    sm.setup("hm_maps");
    if ( sm.exec() ){
        map_id = sm.id;
        fill_map();
        repaint();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (edges.contains(selected_edge)){
        del_edge(selected_edge);
        delete edges[selected_edge];
        edges.erase(edges.find(selected_edge));
        repaint();
    }
}

void MainWindow::on_checkBox_clicked()
{

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if ( edges.contains(selected_edge) )
        edges[selected_edge]->policeman = checked;
}

void MainWindow::on_lineEdit_velocity_returnPressed()
{
    if ( edges.contains(selected_edge) )
        edges[selected_edge]->max_velocity = ui->lineEdit_velocity->text().toInt();
}

void MainWindow::on_action_5_triggered()
{
    close();
}

void MainWindow::on_action_8_triggered()
{
    gui_state = 20;
    optimize();
    QMessageBox::information(NULL,QObject::trUtf8("t"),QString::number(D[to_node]));
}

void MainWindow::on_action_9_triggered()
{
    gui_state = 21;
}

void MainWindow::on_action_10_triggered()
{
    gui_state = 22;
}

void MainWindow::on_actionOpen_triggered()
{
}

void MainWindow::on_action_12_triggered()
{
    SelectMap sm;
    sm.setup("hm_drivers");
    if ( sm.exec() ){
        drv_id = sm.id;
        fill_map();
        repaint();
    }
}

void MainWindow::on_action_13_triggered()
{
    SelectMap sm;
    sm.setup("hm_cars");
    if ( sm.exec() ){
        car_id = sm.id;
        fill_map();
        repaint();
    }
}

void MainWindow::on_action_4_triggered()
{
    driversedit drve;
    drve.exec();
}

void MainWindow::on_action_3_triggered()
{
    CarsEdit carse;
    carse.exec();
}
