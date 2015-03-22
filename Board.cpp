//======================================================================
// Board.cpp
// Author: Will Blades
// Description: Implementation of Board.h 
//======================================================================

#include "Board.h"


// Default constructor, a typical sudoku puzzle (9x9) and an easy
// difficulty setting is assumed by default 
Board::Board()
{
    board_length = 9;
    difficulty_settings = easy;
    Startup();
}

// A constructor where grid length is still default, but the 
// difficulty is overridden 
// @param diff user-defined difficulty
Board::Board(difficulty diff)
{
    difficulty_settings = diff;
    Startup();
}

// A constructor where both difficulty and grid length are overridden 
// and customized by the user 
// @param diff user-defined difficulty
// @param length user-defined board length 
Board::Board(difficulty diff, int length)
{
    difficulty_settings = diff;
    board_length = length;
    Startup();
}

// A constructor where difficulty is still default, but the 
// grid length is overridden 
// @param length length of the custom grid
Board::Board(int length)
{
	difficulty_settings = easy;
    board_length = length;
    Startup();
}

// The main function called by all constructors to initialized the
// multi-dimensional vector (board) and populate possible_numbers
// with a list of all numbers that can possibly appear on the puzzle
void Board::Startup()
{
    for (int i = 1; i < board_length + 1; i++)
        possible_numbers.push_back(i);

    board.resize(board_length);
    for (int i = 0; i < board_length; i++)
            board[i].resize(9,-1);
}

// default destructor 
Board::~Board()
{
    board.clear();
    solution.clear();
    possible_numbers.clear();
    emptyspaces.clear();
}

int RandomInt(int low, int high)
{
// Random number between low and high
return qrand() % ((high + 1) - low) + low;
}

// Generate a sudoku puzzle by randomly swapping rows and columns
// of a valid solved sudoku puzzle through randomly generated 
// numbers of repetitions. 
void Board::Initialize()
{
    board[0] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    board[1] = { 4, 5, 6, 7, 8, 9, 1, 2, 3 };
    board[2] = { 7, 8, 9, 1, 2, 3, 4, 5, 6 };
    board[3] = { 2, 3, 4, 5, 6, 7, 8, 9, 1 };
    board[4] = { 5, 6, 7, 8, 9, 1, 2, 3, 4 };
    board[5] = { 8, 9, 1, 2, 3, 4, 5, 6, 7 };
    board[6] = { 3, 4, 5, 6, 7, 8, 9, 1, 2 };
    board[7] = { 6, 7, 8, 9, 1, 2, 3, 4, 5 };
    board[8] = { 9, 1, 2, 3, 4, 5, 6, 7, 8 };

    //std::default_random_engine generator;
    //std::uniform_int_distribution<int> distribution(1, std::nextafter(50,INT_MAX));
    int swap_repeatitions = RandomInt(1,50);//distribution(generator);

    //swap columns
    for (int i = 0; i < swap_repeatitions; i++)
    {
        for (int j = 0; j < board_length ; j += 3)
        {
            //std::uniform_int_distribution<int> random(0, std::nextafter(2,INT_MAX));
            int column1 = RandomInt(0,2);//random(generator);
            int column2 = RandomInt(0,2);//random(generator);
            std::swap(board[j + column1], board[j + column2]);
        }
    }

    // swap rows
    //std::uniform_int_distribution<int> distribution2(1, std::nextafter(50,INT_MAX));
    int row_repeatitions = RandomInt(1,50); //distribution2(generator);
    for (int i = 0; i < row_repeatitions; i++)
    {
        for (int j = 0; j < board_length ; j += 3)
        {
            //std::uniform_int_distribution<int> random(0, std::nextafter(2,INT_MAX));
            int row1 = RandomInt(0,2);//random(generator);
            int row2 = RandomInt(0,2);//random(generator);

            for (int k = 0; k < board_length; k++)
            {
                int swap_temp = board[k][j + row1];
                board[k][j + row1] = board[k][j + row2];
                board[k][j + row2] = swap_temp;
            }
        }
    }
}

