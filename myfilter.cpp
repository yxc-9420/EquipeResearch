#include "myfilter.h"
#include<qdebug.h>
MyFilter::MyFilter(QObject *parent):QSortFilterProxyModel(parent)
{

}

bool MyFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row,4,source_parent);
    QString ss = sourceModel()->data(index).toString();
    return ss.contains(value);
}
