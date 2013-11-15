#include <QtSql>
#include "clientstorage.h"

Lz::ClientStorage::ClientStorage(QObject *parent) :
    QObject(parent)
{
}

bool Lz::ClientStorage::init(QString dbName)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbName);
    if (!m_database.open()) {
        qDebug() << "Can't open database";
        return false;
    }
    QSqlQuery query(m_database);
    QString str = "CREATE TABLE clients ("
            "ФИО VARCHAR(255) "
            ");";
    if(!query.exec(str)) qDebug() << "cann't create :(";
    return true;
}

bool Lz::ClientStorage::add(const QJsonObject& client)
{
    QSqlQuery query(m_database);
    QString keys, values;
    for(auto key : client.keys())
    {
        auto val = client.value(key).toString();
        keys = QString("%1%2, ").arg(keys).arg(key);
        values = QString("%1'%2', ").arg(values).arg(val);
    }
    if(keys.isEmpty())
    {
        return false;
    }
    else
    {
        keys = keys.mid(0, keys.size() - 2);
        values = values.mid(0, values.size() - 2);
    }
    QString request = QString("INSERT INTO clients(%1) VALUES (%2);").arg(keys).arg(values);
    qDebug() << "so we are trying to perform the next request " << request;
    auto result = query.exec(request);
    if (!result) {
        qDebug() << "Can't insert data";
        return false;
    }
    return true;
}

bool Lz::ClientStorage::change(quint64 id, const QJsonObject& client)
{
    Q_UNUSED(id);
    Q_UNUSED(client)
}

QSqlDatabase& Lz::ClientStorage::database()
{
    return m_database;
}
