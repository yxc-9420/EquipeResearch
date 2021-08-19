#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include<QAbstractItemModel>
#include<string>
#include<vector>
#include<map>
using namespace std;
struct things
{
    things() = default;
    things(qint32 id):id(id){}

    QString get_shuxing() const{
        return (effect.strength != 0?
                    QString("力量:%1\n").arg(effect.strength):QString())
                .append(effect.agi != 0?QString("敏捷:%1\n").arg(effect.agi):"")
                .append(effect.interligence != 0?QString("智力:%1").arg(effect.interligence):"")
                ;
    }
    QString get_hecheng() const{
        QString res;
        if(hecheng.empty()) return res;
        for(auto &thing:hecheng){
            res.append(res.size()>0?" + ":"");
            res.append(thing.second>0?thing.first:"");
            res.append(thing.second>1?" * ":"");
        }
        return res;
    }

    qint32 id;
    QString name;
    QString describe;
    struct shuxing{
        qint32 strength;
        qint32 agi;
        qint32 interligence;
        QString specilal;
    } effect;
    map<QString,qint32> hecheng;
    qint32 type;
    bool operator==(const things &thing){
        return this->id == thing.id;
    }
};

Q_DECLARE_METATYPE(things)
Q_DECLARE_METATYPE(things::shuxing)

class TableModel:public QAbstractTableModel
{
public:
    TableModel(QObject *parent = 0);
    TableModel(QList<things> things_list, QObject *parent = 0);
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QList<things> getThings();
private:
    QList<things> things_list;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // TABLEMODEL_H
