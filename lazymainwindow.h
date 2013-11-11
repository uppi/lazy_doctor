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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Core* core, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleGoButtonClicked();

private:
    Core* m_core;

    PatternListWidget* m_patternList;
    InfoForm* m_infoForm;
    QPushButton* m_goButton;
};

}

#endif // LAZYMAINWINDOW_H
