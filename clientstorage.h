#ifndef LZ_CLIENTDATABASE_H
#define LZ_CLIENTDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Lz {

/**
 * @brief Storage for clients
 */
class ClientStorage : public QObject
{
    Q_OBJECT
public:
    explicit ClientStorage(QObject *parent = 0);

    /**
     * @brief   Create sqlite database with given name and list of text fields or connect to existing database.
     * @param   dbName          Database name.
     * @param   fields          Field list.
     * @return                  True if created/connected successfully, false otherwise.
     *
     * @todo    It doesn't return false in a number of cases it has to do so.
     */
    bool init(const QString& dbName, QStringList fields);

    /**
     * @brief   Add a record to the database or update an existing one if client object contains a valid __id__ field.
     * @param   client          Client record as a json object: {__id__ : $clientId, field1_name : field1_value, ...}
     * @return                  True if created/connected successfully, false otherwise.
     */
    bool add(const QJsonObject& client);

    /**
     * @brief   Remove a record with given @param id from database.
     * @param   id              Id of the record to be deleted
     * @return                  True if deleted successfully, false otherwise.
     *
     * @todo    Implement.
     */
    bool remove(quint64 id);

    /**
     * @brief   Direct access to the database
     * @return  Database reference.
     */
    QSqlDatabase& database();

private:
    QSqlDatabase m_database;
};

} // namespace Lz

#endif // LZ_CLIENTDATABASE_H
