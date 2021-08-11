#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include<QAbstractItemModel>
#include<string>
#include<vector>
using namespace std;
struct things
{
    string name;
    string describe;
    struct shuxing{
        string strength;
        string agi;
        string interligence;
        vector<string> specilal;
    };
    vector<things*> hecheng;
};

class TableModel:public QAbstractTableModel
{
public:
    TableModel(QObject *parent = 0);
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // TABLEMODEL_H
