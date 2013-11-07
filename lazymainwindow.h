#ifndef LAZYMAINWINDOW_H
#define LAZYMAINWINDOW_H

#include <QMainWindow>

namespace Lz
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

}

#endif // LAZYMAINWINDOW_H
