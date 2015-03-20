//======================================================================
// Board.h
// Author: Will Blades
// Description: The main "backend" of the program. This is where the
// initial Sudoku board is randomly initialized, sudoku puzzle generated
// and the puzzle solver all implemented. Debug functions and depricated
// intializing method included for possible future use. 
//======================================================================

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
//#include <random>
//#include <chrono>
#include <QTime>
#include <set>


// an enum for storing pre-defined, user-selectable levels of 
// difficulty
enum difficulty
{
    easy, moderate,hard
};

class Board
{
public:
    Board();
    Board(difficulty diff);
    Board(difficulty diff, int length);
    Board(int length);
    ~Board();
    void Initialize();
    void GeneratePuzzle();
    void DisplayInConsole();
    void SolveGeneratedPuzzle();
    std::vector<std::vector<int> > getBoard() { return board; }
    std::vector<std::vector<int> > getSolution() { return solution; }
    int getBoardlength() { return board_length; }
protected:
    void Startup();
    void FindandEraseEmptySpace(int key, int value);
    bool IsNumberinSubGrid(int number, int xgrid, int ygrid);
    void HiddenSingles();
private:
	// the puzzle presented to the player 
    std::vector<std::vector<int> > board;
	// the solution to the same puzzle 
    std::vector<std::vector<int> > solution;
    std::vector<int> possible_numbers;
	// locations of the unfilled spots in the puzzle
    std::multimap<int, int> emptyspaces;
    int board_length;
    difficulty difficulty_settings;
};

#endif
