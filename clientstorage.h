#ifndef LZ_CLIENTDATABASE_H
#define LZ_CLIENTDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Lz {

class ClientStorage : public QObject
{
    Q_OBJECT
public:
    explicit ClientStorage(QObject *parent = 0);

    bool init(const QString& dbName, QStringList fields);
    bool populate();


    bool add(const QJsonObject& client);
    bool update(quint64 id, const QJsonObject& client);
    bool remove(quint64 id);


    QSqlDatabase& database();
signals:

public slots:

private:
    QSqlDatabase m_database;
};

} // namespace Lz

#endif // LZ_CLIENTDATABASE_H
