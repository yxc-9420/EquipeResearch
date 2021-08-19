#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QTabWidget>
#include <QMainWindow>
#include"tablemodel.h"
#include<QStandardItemModel>
#include"myfilter.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenu();
    void setupTabs();
    void LoadData();
    void flush();

    QMenu *editMenu;
    QAction *flushAct;
    QAction *exitAct;

    QTabWidget* thingsWidget;
    TableModel* table;
    QSortFilterProxyModel *proxymodel;
};
#endif // MAINWINDOW_H
