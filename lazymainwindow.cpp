#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>


#include <QJsonObject>
#include <QVBoxLayout>


#include "lazymainwindow.h"
#include "core.h"
#include "patternstorage.h"
#include "patternlistwidget.h"
#include "presetcombobox.h"
#include "presetstorage.h"
#include "infoform.h"

Lz::MainWindow::MainWindow(Lz::Core* core, QWidget *parent)
    : QMainWindow(parent), m_core(core)
{
    m_presetComboBox = new PresetComboBox();
    m_presetComboBox->setPresetStorage(m_core->presetStorage());

    m_patternList = new PatternListWidget();
    m_patternList->setPatternStorage(m_core->patternStorage());
    m_patternList->setPresetStorage(m_core->presetStorage());
    connect(m_presetComboBox, SIGNAL(currentTextChanged(QString)), m_patternList, SLOT(updatePreset(QString)));

    m_infoForm = new InfoForm();
    m_infoForm->setPatternStorage(m_core->patternStorage());
    m_infoForm->setPatternListWidget(m_patternList);

    m_goButton = new QPushButton("Старт");
    connect(m_goButton, SIGNAL(clicked()), this, SLOT(handleGoButtonClicked()));

    QLayout* presetLayout = new QHBoxLayout();
    presetLayout->addWidget(new QLabel("Набор"));
    presetLayout->addWidget(m_presetComboBox);

    QLayout* patternWithPresetLayout = new QVBoxLayout();
    patternWithPresetLayout->addWidget(m_patternList);
    patternWithPresetLayout->addItem(presetLayout);

    QLayout* patternLayout = new QHBoxLayout();
    patternLayout->addWidget(m_infoForm);
    patternLayout->addItem(patternWithPresetLayout);

    QLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(m_goButton);

    QLayout* mainLayout = new QVBoxLayout();
    mainLayout->addItem(patternLayout);
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
