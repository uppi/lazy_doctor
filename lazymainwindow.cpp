#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>


#include <QJsonObject>
#include <QVBoxLayout>


#include "lazymainwindow.h"
#include "core.h"
#include "patternstorage.h"
#include "patternlistwidget.h"
#include "infoform.h"

Lz::MainWindow::MainWindow(Lz::Core* core, QWidget *parent)
    : QMainWindow(parent), m_core(core)
{
    m_patternList = new PatternListWidget();
    m_patternList->setPatternStorage(m_core->patternStorage());

    m_infoForm = new InfoForm();
    m_infoForm->setPatternStorage(m_core->patternStorage());
    m_infoForm->setPatternListWidget(m_patternList);

    m_goButton = new QPushButton("Старт");
    connect(m_goButton, SIGNAL(clicked()), this, SLOT(handleGoButtonClicked()));

    QLayout* mainLayout = new QVBoxLayout();

    QLayout* patternLayout = new QHBoxLayout;
    patternLayout->addWidget(m_infoForm);
    patternLayout->addWidget(m_patternList);
    mainLayout->addItem(patternLayout);

    QLayout* controlLayout = new QHBoxLayout;
    controlLayout->addWidget(m_goButton);
    mainLayout->addItem(controlLayout);

    this->setCentralWidget(new QWidget());
    this->centralWidget()->setLayout(mainLayout);
}

Lz::MainWindow::~MainWindow()
{

}

void Lz::MainWindow::handleGoButtonClicked()
{
    QJsonObject request;
    QJsonObject fields = m_infoForm->json();
    QJsonArray patterns = m_patternList->json();

    /* just a test */
    QJsonObject actions;
    actions.insert("print", true);

    request.insert("fields", fields);
    request.insert("patterns", patterns);
    request.insert("actions", actions);

    m_core->render(request);
}
