#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlDatabase>
#include<QTableView>
#include<QSortFilterProxyModel>
MainWindow::MainWindow(QWidget *parent)
{
    table = new TableModel();
    thingsWidget = new QTabWidget;
    thingsWidget->setTabPosition(QTabWidget::TabPosition::South);
    setCentralWidget(thingsWidget);
    setupTabs();
    //初始化表格
//    qDebug()<<"available drivers:";
//        QStringList drivers = QSqlDatabase::drivers();
//        foreach(QString driver, drivers)
//            qDebug()<<driver;
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("127.0.0.1");
//    db.setPort(3306);
//    db.setDatabaseName("equipe_research");
//    db.setUserName("root");
//    db.setPassword("mysql");
//    bool flag = db.open();

//    if(flag) QMessageBox::information(this,"提示","连接成功");
//    else QMessageBox::information(this,"提示","连接失败");
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupTabs()
{
    //通过数据库字典获取子表格
    QList<QString> groups{"武器","材料"};
    for(int i =0,length = groups.size();i<length;i++){
        QString str = groups[i];

        QTableView *tableView = new QTableView;
        tableView->setModel(table);

        thingsWidget->addTab(tableView,str);
    }
}

