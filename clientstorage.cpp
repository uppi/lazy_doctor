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
    QString request = QString(
                "CREATE TABLE IF NOT EXISTS clients ("
                "__id__"
                " INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                "%1);"
                ).arg(fieldsString);
    qDebug() << "we are trying to create a table using the following request: " << request;
    if(!query.exec(request)) qDebug() << "can't create table";
    return true;
}

bool Lz::ClientStorage::add(const QJsonObject& client)
{
    QSqlQuery query(m_database);

    int id = -1;
    QString keys, values, updateString;
    if(client.keys().contains("__id__"))
    {
        id = client.value("__id__").toDouble(-1);
    }
    for(auto key : client.keys())
    {
        if(key != "__id__")
        {
            auto val = client.value(key).toString();
            if(id == -1)
            {
                keys = QString("%1%2, ").arg(keys).arg(key);
                values = QString("%1'%2', ").arg(values).arg(val);
            }
            else
            {
                updateString = QString("%1%2=%3, ").arg(updateString).arg(key).arg(val);
            }
        }
    }
    if(keys.isEmpty() && updateString.isEmpty())
    {
        return false;
    }
    else
    {
        if(!keys.isEmpty()) keys = keys.mid(0, keys.size() - 2);
        if(!values.isEmpty()) values = values.mid(0, values.size() - 2);
        if(!updateString.isEmpty()) updateString = updateString.mid(0, updateString.size() - 2);
    }
    QString request;
    if(id == -1)
    {
        request = QString("INSERT INTO clients(%1) VALUES (%2);").arg(keys).arg(values);
    }
    else
    {
        request = QString("UPDATE clients SET %1 WHERE __id__==%2;").arg(updateString).arg(id);
    }
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
