//======================================================================
// mainwindow.h
// Author: Will Blades
// Description: A class for generating and handling Qt GUI code
//======================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QtCore>
#include <QtGui>
#include <QInputDialog>
#include <QMessageBox>
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
    void Solver();
    void DestroyWindow();
    void On_Clicked(int location);
private:
    void PopulateWindow();
    Ui::MainWindow *ui;
    Board* board;
    QSignalMapper *signalMapper;
    QList<QPushButton*> allbuttons;
};

#endif // MAINWINDOW_H
