#include "dbconn.h"
DbConn::DbConn()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      _Mysql = QSqlDatabase::database("qt_sql_default_connection");
    else
      _Mysql = QSqlDatabase::addDatabase("QMYSQL");
    _Mysql.setHostName(_Hostname);
    _Mysql.setPort(_Port);
    _Mysql.setDatabaseName(_DatabaseName);
    _Mysql.setUserName(_Username);
    _Mysql.setPassword(_Password);
}

bool DbConn::open()
{
    return _Mysql.open();
}

void DbConn::close()
{
    if(_Mysql.isOpen())
    _Mysql.close();
}

QSqlQuery DbConn::exec(const QString &query)
{
    return _Mysql.exec(query);
}
