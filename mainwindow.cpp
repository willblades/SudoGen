//======================================================================
// mainwindow.cpp
// Author: Will Blades
// Description: The main "backend" of the Qt GUI. This is where all the
// intializations and signal handling occurs
//======================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>


// Default constructor
// Allocates signal handling for some of the menu actions and calls the 
// initialization function InitiateWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(NewGame()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(About()));

    InitiateWindow();
}

// actionNew_Game Signal handler
// Attempts to destroy the current puzzle and generate a new one
// NOTE: TO BE DEBUGGED, NOT FULLY FUNCTIONAL AS OF YET
void MainWindow::NewGame()
{
    DestroyWindow();
    InitiateWindow();
}

// Creates a Messagebox displaying the program's credits when the About
// action menu is selected
void MainWindow::About()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("SuDoGen v0.1c \nA simple sudoku generator \nAuthor: "
                   "Will Blades \nBuild: Mar 18 2014");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

// Initializes the puzzle by calling an instance of Board and its puzzle
// generating functions. A list of all available QPushButtons is then 
// iterated though, where every single button gets a number from the 
// generated puzzle and background colour (either teal or white) depending
// whether its location is odd or even. 
void MainWindow::InitiateWindow()
{
    board = new Board();
    board->Initialize();
    board->GeneratePuzzle();
   // board->DisplayInConsole();
    std::vector<std::vector<int> > puzzle = board->getBoard();
    QList<QPushButton*> allbuttons = this->findChildren<QPushButton*>();

    int counter = 0;
    int x =0; int y = 0;
    int colorcount = 0;
    foreach (QPushButton* button, allbuttons)
    {
        QString buttonname = "pushButton_" +  QString::number(counter);
        button->setObjectName(buttonname);
        if (colorcount%2 == 0)
            button->setStyleSheet("background-color: teal");
        else
            button->setStyleSheet("background-color: white");
        if (puzzle[x][y] != -1)
            button->setText(QString::number(puzzle[x][y]));

        counter++,y++;colorcount++;
        if (counter == board->getBoardlength())
        {
            x++;
            y = 0;
            counter = 0;
        }
    }
}

// Attempts to destory the current puzzle instance
// NOTE: TO BE DEBUGGED, NOT FULLY FUNCTIONAL AS OF YET
void MainWindow::DestroyWindow()
{
    QString emptycell = " ";
    delete board;
    QList<QPushButton*> allbuttons = this->findChildren<QPushButton*>();
    foreach (QPushButton* button, allbuttons)
    {
        button->setText(emptycell);
        button->repaint();
    }
}

// default destructor 
MainWindow::~MainWindow()
{
    delete ui;
}


