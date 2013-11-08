#include <QWidget>
#include <QVBoxLayout>

#include "lazymainwindow.h"
#include "core.h"
#include "patternstorage.h"
#include "patternlistwidget.h"

Lz::MainWindow::MainWindow(Lz::Core* core, QWidget *parent)
    : QMainWindow(parent), m_core(core)
{
    m_patternList = new PatternListWidget();
    m_patternList->setPatternStorage(m_core->patternStorage());

    QLayout* l = new QVBoxLayout;
    l->addWidget(m_patternList);
    this->setCentralWidget(new QWidget());
    this->centralWidget()->setLayout(l);
}

Lz::MainWindow::~MainWindow()
{

}