// Once the full-valid sudoku grid has been randomly shuffled, the 
// puzzle is generated by randomly emptying the cells. The number of 
// cells emptied depends on the difficulty of the puzzle. A random
// number from 46-50 is selected for easy, 51-57 for moderate, 58-65
// for difficult. This random number signifies the number of cells 
// to be removed from the grid. 
void Board::GeneratePuzzle()
{
    //std::default_random_engine generator;
    int emptycells;

    if (difficulty_settings == easy)
    {
        //std::uniform_int_distribution<int> distribution1(46, 50);
        emptycells = RandomInt(46,50);//distribution1(generator);
    }
    else if (difficulty_settings == moderate)
    {
        //std::uniform_int_distribution<int> distribution2(51, 57);
        emptycells = RandomInt(51,57);//distribution2(generator);
    }
    else
    {
        //std::uniform_int_distribution<int> distribution3(58, 65);
        emptycells = RandomInt(58,65);//distribution3(generator);
    }

    solution = board;
    int location1, location2;
    bool isempty;

    for (int i = 0; i < emptycells; i++)
    {
        isempty = true;
        while (isempty)
        {
            //std::uniform_int_distribution<int> distribution(0, board_length - 1);
            location1 = RandomInt(0, board_length - 1);//distribution(generator);
            //std::uniform_int_distribution<int> distribution2(0, board_length - 1);
            location2 = RandomInt(0, board_length - 1);//distribution2(generator);
            if (board[location1][location2] != -1)
            {
                emptyspaces.insert(std::make_pair(location1, location2));
                board[location1][location2] = -1;
                isempty = false;
            }
        }
    }
}

// Searches a row for a given number
// obsolete function, used for the older InitiateRandomFromScratch()
bool NoDuplicatesFound(std::vector<int> row, int element)
{
    std::vector<int>::iterator it = std::find(row.begin(), row.end(), element);
    if (it != row.end())
        return false;
    else
        return true;
}

// Helper function for the deprecated InitiateRandomFromScratch
void searchRowsandCols(std::vector<int>& searchzone,
    std::set<int>& possible_locations, int checkednumber, int colrownumber)
{
    //std::sort(searchzone.begin(), searchzone.end());
    if (std::find(searchzone.begin(), searchzone.end(), checkednumber) != searchzone.end())
        possible_locations.erase(colrownumber);
}


