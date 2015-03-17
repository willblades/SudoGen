//======================================================================
// main.cpp
// Author: Will Blades
// The main function of the program. This is where the Qt Application is
// called & run
//======================================================================

#include "mainwindow.h"
#include "board.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
