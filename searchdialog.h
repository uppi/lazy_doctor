#ifndef LZ_SEARCHDIALOG_H
#define LZ_SEARCHDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>

namespace Lz {

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SearchDialog(QWidget *parent = 0);

signals:

public slots:

    void handleOkButtonClick();
    void handleCancelButtonClick();

private:
    QTableView  * m_tableView;
    QLineEdit   * m_searchLineEdit;
    QPushButton * m_okButton;
    QPushButton * m_cancelButton;
};

} // namespace Lz

#endif // LZ_SEARCHDIALOG_H
