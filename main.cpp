#include "lazymainwindow.h"
#include "core.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString fileName = QFileDialog::getOpenFileName(0, "Choose config file",
                                                     "",
                                                     "Config files (*.json)");

    Lz::Core core;
    if(core.init(fileName))
    {
        Lz::MainWindow w(&core);
        w.show();
        return a.exec();
    }
    return 0;
}
