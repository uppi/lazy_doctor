#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <QApplication>
#include <QMessageBox>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QGroupBox>
#include <QFileDialog>


#include "mainwindow.h"
#include "core.h"
#include "patternstorage.h"
#include "patternlistwidget.h"
#include "presetcombobox.h"
#include "presetstorage.h"
#include "clientform.h"
#include "clientsearchdialog.h"
#include "clientstorage.h"

Lz::MainWindow::MainWindow(Lz::Core* core, QWidget *parent)
    : QMainWindow(parent), m_core(core)
{
    m_printCheckBox = new QCheckBox("Печатать");
    m_printCheckBox->setChecked(true);
    m_saveCheckBox = new QCheckBox("Сохранить на диск");
    connect(m_saveCheckBox, SIGNAL(stateChanged(int)), this, SLOT(handleSaveCheckBoxStateChanged(int)));

    m_presetComboBox = new PresetComboBox();
    m_presetComboBox->setPresetStorage(m_core->presetStorage());
    m_presetComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    m_patternList = new PatternListWidget();
    m_patternList->setPatternStorage(m_core->patternStorage());
    m_patternList->setPresetStorage(m_core->presetStorage());
    m_patternList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    connect(m_presetComboBox, SIGNAL(currentTextChanged(QString)),
            m_patternList, SLOT(updatePreset(QString)));

    m_infoForm = new ClientForm();
    m_infoForm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_infoForm->setPatternStorage(m_core->patternStorage());
    m_infoForm->setPatternListWidget(m_patternList);

    m_loadFromDbButton = new QPushButton("Найти в базе");
    connect(m_loadFromDbButton, SIGNAL(clicked()), this, SLOT(handleLoadFromDbButtonClicked()));
    m_saveToDbButton = new QPushButton("Сохранить");
    connect(m_saveToDbButton, SIGNAL(clicked()), this, SLOT(handleSaveToDbButtonClicked()));
    m_clearButton = new QPushButton("Очистить");
    connect(m_clearButton, SIGNAL(clicked()), this, SLOT(handleClearButtonClicked()));

    m_goButton = new QPushButton("  Старт  ");
    m_goButton->setAutoDefault(true);
    m_goButton->setDefault(true);
    connect(m_goButton, SIGNAL(clicked()), this, SLOT(handleGoButtonClicked()));

    QLayout* presetLayout = new QHBoxLayout();
    QLabel* presetLabel = new QLabel("Набор: ");
    presetLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);

    presetLayout->addWidget(presetLabel);
    presetLayout->addWidget(m_presetComboBox);

    QLayout* patternWithPresetLayout = new QVBoxLayout();
    patternWithPresetLayout->addWidget(m_patternList);
    patternWithPresetLayout->addItem(presetLayout);

    QLayout* formControlLayout = new QHBoxLayout();
    formControlLayout->addWidget(m_loadFromDbButton);
    formControlLayout->addWidget(m_saveToDbButton);
    formControlLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    formControlLayout->addWidget(m_clearButton);

    QLayout* formWithControlLayout = new QVBoxLayout();
    formWithControlLayout->addWidget(m_infoForm);
    formWithControlLayout->addItem(formControlLayout);

    QGroupBox* formGroupBox = new QGroupBox(" Данные ");
    formGroupBox->setLayout(formWithControlLayout);

    QGroupBox* patternGroupBox = new QGroupBox(" Документы ");
    patternGroupBox->setLayout(patternWithPresetLayout);

    QLayout* fullLayout = new QHBoxLayout();
    fullLayout->addWidget(formGroupBox);
    fullLayout->addWidget(patternGroupBox);


    QLayout* controlLayout = new QHBoxLayout();
    controlLayout->addWidget(m_printCheckBox);
    controlLayout->addWidget(m_saveCheckBox);
    controlLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    controlLayout->addWidget(m_goButton);

    QLayout* mainLayout = new QVBoxLayout();
    mainLayout->addItem(fullLayout);
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
    if(m_printCheckBox->isChecked()) actions.insert("print", true);
    if(m_saveCheckBox->isChecked()) actions.insert("save", m_savePath);

    request.insert("fields", fields);
    request.insert("patterns", patterns);
    request.insert("actions", actions);

    m_core->render(request);
}

void Lz::MainWindow::handleLoadFromDbButtonClicked()
{
    ClientSearchDialog dialog(m_core);
    if(dialog.exec() != QDialog::Accepted) return;
    auto result = dialog.selectedClient();
    if(result.isEmpty()) return;
    qDebug() << result;
    m_infoForm->fill(result);
}

void Lz::MainWindow::handleSaveToDbButtonClicked()
{
    QJsonObject request = m_infoForm->json();
    if(request.contains("__id__"))
    {
        QMessageBox msgBox;
        msgBox.setText("Сохраняемые данные основываются на загруженных из базы.");
        msgBox.setInformativeText("Переписать данные клиента?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        switch (ret) {
            case QMessageBox::Yes:
                m_core->clientStorage()->add(request);
                break;
            case QMessageBox::No:
                request.remove("__id__");
                m_core->clientStorage()->add(request);
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

void Lz::MainWindow::handleClearButtonClicked()
{
    QJsonObject request;
    m_infoForm->fill(request);
}

void Lz::MainWindow::handleSaveCheckBoxStateChanged(int state)
{
    Q_UNUSED(state)
    if(m_saveCheckBox->isChecked())
    {
        m_savePath = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения");
        if(m_savePath.isEmpty())
        {
            m_saveCheckBox->setCheckState(Qt::Unchecked);
        }
    }
}
