#ifndef LZ_SEARCHDIALOG_H
#define LZ_SEARCHDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>


namespace Lz {

class ClientStorage;
class Core;

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(Core *core, QWidget *parent = 0);

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
    QSqlQueryModel * m_sqlQueryModel;

    Core*           m_core;
};

} // namespace Lz

#endif // LZ_SEARCHDIALOG_H
