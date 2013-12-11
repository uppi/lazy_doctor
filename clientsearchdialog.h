#ifndef LZ_CLIENTSEARCHDIALOG_H
#define LZ_CLIENTSEARCHDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlTableModel>


namespace Lz {


class ClientStorage;
class Core;

/**
 * @brief QDialog used to search for clients in @a ClientStorage
 */
class ClientSearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ClientSearchDialog(Core *core, QWidget *parent = 0);

    QJsonObject selectedClient();
signals:

public slots:

    void handleOkButtonClick();
    void handleCancelButtonClick();

private:
    QTableView  * m_tableView;
    QLineEdit   * m_searchLineEdit;
    QPushButton * m_okButton;
    QPushButton * m_cancelButton;

    ClientStorage * m_clientDatabase;
    QSqlTableModel * m_sqlTableModel;

    Core*           m_core;
};

} // namespace Lz

#endif // LZ_CLIENTSEARCHDIALOG_H
