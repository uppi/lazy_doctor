#include <QDebug>
#include <QSqlQuery>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "clientstorage.h"
#include "searchdialog.h"
#include "core.h"


Lz::SearchDialog::SearchDialog(Lz::Core* core, QWidget *parent) :
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
    m_sqlQueryModel = new QSqlQueryModel();
    QSqlQuery query(m_clientDatabase->database());
    query.exec("SELECT * from clients");
    m_sqlQueryModel->setQuery(query);
    m_tableView->setModel(m_sqlQueryModel);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(m_okButton, SIGNAL(clicked()), this, SLOT(handleOkButtonClick()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(handleCancelButtonClick()));
}

void Lz::SearchDialog::handleOkButtonClick()
{
    qDebug() << "ok";
    accept();
}
void Lz::SearchDialog::handleCancelButtonClick()
{
    qDebug() << "cancel";
    reject();
}
