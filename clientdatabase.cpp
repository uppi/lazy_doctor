#include <QtSql>
#include "clientdatabase.h"

Lz::ClientDatabase::ClientDatabase(QObject *parent) :
    QObject(parent)
{
}

bool Lz::ClientDatabase::init(QString dbName)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbName);
    if (!m_database.open()) {
        qDebug() << "Can'topen database";
        return false;
    }
    return true;
}

bool Lz::ClientDatabase::populate()
{
    QSqlQuery a_query(m_database);
    QString str = "CREATE TABLE clients ("
            "number integer PRIMARY KEY NOT NULL, "
            "address VARCHAR(255), "
            "age integer"
            ");";
    bool b = a_query.exec(str);
    if (!b)
    {
        qDebug() << "Can't create table clients";
        return false;
    }

    QString str_insert = "INSERT INTO clients(number, address, age) "
            "VALUES (%1, '%2', %3);";
    str = str_insert.arg("14")
            .arg("hello world str.")
            .arg("37");
    str = str_insert.arg("10")
            .arg("Affff str.")
            .arg("63");
    b = a_query.exec(str);
    if (!b) {
        qDebug() << "Can't insert data";
        return false;
    }
    return true;
}

QSqlDatabase& Lz::ClientDatabase::database()
{
    return m_database;
}
