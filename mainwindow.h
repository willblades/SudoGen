//======================================================================
// mainwindow.h
// Author: Will Blades
// Description: A class for generating and handling Qt GUI code
//======================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "board.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitiateWindow();

private slots:
    void About();
    void NewGame();
    void DestroyWindow();

private:
    Ui::MainWindow *ui;
    Board* board;
};

#endif // MAINWINDOW_H
