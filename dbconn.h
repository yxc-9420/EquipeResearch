#ifndef DBCONN_H
#define DBCONN_H
#include<qstring.h>
#include<QSqlDatabase>
#include<memory>
#include<QSqlQuery>

using namespace std;
const QString cg_Hostname = "127.0.0.1";
const int cg_Port = 3306;
const QString cg_DatabaseName = "equipe_research";
const QString cg_Username = "root";
const QString cg_Password = "mysql";

class DbConn
{
public:
    DbConn();
    bool open();
    void close();
    QSqlQuery exec(const QString &query= QString());
private:
    QString _Hostname = cg_Hostname;
    int _Port = cg_Port;
    QString _DatabaseName = cg_DatabaseName;
    QString _Username = cg_Username;
    QString _Password = cg_Password;
    QSqlDatabase _Mysql;
};

#endif // DBCONN_H
