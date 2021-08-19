#ifndef MYFILTER_H
#define MYFILTER_H

#include<QSortFilterProxyModel>
class MyFilter:public QSortFilterProxyModel
{
public:
    MyFilter(QObject *parent = 0);
    QString value;
    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // MYFILTER_H
