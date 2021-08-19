#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTableView>
#include<QSortFilterProxyModel>
#include<QHeaderView>
#include<QSqlQueryModel>
#include<dbconn.h>
#include<QSqlQuery>
#include<QSqlTableModel>
#include <QMenuBar>
#include<QtDebug>
MainWindow::MainWindow(QWidget *parent)
{
    table = new TableModel(this);
    thingsWidget = new QTabWidget;
    thingsWidget->setTabPosition(QTabWidget::TabPosition::South);
    setCentralWidget(thingsWidget);
    //加载数据
    LoadData();
    //添加表格,绑定数据并筛选
    setupTabs();
    createMenu();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenu()
{
    editMenu = menuBar()->addMenu(tr("编辑"));

//    flushAct = new QAction(tr("刷新"),this);
//    editMenu->addAction(flushAct);
//    connect(flushAct,&QAction::triggered,this,&MainWindow::flush);

    editMenu->addSeparator();

    exitAct = new QAction(tr("关闭"),this);
    editMenu->addAction(exitAct);
    connect(exitAct,&QAction::triggered,this,&QWidget::close);
}

void MainWindow::setupTabs()
{
    QMap<QString,QString> thing_type_map;
    //通过数据库字典获取子表格

    DbConn conn;
    bool flag = conn.open();
    if(flag){
        QSqlQuery query = conn.exec(QString("select * from things_type_dict"));
        while(query.next()){
            thing_type_map.insert(query.value(0).toString(),query.value(1).toString());
        }
    }
    conn.close();
    for(auto s = thing_type_map.cbegin();s!=thing_type_map.end();s++){
        QString str = s.value();
        QTableView *tableView = new QTableView;

        proxymodel = new QSortFilterProxyModel;
        proxymodel->setSourceModel(table);
        proxymodel->setFilterRegExp(QRegExp(s.key()));
        proxymodel->setFilterKeyColumn(4);
        proxymodel->sort(0,Qt::SortOrder::AscendingOrder);
        tableView->setModel(proxymodel);

        //tableView->sortByColumn(0,Qt::SortOrder::AscendingOrder);
        tableView->resizeRowsToContents();

        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableView->setColumnHidden(4,true);
        //tableView->setColumnHidden(0,true);

        thingsWidget->addTab(tableView,str);
    }
}


void write_to_table(things& thing,TableModel* &table);

void MainWindow::LoadData()
{
    DbConn conn;
    if(conn.open()){
        QString sql("select things.*, shuxing.strength");
        sql.append(", shuxing.agi, shuxing.inteligence");
        sql.append(",h.name as child_name,h.quantity,h.child_id");
        sql.append(" from things left join shuxing on things.id = shuxing.id");
        sql.append(" left join");
        sql.append(" (select hecheng.id,things.name,hecheng.quantity,hecheng.child_id from hecheng");
        sql.append(" left join things on hecheng.child_id = things.id) h");
        sql.append(" on things.id = h.id order by things.id asc,h.child_id asc");
        QSqlQuery query = conn.exec(sql);
        things last(0);

        while(query.next()){
            things cur;
            cur.id = query.value(0).toInt();
            cur.name = query.value(1).toString();
            cur.describe = query.value(2).toString();
            cur.type = query.value(3).toInt();
            cur.effect.strength = query.value("strength").toInt();
            cur.effect.agi = query.value("agi").toInt();
            cur.effect.interligence = query.value("inteligence").toInt();
            QString child_name = query.value("child_name").toString();
            if(child_name.size()>0){
                cur.hecheng.insert({query.value("child_name").toString(),query.value("quantity").toInt()});
            }
            if(last == cur) {
                last.hecheng.insert(cur.hecheng.begin(),cur.hecheng.end());
            }
            else if(last.id>0){
                write_to_table(last,table);
                last = cur;
            }
            else{
                last = cur;
            }
        }
        if(last.id>0){
            write_to_table(last,table);
        }
        conn.close();
    }
}

void write_to_table(things& thing,TableModel* &table){
    //将上一个物品存入
    table->insertRows(0,1,QModelIndex());
    //编号
    QModelIndex index = table->index(0,0,QModelIndex());
    table->setData(index,thing.id,Qt::ItemDataRole::EditRole);
    //名称
    index = table->index(0,1,QModelIndex());
    table->setData(index,thing.name,Qt::ItemDataRole::EditRole);
    //效果
    index = table->index(0,2,QModelIndex());
    table->setData(index,QVariant::fromValue(things::shuxing(thing.effect)),Qt::ItemDataRole::EditRole);
    //合成
    index = table->index(0,3,QModelIndex());
    table->setData(index,QVariant::fromValue(thing.hecheng),Qt::ItemDataRole::EditRole);
    //类型 隐藏 此列用于筛选
    index = table->index(0,4,QModelIndex());
    table->setData(index,thing.type,Qt::ItemDataRole::EditRole);
}
