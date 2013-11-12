#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "searchdialog.h"


Lz::SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent)
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
