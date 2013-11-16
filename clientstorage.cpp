#include <QtSql>
#include <QDebug>
#include "clientstorage.h"

Lz::ClientStorage::ClientStorage(QObject *parent) :
    QObject(parent)
{
}

bool Lz::ClientStorage::init(const QString& dbName, QStringList fields)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(dbName);
    if (!m_database.open()) {
        qDebug() << "Can't open database";
        return false;
    }
    QSqlQuery query(m_database);
    fields.append("");
    QString fieldsString = fields.join(" VARCHAR(255) ");
    QString request = QString("CREATE TABLE clients ( %1);").arg(fieldsString);
    qDebug() << "we are trying to create a table using the following request: " << request;
    if(!query.exec(request)) qDebug() << "can't create table";
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
    qDebug() << "so we are trying to perform the following request " << request;
    if(!query.exec(request))
    {
        qDebug() << "Can't insert data";
        return false;
    }
    return true;
}

bool Lz::ClientStorage::update(quint64 id, const QJsonObject& client)
{
    Q_UNUSED(id);
    Q_UNUSED(client);
    return false;
}

bool Lz::ClientStorage::remove(quint64 id)
{
    Q_UNUSED(id);
    return false;
}

QSqlDatabase& Lz::ClientStorage::database()
{
    return m_database;
}
