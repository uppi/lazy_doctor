#ifndef LAZYMAINWINDOW_H
#define LAZYMAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Lz
{

class Core;
class PatternListWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Core* core, QWidget *parent = 0);
    ~MainWindow();

private:
    Core* m_core;

private:
    PatternListWidget* m_patternList;
};

}

#endif // LAZYMAINWINDOW_H
