#include "tablemodel.h"
#include<map>
#include<qdebug.h>
TableModel::TableModel(QObject *parent)
: QAbstractTableModel(parent)
{

}

TableModel::TableModel(QList<things> things_list, QObject *parent)
    : QAbstractTableModel(parent)
    , things_list(things_list)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return things_list.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= things_list.size() || index.row() < 0)
        return QVariant();
    if(role == Qt::TextAlignmentRole){
        return int(Qt::AlignCenter);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const things &t = things_list.at(index.row());
        if (index.column() == 0)
            return t.id;
        else if (index.column() == 1)
            return t.name;
        else if (index.column() == 2)
            return t.get_shuxing();
        else if (index.column() == 3)
            return t.get_hecheng();
        else if (index.column() == 4)
            return t.type;

    }
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
        case 1:
            return tr("名称");
        case 2:
            return tr("属性");
        case 3:
            return tr("合成");
        case 4:
            return tr("类型");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QList<things> TableModel::getThings()
{
    return things_list;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid()&& role == Qt::ItemDataRole::EditRole){
        int row = index.row();
        auto current = things_list.value(index.row());
        if (index.column() == 0)
            current.id = value.toInt();
        else if (index.column() == 1)
            current.name = value.toString();
        else if (index.column() == 2){
            if(value.canConvert<things::shuxing>()){
                current.effect = value.value<things::shuxing>();
            }
        }
        else if (index.column() == 3){
            if(value.canConvert<map<QString,qint32>>()){
                current.hecheng = value.value<map<QString,qint32>>();
            }
        }
        else if (index.column() == 4){
            current.type = value.toInt();
        }
        else
            return false;
        things_list.replace(row, current);
        return true;
    }
    return false;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int row = 0; row < count; ++row)
        things_list.insert(row, things());

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int row = 0; row < count; ++row)
        things_list.removeAt(row);

    endRemoveRows();
    return true;
}
//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
//! [7]


