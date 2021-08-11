#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
: QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return 1;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::ItemDataRole::DisplayRole)
        return QVariant();
    if(orientation == Qt::Orientation::Horizontal){
        switch (section) {
        case 0:
            return tr("编号");
            break;
        case 1:
            return tr("名称");
            break;
        case 2:
            return tr("效果");
            break;
        case 3:
            return tr("合成");
            break;
        default:
            return QVariant();
        }
    }
    return QVariant();
}
