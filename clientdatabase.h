#ifndef LZ_CLIENTDATABASE_H
#define LZ_CLIENTDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Lz {

class ClientDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ClientDatabase(QObject *parent = 0);

    bool init(QString dbName);
    bool populate();

    QSqlDatabase& database();
signals:

public slots:

private:
    QSqlDatabase m_database;
};

} // namespace Lz

#endif // LZ_CLIENTDATABASE_H
