#ifndef LAZYMAINWINDOW_H
#define LAZYMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>

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

private:
    Core* m_core;

    PatternListWidget* m_patternList;
    InfoForm* m_infoForm;
    PresetComboBox* m_presetComboBox;
    QPushButton* m_goButton;
    QPushButton* m_loadFromDbButton;
    QPushButton* m_saveToDbButton;
    QPushButton* m_clearButton;
};

}

#endif // LAZYMAINWINDOW_H
