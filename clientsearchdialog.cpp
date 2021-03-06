#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "clientstorage.h"
#include "clientsearchdialog.h"
#include "core.h"


Lz::ClientSearchDialog::ClientSearchDialog(Lz::Core* core, QWidget *parent) :
    QDialog(parent), m_core(core)
{

    m_okButton = new QPushButton("Ok");
    m_cancelButton = new QPushButton("Отмена");
    m_tableView = new QTableView();

    QLayout * controls = new QHBoxLayout();
    controls->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    controls->addWidget(m_okButton);
    controls->addWidget(m_cancelButton);

    QLayout * main = new QVBoxLayout();
    main->addWidget(m_tableView);
    main->addItem(controls);

    setLayout(main);

    m_clientDatabase = m_core->clientStorage();

    m_sqlTableModel = new QSqlTableModel(this, m_clientDatabase->database());
    m_sqlTableModel->setTable("clients");
    m_sqlTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_sqlTableModel->select();
    m_tableView->setModel(m_sqlTableModel);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setSortingEnabled(true);
    m_tableView->setColumnHidden(0, 1);

    connect(m_okButton, SIGNAL(clicked()), this, SLOT(handleOkButtonClick()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButtonClick()));
}

QJsonObject Lz::ClientSearchDialog::selectedClient()
{
    QJsonObject result;
    auto rows = m_tableView->selectionModel()->selectedRows();
    if(rows.isEmpty()) return result;
    QSqlRecord record = m_sqlTableModel->record(rows.at(0).row());

    result.insert(record.fieldName(0), record.value(0).toDouble());
    for(int i = 1; i < record.count(); i++)
    {
        result.insert(record.fieldName(i), record.value(i).toString());
    }

    return result;
}

void Lz::ClientSearchDialog::handleOkButtonClick()
{
    qDebug() << "ok";
    accept();
}
void Lz::ClientSearchDialog::handleCancelButtonClick()
{
    qDebug() << "cancel";
    reject();
}
