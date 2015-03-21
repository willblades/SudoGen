//======================================================================
// mainwindow.cpp
// Author: Will Blades
// Description: The main "backend" of the Qt GUI. This is where all the
// intializations and signal handling occurs
//======================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"


// Default constructor
// Allocates signal handling for some of the menu actions and calls the 
// initialization function InitiateWindow
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Assign a signalmapper to handle all the button and menu action signals
    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(On_Clicked(int)));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(NewGame()));
    connect(ui->actionSolve_it, SIGNAL(triggered()), this, SLOT(Solver()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(About()));

    int counter = 0;
    allbuttons = this->findChildren<QPushButton*>();
    foreach (QPushButton* button, allbuttons)
    {
        signalMapper->setMapping(button, counter);
        connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        counter++;
    }
    InitiateWindow();
}

// actionNew_Game Signal handler
// Attempts to destroy the current puzzle and generate a new one
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
    msgBox.setText("SuDoGen v0.3 \nA simple sudoku generator \nAuthor: "
                   "Will Blades \nBuild: Mar 21 2014");
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
    PopulateWindow();
}

// Refreshs the contents of the cells with the current contents of the board
// Used in both initialization and Puzzle solver.
void MainWindow::PopulateWindow()
{
    std::vector<std::vector<int> > puzzle = board->getBoard();

    int counter = 0;
    int x =0; int y = 0;
    int colorcount = 0;
    foreach (QPushButton* button, allbuttons)
    {
        QString buttonname = "pushButton_" +  QString::number(counter);
        button->setObjectName(buttonname);
        button->setText(" ");
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

// Destroys the current puzzle instance and
// resets the values of the grid
void MainWindow::DestroyWindow()
{
    QString emptycell = " ";
    delete board;
    foreach (QPushButton* button, allbuttons)
    {
        button->setText(emptycell);
        button->repaint();
    }
}

// A "global" handler for handling all the buttons signals
// Once any cell is clicked, the user is prompted with an
// QInputString, and the userinput is then compared with
// that of the current solution. If it matches, then the
// cell is updated with the new number, otherwise an error
// message appears
void MainWindow::On_Clicked(int location)
{
    // get the right coordinates of the board
    int x = location / board->getBoardlength();
    int y = location % board->getBoardlength();
    std::vector<std::vector<int> > solution = board->getSolution();
    bool ok;
    int user_answer;
    QString text = QInputDialog::getText(this, tr("Enter Your Answer"),
                   tr("Choose a number from 1-9"), QLineEdit::Normal,
                      QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        user_answer =  text.toInt();
    if ( user_answer == solution[x][y])
    {
        allbuttons.at(location)->setText(QString::number(user_answer));
        board->FindandEraseEmptySpace(x,y);
    }
    else if (ok && user_answer != solution[x][y] )
    {
        QMessageBox wronganswer_message;
        wronganswer_message.setText("Wrong Answer!");
        wronganswer_message.exec();
    }

    if (board->isPuzzleSolved())
    {
        QMessageBox congratulations;
        congratulations.setText("Congratulations! Puzzle solved!");
        congratulations.exec();
    }
}

// Calls the Sudoku solver function
void MainWindow::Solver()
{
    board->SolveGeneratedPuzzle();
    PopulateWindow();
}

// default destructor 
MainWindow::~MainWindow()
{
    delete ui;
}


