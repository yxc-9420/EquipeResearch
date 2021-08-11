#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QTabWidget>
#include <QMainWindow>
#include"tablemodel.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenu();
    void setupTabs();

    QTabWidget* thingsWidget;
    TableModel* table;
};
#endif // MAINWINDOW_H