// Displays the current Sudoku grid in a console screen. 
// Mainly used for debugging purposes 
void Board::DisplayInConsole()
{
    for (int i = 0; i < board_length; i++)
        std::cout << "--";
    std::cout << "\n";
    for (int i = 0; i < board_length; i++)
    {
        std::cout << "|";
        for (int j = 0; j < board_length; j++)
        {
            int number = board[i][j];
            if (number != -1)
                std::cout << board[i][j] << "|";
            else
                std::cout << "_|";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < board_length ; i++)
        std::cout << "--";
    std::cout << "\n";
    std::cin.ignore(80, '\n');
}

// Initial (and somewhat crude) implementation of the puzzle solver
// loops the Hidden singles method a number of times until it can 
// no longer find any more numbers 
void Board::SolveGeneratedPuzzle()
{
    for (int i = 0; i < 50; i++)
        HiddenSingles();
}

// Determine if the current Sudoku puzzle has been solved
// by looking at the number of present empty cells
bool Board::isPuzzleSolved()
{
    if (emptyspaces.empty())
        return true;
    else
        return false;
}

// Helper function for HiddenSpaces()
// Since the multimap of emptyspaces contain values of similar keys,
// We need to explicitly look for a matching pair (as opposed to a single
// key or value) and eliminate that pair from the map of emptyspaces if found. 
// @param key : column position of a given 9x9 (or customised) grid entry
// @param value : row position of a given 9x9 (or customised) grid entry
void Board::FindandEraseEmptySpace(int key, int value)
{
    typedef std::multimap<int, int>::iterator mapiter;
    std::pair<mapiter, mapiter> pairiter = emptyspaces.equal_range(key);

    mapiter iterator = pairiter.first;
    for (; iterator != pairiter.second; ++iterator)
    {
        if (iterator->second == value)
        {
            emptyspaces.erase(iterator);
            break;
        }
    }
}

// Helper function for HiddenSpaces()
// Looks for an instance of a given number in a given sudoku subgrid
// (Subgrid is defined as one of the 3x3 grids populating the sudoku
// puzzle. As a general rule of thumb, two instances of the same number
// can never be present in a single subgrid
// @param number the number to be searched
// @param xgrid the starting x-location of the a given subgrid in the 
// multi-dimensional vector board
// @param ygrid the starting y-location of the a given subgrid in the 
// multi-dimensional vector board
bool Board::IsNumberinSubGrid(int number, int xgrid, int ygrid)
{
    bool result = false;
    for (int i = xgrid; i < xgrid + 3; i++)
        for (int j = ygrid; j < ygrid + 3; j++)
            if (board[i][j] == number)
                return true;
    return result;
}

// This function (as of yet) partially solves the generated Sudoku
// puzzle by looking for hidden singles. A single call won't do
// as the updated puzzle opens up new possibilities for the function
// to explore
void Board::HiddenSingles()
{
    for (int i = 0; i < (unsigned)possible_numbers.size(); i++)
    {
        int checkednumber = possible_numbers.at(i);
        for (int xgrid = 0; xgrid < board_length ; xgrid += 3)
        {
            for (int ygrid = 0; ygrid < board_length; ygrid += 3)
            {
                // check and see if the number is already present or not
                // if it is, skip & move on
                if (!IsNumberinSubGrid(checkednumber, xgrid, ygrid))
                {
                    std::set<int> possiblerow_locations{ xgrid, xgrid + 1, xgrid + 2 };
                    std::set<int> possiblecol_locations{ ygrid, ygrid + 1, ygrid + 2 };

                    // search rows first
                    for (int rowcount = xgrid; rowcount < xgrid + 3; rowcount++)
                    {
                        std::vector<int> currentrow = board[rowcount];
                        searchRowsandCols(currentrow,
                            possiblerow_locations, checkednumber,rowcount);
                    }

                    // search columns next
                    std::vector<int> currentcol;
                    currentcol.resize(board_length, -1);
                    for (int colcount = ygrid; colcount < ygrid + 3; colcount++)
                    {
                        for (int j = 0; j < board_length; j++)
                            currentcol[j] = board[j][colcount];
                        searchRowsandCols(currentcol,
                            possiblecol_locations, checkednumber,colcount);
                    }

                    // if only one empty location remains, all's good and dandy! else...
                    // we have to eliminate locations that might be already occupied in hopes
                    // we end up with only one. This is done by eliminating non-empty cells

                    if (possiblerow_locations.size() == 1 && possiblecol_locations.size() == 1)
                    {
                        int cell_x = *possiblerow_locations.begin();
                        int cell_y = *possiblecol_locations.begin();
                        board[cell_x][cell_y] = checkednumber;
                        FindandEraseEmptySpace(cell_x, cell_y);
                    }
                    else
                    {
                        int emptyrowcount = 0;
                        int temploc[2] = { -1, -1 };
                        std::set<int>::iterator rowiter, coliter;
                        for (rowiter = possiblerow_locations.begin(); rowiter !=
                            possiblerow_locations.end(); ++rowiter)
                        {
                            for (coliter = possiblecol_locations.begin(); coliter !=
                                possiblecol_locations.end(); ++coliter)
                            {
                                int checkingx = *rowiter;
                                int checkingy = *coliter;
                                if (board[checkingx][checkingy] == -1)
                                {
                                    emptyrowcount++;
                                    temploc[0] = checkingx;
                                    temploc[1] = checkingy;
                                }
                            }
                        }
                        if (emptyrowcount == 1)
                        {
                            int locatedcell_x = temploc[0];
                            int locatedcell_y = temploc[1];
                            board[locatedcell_x][locatedcell_y] = checkednumber;
                            FindandEraseEmptySpace(locatedcell_x, locatedcell_y);
                        }
                    }
                    possiblecol_locations.clear(), possiblerow_locations.clear();
                }
            }
        }
    }
}
