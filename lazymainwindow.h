#ifndef LAZYMAINWINDOW_H
#define LAZYMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QEvent>

namespace Lz
{

class Core;
class PatternListWidget;
class InfoForm;
class PresetComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Core* core, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleGoButtonClicked();
    void handleLoadFromDbButtonClicked();
    void handleSaveToDbButtonClicked();
    void handleClearButtonClicked();
    void handleSaveCheckBoxStateChanged(int state);

private:
    Core* m_core;

    PatternListWidget* m_patternList;
    InfoForm* m_infoForm;
    PresetComboBox* m_presetComboBox;
    QPushButton* m_goButton;
    QPushButton* m_loadFromDbButton;
    QPushButton* m_saveToDbButton;
    QPushButton* m_clearButton;
    QCheckBox* m_printCheckBox;
    QCheckBox* m_saveCheckBox;
    QString m_savePath;
};

}

#endif // LAZYMAINWINDOW_H
